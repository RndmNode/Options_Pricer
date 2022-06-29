#ifndef API_H
#define API_H

#include <iostream>
#include <stdio.h>
#include <curl/curl.h>
#include <string>

class API{
    public:
        API(){};
        API(std::string api_key, std::string cert_path);
        ~API();
    private:
        CURL *api_handle;
        CURLcode result;

        std::string api_key;
        std::string base_url;

        
};

#endif /* ifndef API_H */