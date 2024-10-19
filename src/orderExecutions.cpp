#include "orderExecutions.h"

orderExecutions::orderExecutions(sql::ResultSet *res)
{
    orderExecutions::load(res);
}


orderExecutions::~orderExecutions()
{

}


void orderExecutions::load(sql::ResultSet *res)
{
    orderExecutions::setId ( res->getInt("id")) ;
    orderExecutions::setOrderid( res->getString("orderid"));
    orderExecutions::setExecVol( res->getDouble("exec_vol"));
    orderExecutions::setExecPrice( res->getDouble("exec_price"));
    orderExecutions::setContrahent( res->getString("contrahent"));
    orderExecutions::setTs( res->getString("ts"));
    orderExecutions::setInstant( res->getDouble("instant"));
    orderExecutions::setIfid( res->getString("ifid"));
    orderExecutions::setUniqueid( res->getString("uniqueid"));
    //...
}