// Debugging console I use to test instructions.
// version code 02

#define LINUX

#include "libpinsc/main.hpp"
#include "headers/extra.hpp"

using namespace std;

libps_class__ libps;

int main() {
    string comm, action;
    int code;

    libps.OUTDIR = "./temp/out";
    libps.TEMPDIR = "./temp/temp";

    trymkdir(libps.OUTDIR);
    trymkdir(libps.TEMPDIR);

    cout << "libpinsc debug console.\nuse 'help' for help.\n";
    while (true) {
        // Prompt
        cout << ">> ";
        getline(cin, comm);

        libps.parse(comm);
        if (libps.action == "help") {
            cout << "This is a debug console made to test features.\n";
            cout << "You can use all PinsaScript instructions here, along with some\n";
            cout << "Specific commands that can only be used here:\n";
            cout << " help      Show this.\n";
            cout << " getattrs  print out all attrs\n";
            cout << " exit      exit the console\n";
        } else if (libps.action == "getattrs"){
            for (int i = 0; i < LIBPS_ATTR_LIMIT; i++) {
                if (libps.ATTRLIST[i] != "") {
                    cout << libps.ATTRLIST[i] << " ";
                }
            }

            if (libps.ATTRCOUNT > 0) {
                cout << "\nThat's " << libps.ATTRCOUNT << " attributes in total.\n";
            } else {
                cout << "No attributes have been declared yet.\n";
            }
        } else if (libps.action == "exit") {
            break;
        } else {
            // If flow ends up here, then it was not a debug command.
            // Instead it assumes the prompt was a pinsascript instruction.
            code = libps.exec(comm);
            cout << "Returned " << code << "\n";
        }
    }

    return 0;
}