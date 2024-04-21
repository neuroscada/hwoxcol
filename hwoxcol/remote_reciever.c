
#include "curl\curl.h"
#include "reciever_global_variables.h"

int send_to_remote_reciever(char filename[]) {
    CURL *curl;
    CURLcode res;
    struct curl_httppost *formpost = NULL;
    struct curl_httppost *lastptr = NULL;
    curl_global_init(CURL_GLOBAL_ALL);
    curl_formadd(&formpost, &lastptr,
                 CURLFORM_COPYNAME, "file",
                 CURLFORM_FILE, filename,
                 CURLFORM_END);
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, reciever_host_endpoint);
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            fprintf(stderr, "Error while requesting: %s\n", curl_easy_strerror(res));
            return -1;
        }
        curl_easy_cleanup(curl);
    }
    curl_formfree(formpost);
    curl_global_cleanup();
    return 0;
}