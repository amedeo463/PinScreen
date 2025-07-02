// Header file containing common functions for ALL platforms.

#include <iostream>
#include <string>
#include <bits/stdc++.h>

using namespace std;

// error codes.
struct ps_errs_ {
    int UNKNOWN_INSTRUCTION = -1;
    int NOT_ENOUGH_ARGUMENTS = -2;
    int SCRIPT_STOPPED = -3;
    int SCRIPT_STOPPED_ERROR = -4;
    int CANNOT_COPY = -5;
    int ACCESS_DENIED = -6;
    int FILE_EXISTS = -7;
    int DIRECTORY_NOT_EMPTY = -8;
} ps_errs;

// Argument limit for PinsaScript instructions.
const int LIBPS_ARG_LIMIT = 128;

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
};