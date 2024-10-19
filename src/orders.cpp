#include "orders.h"

dborders::dborders(sql::ResultSet *res)
{
    dborders::load(res);
}

dborders::~dborders()
{
}

time_t dborders::String2time_t(const std::string& strDateTime)
{
    tm t;
    strptime(strDateTime.c_str(), "%F %T", &t);
    return mktime(&t); 
}

void dborders::load(sql::ResultSet *res)
{
     dborders::setId ( res->getInt("id")) ;
     dborders::setIsin ( res->getString("isin")) ;
     dborders::setProductname (res->getString("productname")) ;
     dborders::setMarket ( res->getString("market")) ;
     dborders::setIfmarket (res->getString("ifmarket")) ;
     dborders::setAccount ( res->getString("account")) ;
     dborders::setUser (res->getString("user")) ;          
     dborders::setCreated ( res->getString("created")) ;
     dborders::setCreatedInstant (res->getDouble("created_instant")) ;
     dborders::setDest ( res->getString("dest")) ;
     dborders::setCurrency (res->getString("currency")) ;  
     dborders::setSymbol ( res->getString("symbol")) ;
     dborders::setMspid (res->getString("mspid")) ;  
     dborders::setComment ( res->getString("comment")) ;
     dborders::setExternid (res->getString("externid")) ;            
     dborders::setType ( res->getString("type")) ;
     dborders::setCompleted (res->getString("completed")) ;  
     dborders::setInstrumenttype ( res->getString("instrumenttype")) ;
     dborders::setOcogroup (res->getString("ocogroup")) ;  
     dborders::setOtogroup ( res->getString("otogroup")) ;
     dborders::setGroupid (res->getString("groupid")) ;            
     dborders::setGrouptype ( res->getInt("grouptype")) ;
     dborders::setPricefactor (res->getDouble("pricefactor")) ;        
}

bool dborders::save ( sql::Connection *con )
{
 sql::PreparedStatement *prep_stmt;
    sql::ResultSet *res;
    res = NULL;    
    try
    {
        prep_stmt = con->prepareStatement(ssqlInsertOrders);
        prep_stmt->setInt(1, getId());
        prep_stmt->setString (2, getIsin());
        prep_stmt->setString (3, getProductname());
        prep_stmt->setString (4, getMarket());
        prep_stmt->setString (5, getIfmarket());
        prep_stmt->setString (6, getAccount());
        prep_stmt->setString (7, getUser());
        prep_stmt->setString (8, getCreated());
        prep_stmt->setDouble (9, getCreatedInstant());
        prep_stmt->setString (10, getDest());
        prep_stmt->setString (11, getCurrency());
        prep_stmt->setString (12, getSymbol());
        prep_stmt->setString (13, getMspid());
        prep_stmt->setString (14, getComment());
        prep_stmt->setString (15, getExternid());
        prep_stmt->setString (16, getType());
        prep_stmt->setString (17, getCompleted());
        prep_stmt->setString (18, getInstrumenttype());
        prep_stmt->setString (19, getOcogroup());
        prep_stmt->setString (20, getOtogroup());
        prep_stmt->setString (21, getGroupid());
        prep_stmt->setInt (22, getGrouptype());
        prep_stmt->setDouble (23, getPricefactor());
        prep_stmt->setString (24, getCompleted());
        prep_stmt->execute();
        delete res;
        delete prep_stmt;
        return true;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Caught general exception: [saveOrder] " << e.what() << std::endl;
        return false;
    }
}

void dborders::show()
{
    std::cout << "ID     \t" << dborders::getId()   << "ISIN   \t" << dborders::getIsin() << std::endl;
    std::cout << "Productname   \t" << dborders::getProductname() << "Market   \t" << dborders::getMarket() << std::endl;
    std::cout << "IfMarket   \t" << dborders::getIfmarket() << "Account   \t" << dborders::getAccount() << std::endl;
    std::cout << "User   \t" << dborders::getUser() << "Created   \t" << dborders::getCreated() << std::endl;
    std::cout << "--------------------------------------------------------------\n" <<std::endl;
}
