#ifndef ORDEREXECUTIONS_H
#define ORDEREXECUTIONS_H

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

class orderExecutions
{
public:
    orderExecutions();
    ~orderExecutions();


    std::string getOrderid()  { return orderid; }
    void setOrderid( std::string &orderid_) { orderid = orderid_; }

    double getExecVol()  { return exec_vol; }
    void setExecVol(double execVol) { exec_vol = execVol; }

    double getExecPrice()  { return exec_price; }
    void setExecPrice(double execPrice) { exec_price = execPrice; }

    std::string getContrahent()  { return contrahent; }
    void setContrahent( std::string &contrahent_) { contrahent = contrahent_; }

    std::string getTs()  { return ts; }
    void setTs( std::string &ts_) { ts = ts_; }

    double getInstant()  { return instant; }
    void setInstant(double instant_) { instant = instant_; }

    std::string getIfid()  { return ifid; }
    void setIfid( std::string &ifid_) { ifid = ifid_; }

    std::string getUniqueid()  { return uniqueid; }
    void setUniqueid( std::string &uniqueid_) { uniqueid = uniqueid_; }

    double getCurrencySpot()  { return currency_spot; }
    void setCurrencySpot(double currencySpot) { currency_spot = currencySpot; }

    int getOpenclose()  { return openclose; }
    void setOpenclose(int openclose_) { openclose = openclose_; }

    double getFees()  { return fees; }
    void setFees(double fees_) { fees = fees_; }

    double getCalcfee()  { return calcfee; }
    void setCalcfee(double calcfee_) { calcfee = calcfee_; }

    long getStateid()  { return stateid; }
    void setStateid(long stateid_) { stateid = stateid_; }

    std::string getFlags()  { return flags; }
    void setFlags( std::string &flags_) { flags = flags_; }

    std::string getMifidTvtic()  { return mifid_tvtic; }
    void setMifidTvtic( std::string &mifidTvtic) { mifid_tvtic = mifidTvtic; }

    std::string getExchangetradeid()  { return exchangetradeid; }
    void setExchangetradeid( std::string exchangetradeid_) { exchangetradeid = exchangetradeid_; }


    std::string getExchangeorderid()  { return exchangeorderid; }
    void setExchangeorderid( std::string exchangeorderid_) { exchangeorderid = exchangeorderid_; }

    long getId()  { return id; }
    void setId(long id_) { id = id_; }

private:
    long id;
    std::string orderid;
    double exec_vol;
    double exec_price;
    std::string contrahent;
    std::string ts;
    double instant;
    std::string ifid;
    std::string uniqueid;
    double currency_spot;
    int openclose;
    double fees;
    double calcfee;
    long stateid;
    std::string flags;
    std::string mifid_tvtic;
    std::string mifid_waiver;
    std::string exchangetradeid;
    std::string exchangeorderid;

};

#endif