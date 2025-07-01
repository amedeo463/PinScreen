// Header file for PC only.

#include "common.hpp"
#include "requests.c/requests.h"

// initialize values
const string BUTTON_CONFIRM = "[RETURN]";

// miscellaneous functions and values
class p_misc {
    public:
        void waitForUser() {
            string trashbin;
            getline(cin, trashbin); // no one is remembering the input of this
        }

        int download(const string URL, string saveas) {
            const char *URL_[] = *URL;
            RequestsHandler *request = req_get(request, URL_, "");
            return 0;
        }
};
