#include "dbConnect.h"

bool dbConnect::searchOrders(void)
{
    sql::PreparedStatement *prep_stmt;
    sql::ResultSet *res;
    res = NULL;
    try
    {
        prep_stmt = con->prepareStatement(dbConnect::ssqlSelectOrders);
        prep_stmt->setInt(1, 243935060);
        prep_stmt->setInt(2, 243935160);
        res = prep_stmt->executeQuery();
        while (res->next())
        {
            dborders ord(res);
            ord.show();
            ord.save(consino);
        }
        std::cout << "Done" << std::endl;
        delete res;
        delete prep_stmt;
        return true;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Caught general exception: " << e.what() << std::endl;
        return false;
    }
}

dbConnect::~dbConnect()
{
    delete con;
    delete consino;
}

dbConnect::dbConnect(char *dbLocal[3], char *dbsino[3])
{
    try
    {
        driver = get_driver_instance();
        con = driver->connect(dbLocal[0], dbLocal[1], dbLocal[2]);

        driversino = get_driver_instance();
        consino = driversino->connect(dbsino[0], dbsino[1], dbsino[2]);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Caught general exception: " << e.what() << std::endl;
    }
}
