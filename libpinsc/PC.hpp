// Header file for PC only.

#include "common.hpp"
extern "C" {
    #include <curl/curl.h>
}
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
            // I stole this piece of code from here: https://gist.github.com/whoshuu/2dc858b8730079602044
            // Then I applied some modifications
            auto curl = curl_easy_init();
            if (curl) {
                FILE *fileptr = fopen(saveas.c_str(), "a");
                string header_string;
                curl_easy_setopt(curl, CURLOPT_URL, URL.c_str()); // url
                curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
                curl_easy_setopt(curl, CURLOPT_USERAGENT, "curl/7.42.0"); // user agent
                curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 50L); // max redirects
                curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1L);
                curl_easy_setopt(curl, CURLOPT_WRITEDATA, &fileptr); 
                curl_easy_setopt(curl, CURLOPT_HEADERDATA, &header_string);

                char* url;
                long response_code;
                double elapsed;
                curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
                curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &elapsed);

                // Perform request and cleanup
                curl_easy_perform(curl);
                curl_easy_cleanup(curl);
                curl = NULL;

                if (response_code != CURLE_OK) {
                    return ps_errs.DOWNLOAD_FAIL;
                }
            }

            return 0;
            //TODO: fix and finish this function
            //          - implement curl
        }
};