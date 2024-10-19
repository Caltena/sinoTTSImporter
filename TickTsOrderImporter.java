package de.sino.baaderimport;

import de.sino.baaderimport.helper.SystemConfiguration;
import de.sino.baaderimport.persistence.jooq.db_tickts.Tables;
import lombok.extern.slf4j.Slf4j;
import net.logstash.logback.argument.StructuredArguments;
import org.jooq.DSLContext;
import org.jooq.Record;
import org.jooq.ResultQuery;
import org.jooq.SQLDialect;
import org.jooq.exception.DataAccessException;
import org.jooq.impl.DSL;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import java.time.format.DateTimeFormatter;
import java.time.format.DateTimeFormatterBuilder;
import java.time.temporal.ChronoField;

@Slf4j
@Component
public class TickTsOrderImporter {

	public static DateTimeFormatter mysqlDateTimeFormat = new DateTimeFormatterBuilder().appendPattern("yyyy-MM-dd HH:mm:ss")
	                                                                                    .appendFraction(ChronoField.MICRO_OF_SECOND, 0, 6, true)
	                                                                                    .toFormatter();

	@Autowired
	private SystemConfiguration systemConfiguration;


	public boolean process() {
		boolean success = true;


		final String jdbcConnectionString = String.format("jdbc:mysql://%s:%s/%s?useSSL=%s", this.systemConfiguration.getPersistenceSinoDbTickTsHost(), this.systemConfiguration.getPersistenceSinoDbTickTsPort(), this.systemConfiguration.getPersistenceSinoDbTickTsName(), this.systemConfiguration.getPersistenceSinoDbTickTsSSL());
		try (final Connection connectionDestinationDB = DriverManager.getConnection(jdbcConnectionString, this.systemConfiguration.getPersistenceSinoDbTickTsUser(), this.systemConfiguration.getPersistenceSinoDbTickTsPass())) {
			final DSLContext dslContextDestination = DSL.using(connectionDestinationDB, SQLDialect.MYSQL);


			// mstrater darf nicht passieren. orderexecutions kommen nicht immer nur für die neueste Order
			/*Integer maxIDOrders = dslContextDestination.select(DSL.max(Tables.ORDERS.ID))
			                                           .from(Tables.ORDERS)
			                                           .fetchOne(DSL.max(Tables.ORDERS.ID));

			if (maxIDOrders == null) {
				maxIDOrders = Integer.valueOf(0);
			}*/

			Long maxIDOrderExcecutions = dslContextDestination.select(DSL.max(Tables.ORDEREXECUTIONS.ID))
			                                                  .from(Tables.ORDEREXECUTIONS)
			                                                  .fetchOne(DSL.max(Tables.ORDEREXECUTIONS.ID));

			if (maxIDOrderExcecutions == null) {
				maxIDOrderExcecutions = Long.valueOf(0);
			}
			// TickTsOrderImporter.log.debug("latest copied orderexecutionid = '{}'", maxIDOrderExcecutions);

			final String jdbcConnectionStringOrderDB = String.format("jdbc:mysql://%s:%s/%s?useSSL=%s", this.systemConfiguration.getPersistenceTicktsTradedbHost(), this.systemConfiguration.getPersistenceTicktsTradedbPort(), this.systemConfiguration.getPersistenceTicktsTradedbName(), this.systemConfiguration.getPersistenceTicktsTradedbSSL());
			try (final Connection connectionSourceDB = DriverManager.getConnection(jdbcConnectionStringOrderDB, this.systemConfiguration.getPersistenceTicktsTradedbUser(), this.systemConfiguration.getPersistenceTicktsTradedbPass())) {
				final DSLContext dslContextSource = DSL.using(connectionSourceDB, SQLDialect.MYSQL);

				Long maxIDOrderExcecutionsOnTradeServer = (Long) dslContextSource.select(DSL.max(DSL.field("id")))
			                                                  .from("tradedb.orderexecutions")
			                                                  .fetchOne(DSL.max(DSL.field("id")));

				final String sqlSelectOrders = """
						 SELECT
						      o.*
							, il.name AS productname
						 FROM
						     tradedb.orders o
						    LEFT JOIN quotedb.isinlist  il ON o.isin = il.isin
						 WHERE
						         o.id IN (SELECT
						                      oe.orderid
						                  FROM
						                      tradedb.orderexecutions oe
						                  WHERE
						                      oe.id > {0}
						                      AND oe.id <= {1}
						                  GROUP BY
						                      oe.orderid
						                  ORDER BY
						                      oe.orderid ASC)
						 ORDER BY
						     o.id ASC
						""";

				final ResultQuery<org.jooq.Record> recordResultQueryOrders = dslContextSource.resultQuery(sqlSelectOrders, maxIDOrderExcecutions, maxIDOrderExcecutionsOnTradeServer);
				int ordersCounter = 0;


				final String insertOrders = """
						INSERT INTO `db_tickts`.`orders`
							(`id`,
							`isin`,
							`productname`,
							`market`,
							`ifmarket`,
							`account`,
							`user`,
							`created`,
							`created_instant`,
							`dest`,
							`currency`,
							`symbol`,
							`mspid`,
							`comment`,
							`externid`,
							`type`,
							`completed`,
							`instrumenttype`,
							`ocogroup`,
							`otogroup`,
							`groupid`,
							`grouptype`,
							`pricefactor`)
						VALUES
							(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)
						ON DUPLICATE KEY UPDATE completed = ?				
						""";

				//ON DUPLICATE KEY UPDATE SET completed = ?;
				final PreparedStatement insertPrepStatement = connectionDestinationDB.prepareStatement(insertOrders);

				for (final Record sourceRecord : recordResultQueryOrders) {
					Integer currentID = -1;
					try {
						currentID = sourceRecord.get(Tables.ORDERS.ID);
						insertPrepStatement.setInt(1, currentID);
						insertPrepStatement.setString(2, sourceRecord.get(Tables.ORDERS.ISIN));
						insertPrepStatement.setString(3, sourceRecord.get("productname") != null ? sourceRecord.get("productname")
																													.toString() : "");
						insertPrepStatement.setString(4, sourceRecord.get(Tables.ORDERS.MARKET));
						insertPrepStatement.setString(5, sourceRecord.get(Tables.ORDERS.IFMARKET));
						insertPrepStatement.setString(6, sourceRecord.get(Tables.ORDERS.ACCOUNT));
						insertPrepStatement.setString(7, sourceRecord.get(Tables.ORDERS.USER));
						insertPrepStatement.setString(8, sourceRecord.get("created") != null ? sourceRecord.get("created")
																										   .toString() : null);
						insertPrepStatement.setBigDecimal(9, sourceRecord.get(Tables.ORDERS.CREATED_INSTANT));
						insertPrepStatement.setString(10, sourceRecord.get(Tables.ORDERS.DEST));
						insertPrepStatement.setString(11, sourceRecord.get(Tables.ORDERS.CURRENCY));
						insertPrepStatement.setString(12, sourceRecord.get(Tables.ORDERS.SYMBOL));
						insertPrepStatement.setString(13, sourceRecord.get(Tables.ORDERS.MSPID));
						insertPrepStatement.setString(14, sourceRecord.get(Tables.ORDERS.COMMENT));
						insertPrepStatement.setString(15, sourceRecord.get(Tables.ORDERS.EXTERNID));
						insertPrepStatement.setString(16, sourceRecord.get(Tables.ORDERS.TYPE));
						insertPrepStatement.setString(17, sourceRecord.get("completed") != null ? sourceRecord.get("completed")
																											  .toString() : null);
						insertPrepStatement.setString(18, sourceRecord.get(Tables.ORDERS.INSTRUMENTTYPE));
						insertPrepStatement.setString(19, sourceRecord.get(Tables.ORDERS.OCOGROUP));
						insertPrepStatement.setString(20, sourceRecord.get(Tables.ORDERS.OTOGROUP));
						insertPrepStatement.setString(21, sourceRecord.get(Tables.ORDERS.GROUPID));
						insertPrepStatement.setInt(22, sourceRecord.get(Tables.ORDERS.GROUPTYPE));
						insertPrepStatement.setBigDecimal(23, sourceRecord.get(Tables.ORDERS.PRICEFACTOR));
						insertPrepStatement.setString(24, sourceRecord.get("completed") != null ? sourceRecord.get("completed")
																											  .toString() : null);
						final int rows = insertPrepStatement.executeUpdate();
						ordersCounter++;

					}catch (final Exception exception) {
						TickTsOrderImporter.log.debug("Can't execute insert into tblorders for id '{}'", currentID, exception);
						success = false;
					}
				}

				//insertPrepStatement.executeBatch();


				final String sqlSelectOrderExecutions = """
						SELECT
						    *
						FROM
						    tradedb.orderexecutions oe
						WHERE
						    oe.id > {0}
						    AND oe.id <= {1}
						ORDER BY
						    oe.id ASC
						""";
				final ResultQuery<org.jooq.Record> recordResultQueryOrderExcecutions = dslContextSource.resultQuery(sqlSelectOrderExecutions, maxIDOrderExcecutions, maxIDOrderExcecutionsOnTradeServer);

				final String insertOrderExecutions = """
						INSERT INTO `db_tickts`.`orderexecutions` 
							(`id`, 
							`orderid`, 
							`exec_vol`, 
							`exec_price`, 
							`contrahent`, 
							`ts`, 
							`instant`, 
							`ifid`, 
							`uniqueid`, 
							`currency_spot`, 
							`openclose`, 
							`fees`, 
							`calcfee`, 
							`stateid`, 
							`flags`, 
							`mifid_tvtic`, 
							`mifid_waiver`, 
							`exchangetradeid`, 
							`exchangeorderid`) 
						VALUES 
							(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)				
						""";

				final PreparedStatement insertExecutionsPrepStatement = connectionDestinationDB.prepareStatement(insertOrderExecutions);

				int orderExecutionsCounter = 0;
				for (final Record sourceRecord : recordResultQueryOrderExcecutions) {
					Long currentID = -1L;
					int currentOrderID = -1;
					try {
						currentID = sourceRecord.get(Tables.ORDEREXECUTIONS.ID);
						currentOrderID = sourceRecord.get(Tables.ORDEREXECUTIONS.ORDERID);
						insertExecutionsPrepStatement.setLong(1, currentID);
						insertExecutionsPrepStatement.setInt(2, currentOrderID);
						insertExecutionsPrepStatement.setInt(3, sourceRecord.get(Tables.ORDEREXECUTIONS.EXEC_VOL));
						insertExecutionsPrepStatement.setBigDecimal(4, sourceRecord.get(Tables.ORDEREXECUTIONS.EXEC_PRICE));
						insertExecutionsPrepStatement.setString(5, sourceRecord.get(Tables.ORDEREXECUTIONS.CONTRAHENT));
						insertExecutionsPrepStatement.setString(6, sourceRecord.get("ts") != null ? sourceRecord.get("ts").toString() : null);
						insertExecutionsPrepStatement.setBigDecimal(7, sourceRecord.get(Tables.ORDEREXECUTIONS.INSTANT));
						insertExecutionsPrepStatement.setString(8, sourceRecord.get(Tables.ORDEREXECUTIONS.IFID));
						insertExecutionsPrepStatement.setString(9, sourceRecord.get(Tables.ORDEREXECUTIONS.UNIQUEID));
						insertExecutionsPrepStatement.setBigDecimal(10, sourceRecord.get(Tables.ORDEREXECUTIONS.CURRENCY_SPOT));
						insertExecutionsPrepStatement.setInt(11, sourceRecord.get(Tables.ORDEREXECUTIONS.OPENCLOSE));
						insertExecutionsPrepStatement.setBigDecimal(12, sourceRecord.get(Tables.ORDEREXECUTIONS.FEES));
						insertExecutionsPrepStatement.setBigDecimal(13, sourceRecord.get(Tables.ORDEREXECUTIONS.CALCFEE));
						insertExecutionsPrepStatement.setLong(14, sourceRecord.get(Tables.ORDEREXECUTIONS.STATEID));
						insertExecutionsPrepStatement.setString(15, sourceRecord.get(Tables.ORDEREXECUTIONS.FLAGS));
						insertExecutionsPrepStatement.setString(16, sourceRecord.get(Tables.ORDEREXECUTIONS.MIFID_TVTIC));
						insertExecutionsPrepStatement.setString(17, sourceRecord.get(Tables.ORDEREXECUTIONS.MIFID_WAIVER));
						insertExecutionsPrepStatement.setString(18, sourceRecord.get(Tables.ORDEREXECUTIONS.EXCHANGETRADEID));
						insertExecutionsPrepStatement.setString(19, sourceRecord.get(Tables.ORDEREXECUTIONS.EXCHANGEORDERID));
						//insertExecutionsPrepStatement.setString(20, sourceRecord.get("trading_day") != null ? sourceRecord.get("trading_day").toString() : null);

						final int rows = insertExecutionsPrepStatement.executeUpdate();
						orderExecutionsCounter++;

					}catch (final Exception exception) {
						TickTsOrderImporter.log.debug("Can't execute insert into tblorderexecutions for id '{}' (OrderID: '{}')", currentID, currentOrderID, exception);
						success = false;
					}
				}
				TickTsOrderImporter.log.info("tickTS TradeDB sync: orders : {}, orderexcecutions: {} [FullSuccess: "+success+"] [From oe.id {} to {}]", ordersCounter, orderExecutionsCounter, maxIDOrderExcecutions, maxIDOrderExcecutionsOnTradeServer, StructuredArguments.keyValue("copiedOrders", ordersCounter), StructuredArguments.keyValue("copiedOrderExcecutions", orderExecutionsCounter));
			}
		} catch (final SQLException | DataAccessException e) {
			TickTsOrderImporter.log.error("something failed by copying tradedb orders", e);
			throw new RuntimeException(e);
		}


		return success;
	}

}
