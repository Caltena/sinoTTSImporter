#include <stdlib.h>
#include "dbConnect.h"
#include "curlRest.h"
#include "orders.h"
#include "copyFileViaSSH.h"
#include "config.h"
#include "log.h"
#include <string>
#include <iostream>

/*
$ sudo apt-get install libcpprest-dev
*/


int main(int argc, char *argv[])
{
  // Connect to local DB


  Logger logger("log.txt");
  logger.log("Programm gestartet", Logger::INFO);
  logger.log("Read Database", Logger::INFO);
  dbConnect *dbC = new dbConnect(dbtickts , dbsino );
  dbC->searchOrders();
   logger.log("END Read Database", Logger::INFO);

/*
   logger.log("Read Rest-API", Logger::INFO);
  curlRest cr;
  cr.DownloadJSON(sUrl);
*/
  return 0;
}
