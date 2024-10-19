#ifndef ORDERS_H
#define ORDERS_H

#include <string>
#include <iostream>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <ctime>

#pragma once


class dborders
{
public:

  #include "sqlquery.h"

  dborders(sql::ResultSet *res);
  ~dborders();


  void load(sql::ResultSet *res);
  bool save ( sql::Connection *con );
  void show();
  time_t String2time_t(const std::string &strDateTime);



private:
  int id;
  std::string isin;
  std::string productname;
  std::string market;
  std::string ifmarket;
  std::string account;
  std::string user;
  std::string created;
  float created_instant;
  std::string dest;
  std::string currency;
  std::string symbol;
  std::string mspid;
  std::string comment;
  std::string externid;
  std::string type;
  std::string completed;
  std::string instrumenttype;
  std::string ocogroup;
  std::string otogroup;
  std::string groupid;
  int grouptype;
  float pricefactor;

public:
  

  int getId() const { return id; }
  void setId(int id_) { id = id_; }

  std::string getIsin() const { return isin; }
  void setIsin(const std::string &isin_) { isin = isin_; }

  std::string getProductname() const { return productname; }
  void setProductname(const std::string &productname_) { productname = productname_; }

  std::string getMarket() const { return market; }
  void setMarket(const std::string &market_) { market = market_; }

  std::string getIfmarket() const { return ifmarket; }
  void setIfmarket(const std::string &ifmarket_) { ifmarket = ifmarket_; }

  std::string getAccount() const { return account; }
  void setAccount(const std::string &account_) { account = account_; }

  std::string getUser() const { return user; }
  void setUser(const std::string &user_) { user = user_; }

  std::string getCreated() const { return created; }
  void setCreated(const std::string &created_) { created = created_; }

  float getCreatedInstant() const { return created_instant; }
  void setCreatedInstant(float createdInstant) { created_instant = createdInstant; }

  std::string getDest() const { return dest; }
  void setDest(const std::string &dest_) { dest = dest_; }

  std::string getCurrency() const { return currency; }
  void setCurrency(const std::string &currency_) { currency = currency_; }

  std::string getSymbol() const { return symbol; }
  void setSymbol(const std::string &symbol_) { symbol = symbol_; }

  std::string getMspid() const { return mspid; }
  void setMspid(const std::string &mspid_) { mspid = mspid_; }

  std::string getComment() const { return comment; }
  void setComment(const std::string &comment_) { comment = comment_; }

  std::string getExternid() const { return externid; }
  void setExternid(const std::string &externid_) { externid = externid_; }

  std::string getType() const { return type; }
  void setType(const std::string &type_) { type = type_; }

  std::string getCompleted() const { return completed; }
  void setCompleted(const std::string &completed_) { completed = completed_; }

  std::string getInstrumenttype() const { return instrumenttype; }
  void setInstrumenttype(const std::string &instrumenttype_) { instrumenttype = instrumenttype_; }

  std::string getOcogroup() const { return ocogroup; }
  void setOcogroup(const std::string &ocogroup_) { ocogroup = ocogroup_; }

  std::string getOtogroup() const { return otogroup; }
  void setOtogroup(const std::string &otogroup_) { otogroup = otogroup_; }

  std::string getGroupid() const { return groupid; }
  void setGroupid(const std::string &groupid_) { groupid = groupid_; }

  int getGrouptype() const { return grouptype; }
  void setGrouptype(int grouptype_) { grouptype = grouptype_; }

  float getPricefactor() const { return pricefactor; }
  void setPricefactor(float pricefactor_) { pricefactor = pricefactor_; }
};

#endif