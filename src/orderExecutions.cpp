#include "orderExecutions.h"

dborderExecutions::dborderExecutions(sql::ResultSet *res)
{
    dborderExecutions::load(res);
}

dborderExecutions::~dborderExecutions()
{
}

void dborderExecutions::load(sql::ResultSet *res)
{
    dborderExecutions::setId(res->getInt("id"));
    dborderExecutions::setOrderid(res->getString("orderid"));
    dborderExecutions::setExecVol(res->getDouble("exec_vol"));
    dborderExecutions::setExecPrice(res->getDouble("exec_price"));
    dborderExecutions::setContrahent(res->getString("contrahent"));
    dborderExecutions::setTs(res->getString("ts"));
    dborderExecutions::setInstant(res->getDouble("instant"));
    dborderExecutions::setIfid(res->getString("ifid"));
    dborderExecutions::setUniqueid(res->getString("uniqueid"));
    dborderExecutions::setCurrencySpot(res->getDouble("currency_spot"));
    dborderExecutions::setOpenclose(res->getInt("openclose"));
    dborderExecutions::setFees(res->getDouble("fees"));
    dborderExecutions::setCalcfee(res->getDouble("calcfee"));
    dborderExecutions::setStateid(res->getInt64("stateid"));
    dborderExecutions::setFlags(res->getString("flags"));
    dborderExecutions::setMifidTvtic(res->getString("mifid_tvtic"));
    dborderExecutions::setMifidWaiver(res->getString("mifid_waiver"));
    dborderExecutions::setExchangetradeid(res->getString("exchangetradeid"));
    dborderExecutions::setExchangeorderid(res->getString("flags"));
}

void dborderExecutions::save(sql::Connection *con)
{
    sql::PreparedStatement *prep_stmt;
    sql::ResultSet *res;
    res = NULL;
    try
    {
        prep_stmt = con->prepareStatement(ssqlInsertOrderExecution);
        prep_stmt->setInt(1, getId());
        prep_stmt->setString(2, getOrderid());
        prep_stmt->setDouble(3, getExecVol());
        prep_stmt->setDouble(4, getExecPrice());
        prep_stmt->setString(5, getContrahent());
        prep_stmt->setString(6, getTs());
        prep_stmt->setDouble(7, getInstant());
        prep_stmt->setString(8, getIfid());
        prep_stmt->setString(9, getUniqueid());
        prep_stmt->setDouble(10, getCurrencySpot());
        prep_stmt->setDouble(11, getOpenclose());
        prep_stmt->setDouble(12, getFees());
        prep_stmt->setDouble(13, getCalcfee());
        prep_stmt->setInt64(14, getStateid());
        prep_stmt->setString(15, getFlags());
        prep_stmt->setString(16, getMifidTvtic());
        prep_stmt->setString(17, getMifidWaiver());
        prep_stmt->setString(18, getExchangetradeid());
        prep_stmt->setString(19, getExchangeorderid());
        prep_stmt->execute();
        delete res;
        delete prep_stmt;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Caught general exception: [saveOrder] " << e.what() << std::endl;
    }
}