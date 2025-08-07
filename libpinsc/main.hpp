// LIBPINSC v1.0 (incomplete)
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
        int download(string URL, string saveas) {
            cout << "DOWNLOAD: " << URL << " --> " << saveas << "\n";
            return ps_p_misc.download(URL, saveas);
        }
};
w_misc ps_w_misc;

// the library itself
class libps_class__ {
    public:
        // Array to hold the arguments at the last call of parse()
        string ARGS[LIBPS_ARG_LIMIT];

        // Argument count at the last call of parse() (Number of items in ARGS[])
        int ARGCOUNT = 0;

        // ARGS[0] in lowercase
        string action;

        // Non-parsed text after ARGS[0].
        string argstr;

        // Array containing attributes
        string ATTRLIST[LIBPS_ATTR_LIMIT];

        // Number of currently active attributes.
        int ATTRCOUNT = 0;

        // Path to output directory (OUT:/)
        string OUTDIR = "./psout";

        // Path to temp folder (TEMP:/)
        string TEMPDIR = "./pstemp";

        // convert paths using OUT: and TEMP: to paths your system can understand
        string dirconv(string str_) {
            string s_str_ = ps_misc.strip(str_);
            string ret;
            if (s_str_.substr(0,4) == "OUT:") {
                ret = OUTDIR+"/"+s_str_.substr(4);
            } else if (s_str_.substr(0,5) == "TEMP:") {
                ret = TEMPDIR+"/"+s_str_.substr(5);
            } else {
                ret = s_str_;
            }

            return ret;
        }

        // Parse a line of code
        int parse(string line) {
            string s_line = ps_misc.strip(line);

            int last_end = 0;
            ARGCOUNT = 0;
            for (int i = 0; i < s_line.length(); i++) {
                if (s_line[i] == ' ') {
                    if (ARGCOUNT < LIBPS_ARG_LIMIT) {
                        if (i-last_end >= 1) {
                            ARGS[ARGCOUNT] = s_line.substr(last_end, i-last_end);
                            ARGCOUNT++;
                        }
                    }

                    last_end = i+1;
                }
            }
            // Specifically for the last argument (where there's no space and there's only the end of the string)
            ARGS[ARGCOUNT] = s_line.substr(last_end, last_end-s_line.length()-1);
            ARGCOUNT++;

            // get the instruction name, then make it lowercase for easier usage
            action = ARGS[0];
            transform(action.begin(), action.end(), action.begin(), ::tolower);

            // find the args (but as a string), mainly used for logging
            int temp0 = s_line.find_first_of(' ');
            argstr = "";
            if (temp0 < s_line.length()) {
                argstr = s_line.substr(temp0+1, s_line.length()-1);
            }

            return 0;
        }

        // Execute a single PinsaScript instruction
        int exec(string line) {
            // parse instruction
            parse(line);
            
            // this one is used for return codes (it's rt as in ReTurn)
            int rt = 0;


            // after obtaining all this info, we can finally interpret the line
            //TODO: some instructions use the same code, I wonder If I can unite them in a function
            if (action == "notice") {
                // tell the user something and wait for it to hit the CONFIRM key
                cout << "NOTICE: " << argstr << "\n";
                ps_w_misc.waitForUser();

            } else if (action == "log") {
                // show a simple message on screen
                cout << "LOG: " << argstr << "\n";

            } else if (action == "download") {
                // download a file from the internet
                if (ARGCOUNT == 3) { // check if there are enough arguments
                    try {
                        rt = ps_w_misc.download(ARGS[1], dirconv(ARGS[2]));
                    } catch (...) {
                        return ps_errs.GENERIC_ERROR;
                    }
                } else if (ARGCOUNT < 3) {
                    return ps_errs.NOT_ENOUGH_ARGUMENTS; // not enough arguments
                } else {
                    return ps_errs.TOO_MANY_ARGUMENTS;
                }

            } else if (action  == "copy") {
                //TODO: test this with OUT: and TEMP:
                if (ARGCOUNT == 3) {
                    if (!filesystem::is_directory(ARGS[1]) ) {
                        if (filesystem::is_directory(ARGS[2])) {
                            try {
                                filesystem::copy(ARGS[1], ARGS[2]);
                            } catch (...) {
                                return ps_errs.CANNOT_COPY; // unable to copy file
                            }
                        } else {
                            return ps_errs.NOT_A_DIRECTORY; // not a directory
                        }
                    } else {
                        return ps_errs.IS_DIRECTORY; // is a directory (please anything but a directory)
                    }
                } else if (ARGCOUNT < 3) {
                    return ps_errs.NOT_ENOUGH_ARGUMENTS;
                } else if (ARGCOUNT > 3) {
                    return ps_errs.TOO_MANY_ARGUMENTS;
                }

            } else if (action == "delete" || action == "rm") {
                if (ARGCOUNT >= 2) {
                    for (int i = 0; i < ARGCOUNT; i++) {
                        rt = comFileFun(ARGS[i]);

                        if (rt == 0) {
                            try {
                                filesystem::remove(ARGS[i]);
                            } catch (...) {
                                return ps_errs.GENERIC_ERROR;
                            }
                        } else {
                            break;
                        }
                    }
                } else {
                    return ps_errs.NOT_ENOUGH_ARGUMENTS;
                }

            } else if (action == "newdir" || action == "mkdir") {
                if (ARGCOUNT >= 2) {
                    for (int i = 1; i < ARGCOUNT; i++) {
                        if (!filesystem::exists(ARGS[i])) {
                            try {
                                filesystem::create_directory(ARGS[i]);
                            } catch (...) {
                                return ps_errs.GENERIC_ERROR;
                            }
                        } else {
                            return ps_errs.DIRECTORY_EXISTS;
                        }
                    }
                } else {
                    return ps_errs.NOT_ENOUGH_ARGUMENTS;
                }

            } else if (action == "trynewdir" || action == "trymkdir") {
                if (ARGCOUNT >= 2) {
                    for (int i = 1; i < ARGCOUNT; i++) {
                        ps_misc.trymkdir(ARGS[i]);
                    }
                } else {
                    return ps_errs.NOT_ENOUGH_ARGUMENTS;
                }

            } else if (action == "copydir") {
            } else if (action == "deldir" || action == "rmdir") {
                if (ARGCOUNT >= 2) {
                    for (int i = 1; i < ARGCOUNT; i++) {
                        if (filesystem::exists(ARGS[i])) {
                            if (filesystem::is_empty(ARGS[i])) {
                                filesystem::remove(ARGS[i]);
                            } else {
                                return ps_errs.DIRECTORY_NOT_EMPTY;
                            }
                        } else {
                            return ps_errs.DIRECTORY_NOT_FOUND;
                        }
                    }
                } else {
                    return ps_errs.NOT_ENOUGH_ARGUMENTS;
                }

            } else if (action == "trydeldir" || action == "tryrmdir") {
                // Actually I don't think I needed any additional function
                if (ARGCOUNT >= 2) {
                    for (int i = 1; i < ARGCOUNT; i++) {
                        ps_misc.tryrm(ARGS[i]);
                    }
                } else {
                    return ps_errs.NOT_ENOUGH_ARGUMENTS;
                }

            } else if (action == "rdeldir" || action == "rrmdir") {
                // My current C++ skills can't make this any shorter
                if (ARGCOUNT >= 2) {
                    for (int i = 1; i < ARGCOUNT; i++) {
                        rt = comDirFun(ARGS[i]);

                        if (rt == 0) {
                            try {
                                filesystem::remove_all(ARGS[i]);
                            } catch (...) {
                                return ps_errs.GENERIC_ERROR;
                            }
                        } else {
                            break;
                        }
                    }
                } else {
                    return ps_errs.NOT_ENOUGH_ARGUMENTS;
                }
            } else if (action == "extract") { // This is going to be hard to implement (If I don't find a library for it) (oh boy)
            } else if (action == "attryn") {
            } else if (action == "attrsel") {
            } else if (action == "attrmsel") {
            } else if (action == "addattr") {
                if (ARGCOUNT > 1) {
                    for (int i = 1; i < ARGCOUNT; i++) {
                        rt = add_attr(ARGS[i]);
                        cout << ARGS[i] << "\n";
                        if (rt != 0) {
                            return rt;
                        }
                    }
                } else {
                    return ps_errs.NOT_ENOUGH_ARGUMENTS;
                }

            } else if (action == "remattr") {
                if (ARGCOUNT > 1) {
                    for (int i = 1; i < ARGCOUNT; i++) {
                        rt = del_attr(ARGS[i]);
                        if (rt != 0) {
                            return rt;
                        }
                    }
                } else {
                    return ps_errs.NOT_ENOUGH_ARGUMENTS;
                }

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


            return rt;
        }

        // Adds an attribute to the attribute list. No effect if the attribute existed already.
        int add_attr(string attr) {
            if (ATTRCOUNT < LIBPS_ATTR_LIMIT) {
                int putattrin = -1;
                bool existed = false;
                for (int i = 0; i < LIBPS_ATTR_LIMIT; i++) {
                    if (ATTRLIST[i] == "") {
                        putattrin = i; // hold on, we don't know if the attr already exists somewhere else
                    }

                    if (ATTRLIST[i] == attr) {
                        existed = true;
                        break;
                    }
                }

                if (putattrin != -1 && !existed) {
                    ATTRLIST[putattrin] = attr;
                    ATTRCOUNT++;
                } else if (existed) {
                    ;
                } else {
                    // No idea how you could end up here but here's a handler anyway
                    return ps_errs.GENERIC_ERROR;
                }
            } else {
                return ps_errs.ATTR_LIMIT_REACHED;
            }

            return 0;
        }

        int del_attr(string attr) {
            for (int i = 0; i < LIBPS_ATTR_LIMIT; i++) {
                if (ATTRLIST[i] == attr) {
                    ATTRLIST[i] = "";
                    ATTRCOUNT--;
                    return 0;
                }
            }

            return ps_errs.ATTR_NOT_FOUND;
        }
    
    // Seeing a ton of repeated code, wanted to make some functions to lighten source.
    // Is it over-engineered? Probably, I don't know.
    //private:
        // com mon
        // Dir ectory
        // Fun ction.
        int comDirFun(string path__, bool requireEmpty = false) {
            if (filesystem::exists(path__)) {
                if (filesystem::is_directory(path__)) {
                    if (filesystem::is_empty(path__) || !requireEmpty) {
                        return 0;
                    }
                } else {
                    return ps_errs.NOT_A_DIRECTORY;
                }
            } else {
                return ps_errs.DIRECTORY_NOT_FOUND;
            }

            return 0;
        }

        // com mon
        // File
        // Fun ction.
        int comFileFun(string path__) {
            if (ARGCOUNT >= 2) {
                for (int i = 1; i < ARGCOUNT; i++) {
                    if (filesystem::exists(ARGS[i])) {
                        if (filesystem::is_regular_file(ARGS[i])) {
                            return 0;
                        } else {
                            return ps_errs.NOT_A_REGULAR_FILE;
                        }
                    } else {
                        return ps_errs.FILE_NOT_FOUND;
                    }
                }
            } else {
                return ps_errs.NOT_ENOUGH_ARGUMENTS;
            }

            return 0;
        }
};