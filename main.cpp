#include <iostream>
#include <stdio.h>
#include <curl/curl.h>
#include <string>
#include <cpr/cpr.h>

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

int main() {
    std::cout << "Hello, World!" << std::endl;

    CURL *curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "https://www.google.com");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        std::cout << readBuffer << std::endl;

        std::cout << "res: " << res << std::endl ;

        cpr::Response r = cpr::Get(cpr::Url{"https://ipinfo.io"}
//                                   ,cpr::Authentication{"user", "pass"},
//                                   cpr::Parameters{{"anon", "true"}, {"key", "value"}}
                                   );

//        cpr::Response r = cpr::Get(cpr::Url{"http://www.httpbin.org/get"});

        std::cout << "status: " << r.status_code << std::endl;                  // 200

        std::cout << "content-type: " << r.header["content-type"] << std::endl;       // application/json; charset=utf-8
        std::cout << "text: " << r.text  << std::endl          ;               // JSON text string

    }
    return 0;

}
