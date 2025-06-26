// Header file for PC only.

#include "common.hpp"
#include "requests.c/requests.h"

#if defined(WINDOWS)
#else // Linux/MacOS
#endif

// initialize values
const string BUTTON_CONFIRM = "[RETURN]";
const int DOWNLOAD_BUFFER = 4096;

// miscellaneous functions and values
class p_misc {
    public:
        void waitForUser() {
            string trashbin;
            getline(cin, trashbin); // no one is remembering the input of this
        }

        int download(string URL, string saveas) {
            return 0;
        }
};
