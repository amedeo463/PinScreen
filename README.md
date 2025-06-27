# PinScreen
The C++ successor of PScrInt, still a really big WIP.

## Building
You are on your own on this one. To make a build, you must compile the given requests.c to a static library, then
you must compile main.cpp with the library we just compiled.

Building with make is possible only for linux on x86-64 at the moment, I broke the makefile while trying to make the building process
more modular.

You must run the makefile at the root of the repo twice (I'll fix that later) to build for linux on x86-64

## Goals to reach:
- Add support for a REALLY amount of CPU architectures (even the shadier ones like MIPS, just for the sake of supporting a lot of devices)
- Add support for Windows, Linux and various BSD-based operating systems
- Add console support, mainly 3DS and Wii U
- Actually finishing the project and maintaining it (see TODO section to see what I have to do)
- Make a guide on how to use PinsaScript (the language this software is meant to interpret)
- Make an independent repo for libpinsc
- Use libpinsc to make a PinsaScript compiler (could call it PinComp or something)

## TODO:
- Fix the makefile
- Implement all commands I previously implemented on PScrInt
  - NOTICE [DONE]
  - LOG [DONE]
  - DOWNLOAD [WIP]
  - COPY
  - DELETE
  - NEWDIR
  - COPYDIR
  - DELDIR
  - RDELDIR
  - EXTRACT
  - ATTRYN
  - ATTRSEL
  - ATTRMSEL
  - ADDATTR
  - REMATTR
  - STOP [DONE]
  - ESTOP [DONE]
  - NOTHING [DONE]
- Implement script execution
- Implement script download
- Implement sections from PScrInt (parts of code that are executed only with certain attributes)
- Implement attributes
- Implement platform restriction for scripts (A script could specify for what platform it was made - If such is attempted to be run on another platform, PinScreen will refuse to execute it)
