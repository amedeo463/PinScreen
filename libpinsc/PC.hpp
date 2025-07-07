// Header file for PC only.

#define DCURL_STATICLIB

#include "common.hpp"
#include <curl/curl.h>

// initialize values
const string BUTTON_CONFIRM = "[RETURN]";
// miscellaneous functions and values
class p_misc {
    public:
        void waitForUser() {
            string trashbin;
            getline(cin, trashbin); // no one is remembering the input of this
        }

        int download(string URL, string saveas) {
            // stolen and modified from: https://gist.github.com/alghanmi/c5d7b761b2c9ab199157
            CURL *curl;
            CURLcode res;
            FILE *fsaves = fopen(saveas.c_str(), "a");
            // TODO: check documentation for fopen() modes

            curl = curl_easy_init();
            if (curl) {
                curl_easy_setopt(curl, CURLOPT_URL, URL.c_str());
                curl_easy_setopt(curl, CURLOPT_WRITEDATA, &fsaves);

                res = curl_easy_perform(curl);
                curl_easy_cleanup(curl);
            }

            return 0;
            //TODO: fix and finish this function
        }

    private:
};