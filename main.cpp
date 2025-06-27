/////////////// 
//  ___ ___  // PinScreen
// |   |  _| // a PinsaScript interpreter
// |  _|_  | // Ver. 1.0
// |_| |___| // Written by amedeo463 
//           // Protected under CC BY-SA 4.0 International
/////////////// 

// iostream was already included in common.hpp
#include "libpinsc/main.hpp"

using namespace std;
libps_class__ libps;

int main() {
    // I'm using the function below to test instructions
    int returncode = libps.exec("stop FUCK YOU!");
    cout << "Returned " << returncode << "\n";
    return 0;
}