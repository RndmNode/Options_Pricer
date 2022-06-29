#include "../include/api.h"

// constructor
API::API(std::string api_key, std::string cert_path){
    curl_global_init(CURL_GLOBAL_ALL);
    api_handle = curl_easy_init();
    curl_easy_setopt(api_handle, CURLOPT_CAINFO, cert_path.c_str());
}

// destructor
API::~API(){
    curl_easy_cleanup(api_handle);
    curl_global_cleanup();
}