// Header file containing common functions and constants for ALL platforms.

#include <iostream>
#include <string>
#include <bits/stdc++.h>

using namespace std;

// error codes.
struct ps_errs_ {
    int UNKNOWN_INSTRUCTION  = -1;
    int NOT_ENOUGH_ARGUMENTS = -2;
    int SCRIPT_STOPPED       = -3;
    int SCRIPT_STOPPED_ERROR = -4;
    int CANNOT_COPY          = -5;
    int ACCESS_DENIED        = -6;
    int FILE_EXISTS          = -7;
    int DIRECTORY_NOT_EMPTY  = -8;
    int FILE_NOT_FOUND       = -9;
    int DIRECTORY_NOT_FOUND  = -10;
    int DOWNLOAD_FAIL        = -11;
    int DOWNLOAD_SAVE_FAIL   = -12;
    int TOO_MANY_ARGUMENTS   = -13;
    int NOT_A_REGULAR_FILE   = -14;
    int NOT_A_DIRECTORY      = -15;
    int IS_DIRECTORY         = -16;
    int ATTR_LIMIT_REACHED   = -17;
    int ATTR_NOT_FOUND       = -18;

    int GENERIC_ERROR = -1000000;
} ps_errs;

// Argument limit for PinsaScript instructions.
const int LIBPS_ARG_LIMIT = 128;

// Maximum attributes for scripts.
const int LIBPS_ATTR_LIMIT = 256;

class _misc {
    public:
        string strip(string line) {
            //// 1. strip the instruction
            int cmdstart = 0, cmdend = line.length()-1;
            /// 1.1 find bounds
            // 1.1.1 find start
            while (line[cmdstart] == ' ') {
                cmdstart++;
            }
            // 1.1.2 find end
            while (line[cmdend] == ' ') {
                cmdend--;
            }
            cmdend++;
            /// 1.2 strip the thing and return
            return line.substr(cmdstart, cmdend-cmdstart);
        }
    
    void trymkdir(string path__) {
        // Creates a directory if it does not exist
        if (!filesystem::exists(path__)) {
            filesystem::create_directory(path__);
        }  
    }

    void tryrm(string path__) {
        // removes a file or an empty diretory if it exists
        if (filesystem::exists(path__)) {
            filesystem::remove(path__);
        }
    }

    void tryrrmdir(string path__) {
        // removes a directory and its contents, recursively
        if (filesystem::exists(path__)) {
            filesystem::remove_all(path__);
        }
    }
};