// Header file containing common functions across ALL platforms.

#include <iostream>
#include <string>
#include <bits/stdc++.h>

using namespace std;

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