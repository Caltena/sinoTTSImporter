#include "curlRest.h"

/**
 * @brief 
 *
 * @param 
 * @return 
 */
curlRest::curlRest()
{
}

/**
 * @brief 
 *
 * @param 
 * @return 
 */
curlRest::~curlRest()
{
}

/**
 * @brief 
 *
 * @param 
 * @return 
 */
 size_t curlRest::WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string *)userp)->append((char *)contents, size * nmemb);
    return size * nmemb;
}

/**
 * @brief 
 *
 * @param 
 * @return 
 */
int curlRest::DownloadJSON(char *sURL)
{
    CURL *curl;
    CURLcode res;
    std::string readBuffer;
    std::string client_id = "your_client_id";
    std::string client_secret = "your_client_secret";

    struct curl_slist *headers = NULL;

    // std::string auth = client_id + ":" + client_secret;
    // std::string encoded_auth = "Basic " + base64_encode(auth); // You need to implement base64_encode

    headers = curl_slist_append(headers, "Accept: application/json");
    headers = curl_slist_append(headers, "Content-Type: application/json");
    headers = curl_slist_append(headers, "charset: utf-8");
    // headers = curl_slist_append(headers, ("Authorization: " + encoded_auth).c_str());

    curl = curl_easy_init();
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_URL, sURL);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        if (CURLE_OK == res)
        {
            users user;
            user.readjson((std::string)readBuffer);
        }
    }
    return 0;
}
