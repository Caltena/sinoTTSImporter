#ifndef CURLREST_H
#define CURLREST_H

#include "users.h"
#include <iostream>
#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

#pragma once

class curlRest
{
public:
    curlRest();
    ~curlRest();

    static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);

    int DownloadJSON(char *sURL);

private:
};

#endif