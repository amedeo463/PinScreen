/////////////// 
//  ___ ___  // PinScreen
// | _ |  _| // a PinsaScript interpreter
// |  _|_  | // Ver. 1.0
// |_| |___| // Written by amedeo463 
//           // Protected under CC BY-SA 4.0 International
/////////////// 

// iostream was already included in common.hpp
#include "libpinsc/main.hpp"
#include "headers/loopmanage.hpp"

using namespace std;
libps_class__ libps;


// the structure looks like this because of future game console support
int main() {
    init();

    while (loopCond()) {
        beforeIter();

        // I'm using the function below to test instructions
        int returncode = libps.exec("copy temp/aaa temp/a");
        cout << "Returned " << returncode << "\n";

        DO_QUIT_ACTION = true;
        
        afterIter();
        if (DO_QUIT_ACTION) {
            break;
        }
    }

    doExitAction();
    return 0;
}