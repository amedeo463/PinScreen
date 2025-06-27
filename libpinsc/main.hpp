// LIBPINSC v1.0
// A library to interpret PinsaScript

// This is the main header.


// ifdefs for all supported platforms.
// Each points to a device-specific header file.
// common.hpp, included by every platform-specific header file, already includes iostream. Don't panic.
#if defined(WINDOWS)
#include "PC.hpp"
#elif defined(LINUX) || defined(BSD)
#include "PC.hpp"
#elif defined(N3DS)
#include "console.hpp" // still TODO
#elif defined(WIIU)
#include "console.hpp" // again, still TODO
#else
#include "PC.hpp" // compiles for PC by default
#endif

_misc ps_misc;
p_misc ps_p_misc;

// contains wrappers for certain functions
class w_misc {
    public:
        void waitForUser() {
            cout << "Press " << BUTTON_CONFIRM << " to continue...\n";
            ps_p_misc.waitForUser();
        }
        void download(string URL, string saveas) {
            cout << "DOWNLOAD: " << saveas << " (" << URL << ")\n";
            ps_p_misc.download(URL, saveas);
        }
};
w_misc ps_w_misc;

// the library itself
class libps_class__ {
    public:
        // Array to hold the arguments at the last call of parse()
        string ARGS[LIBPS_ARG_LIMIT];

        int ARGCOUNT = 0;

        // Parse a line of code
        int parse(string line) {
            string s_line = ps_misc.strip(line);

            int last_end = 0;
            ARGCOUNT = 0;
            for (int i = 0; i < s_line.length(); i++) {
                if (s_line[i] == ' ') {
                    if (ARGCOUNT < LIBPS_ARG_LIMIT) {
                        if (i-last_end > 1) {
                            ARGS[ARGCOUNT] = s_line.substr(last_end, i-last_end);
                            ARGCOUNT++;
                        }
                    }

                    last_end = i+1;
                }
            }
            ARGS[ARGCOUNT] = s_line.substr(last_end, last_end-s_line.length()-1);

            return 0;
        }

        // Execute a single PinsaScript instruction
        int exec(string line) {
            // strip and parse instruction
            string line_s = ps_misc.strip(line);
            parse(line_s);

            // find the args (but as a string), mainly used for logging
            int temp0 = line_s.find_first_of(' ');
            string argstr = "";
            if (temp0 < line_s.length()) {
                argstr = line_s.substr(temp0+1, line_s.length()-1);
            }

            // get the instruction name, then make it lowercase for easier usage
            string action = ARGS[0];
            transform(action.begin(), action.end(), action.begin(), ::tolower);
            
            // after obtaining all this info, we can finally interpret the line
            if (action == "log") {
                // show a simple message on screen
                cout << "LOG: " << argstr << "\n";
            } else if (action == "notice") {
                // tell the user something and wait for it to hit the CONFIRM key
                cout << "NOTICE: " << argstr << "\n";
                ps_w_misc.waitForUser();
            } else if (action == "download") {
                // download a file from the internet
                if (ARGCOUNT >= 2) { // check if there are enough arguments
                    ps_w_misc.download(ARGS[1], ARGS[2]);
                } else {
                    return -2; // not enough arguments
                }
            } else if (action == "nothing") {
                ;
            } else if (action == "stop") {
                return -3; // script stopped (no error)
            } else if (action == "estop") {
                cout << "ERROR: " << argstr << "\n";
                return -4; // script stopped (an error occoured)
            } else {
                return -1; // unknown instruction name
            }

            return 0;
        }
};