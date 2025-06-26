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
    libps.exec("log hi, I'm working fine");
    return 0;
}