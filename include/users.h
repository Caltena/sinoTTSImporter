#ifndef USERS_H
#define USERS_H
/*
rc/main.cpp:11:26: warning: unused parameter ‘argv’ [-Wunused-parameter]
   11 | int main(int argc, char *argv[])
      |                    ~~~~~~^~~~~~
g++ src/curlRest.o src/dbConnect.o src/main.o -o appDB -Llib -lmysqlcppconn -lssl -lcrypto -lcurl
rm -f src/curlRest.o src/dbConnect.o src/main.o
claus@claus-XPS13-9333:~/source/project/AppDB$ ./appDB
NAME
_NAME_
###
NAME
_NAME_
{
  "id": 1,
  "name": "Leanne Graham",
  "username": "Bret",
  "email": "Sincere@april.biz",
  "address": {
    "street": "Kulas Light",
    "suite": "Apt. 556",
    "city": "Gwenborough",
    "zipcode": "92998-3874",
    "geo": {
      "lat": "-37.3159",
      "lng": "81.1496"
    }
  },
  "phone": "1-770-736-8031 x56442",
  "website": "hildegard.org",
  "company": {
    "name": "Romaguera-Crona",
    "catchPhrase": "Multi-layered client-server neural-net",
    "bs": "harness real-time e-markets"
  }
}

*/

#include "users.h"
#include <iostream>
#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

#pragma once

class users
{
public:
    users();
    ~users();

    int id;
    std::string name, username, email;
    std::string street, suite, city, zipcode, lat, lng;

    int readjson(std::string readBuffer)
    {
        std::cout << readBuffer << std::endl;
        json jsonObject = json::parse(readBuffer);
        // Convert json object to C++ variables
        id = jsonObject["id"];
        name = jsonObject["name"];
        username = jsonObject["username"];
        email = jsonObject["email"];

        auto &address = jsonObject["address"];
        street = address["street"];

        suite = address["suite"];
        city = address["city"];
        zipcode = address["zipcode"];

        auto &geo = address["geo"];
        lat = geo["lat"];
        lng = geo["lng"];

        // Output the values
        std::cout << "Name: " <<    name << "\n";
        std::cout << "city: " << city << "\n";
         std::cout << "lat: " << lat << "\n";
        return 0;
    }

private:
};

#endif