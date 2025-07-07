// LIBPINSC v1.0
// A library to interpret PinsaScript

// This is the main header.


// ifdefs for all supported platforms.
// Each points to a device-specific header file.
// common.hpp, included by every platform-specific header file, already includes iostream. Don't panic.
#if defined(WINDOWS) || defined(LINUX) || defined(BSD)
#include "PC.hpp"
#elif defined(N3DS)
#include "3DS.hpp"
#else
#include "PC.hpp" // compiles for PC by default
#endif

#include <fstream>

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
        //TODO: add struct or something else to better implement error handling
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
            if (action == "notice") {
                // tell the user something and wait for it to hit the CONFIRM key
                cout << "NOTICE: " << argstr << "\n";
                ps_w_misc.waitForUser();
            } else if (action == "log") {
                // show a simple message on screen
                cout << "LOG: " << argstr << "\n";
            } else if (action == "download") {
                // download a file from the internet
                if (ARGCOUNT >= 2) { // check if there are enough arguments
                    ps_w_misc.download(ARGS[1], ARGS[2]);
                } else {
                    return ps_errs.NOT_ENOUGH_ARGUMENTS; // not enough arguments
                }
            } else if (action  == "copy") {
                //TODO: test this
                if (filesystem::is_directory(ARGS[1])) {
                    try {
                        filesystem::copy(ARGS[1], ARGS[2]);
                    } catch (...) {
                        return ps_errs.CANNOT_COPY; // unable to copy file
                    }
                }
            } else if (action == "delete") {
            } else if (action == "newdir") {
            } else if (action == "copydir") {
            } else if (action == "deldir") {
            } else if (action == "rdeldir") {
            } else if (action == "extract") {
            } else if (action == "attryn") {
            } else if (action == "attrsel") {
            } else if (action == "attrmsel") {
            } else if (action == "addattr") {
            } else if (action == "remattr") {
            } else if (action == "stop") {
                return ps_errs.SCRIPT_STOPPED; // script stopped (no error)
            } else if (action == "estop") {
                cout << "ERROR: " << argstr << "\n";
                return ps_errs.SCRIPT_STOPPED_ERROR; // script stopped (an error occoured)
            } else if (action == "nothing") {
                ;
            } else {
                return ps_errs.UNKNOWN_INSTRUCTION; // unknown instruction name
            }

            return 0;
        }
};