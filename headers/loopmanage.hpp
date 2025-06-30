// different functions for the mainloop in ../main.cpp

bool DO_QUIT_ACTION = false;

#if defined(WINDOWS) || defined(LINUX) || defined(BSD)
#define DEFAULT_PLATFORM
#elif defined(N3DS)
#include <3ds.h>
#elif defined(WIIU)

#else
#define DEFAULT_PLATFORM
#endif


// default
#if defined(DEFAULT_PLATFORM)
void init() {}
void beforeIter() {}
void afterIter() {}

bool loopCond() {
    return true;
}

void doExitAction() {}
#endif