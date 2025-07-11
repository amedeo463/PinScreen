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
            // took inspiraion from https://curl.se/libcurl/c/url2file.html
            CURL *curl;
            CURLcode res;
            FILE *fsaves = fopen(saveas.c_str(), "wb");
            curl_global_init(CURL_GLOBAL_ALL);
            curl = curl_easy_init();
            if (curl) {
                curl_easy_setopt(curl, CURLOPT_URL, URL.c_str());
                curl_easy_setopt(curl, CURLOPT_WRITEDATA, fsaves);
                curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, dataWrite);
                //curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

                curl_easy_perform(curl);
                fclose(fsaves);
                curl_easy_cleanup(curl);
                curl_global_cleanup();
            }

            //fclose(fsaves); //if you uncomment this simple line, the program segfaults
            return 0;
            //TODO: fix and finish this function
        }

    private:
        // stolen from https://curl.se/libcurl/c/url2file.html
        static size_t dataWrite(void *ptr, size_t size, size_t nmemb, void *stream) {
            size_t written = fwrite(ptr, size, nmemb, (FILE *)stream);
            return written;
        }
};