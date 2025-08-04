# PinScreen
The C++ successor of PScrInt, still a really big WIP.

## Building
### Building requirements
- a GNU/Linux system (I think you can use MSYS2 on Windows, but I'm not going to test that) with the following packages and the corresponding dependencies:
  - curl
  - libcurl4-openssl-dev
  - libpsl-dev
  - g++-x86-64-linux-gnu
  - g++-mingw-w64-x86-64
  - make
  - libtool

Why these g++ cross-compilers in particular?
Well... The list is going to grow a lot more in the future.

### Actually building the thing

Building is possible only for GNU/Linux on x86-64 at the moment.

All you have to do is run `make` in the root of the repo.

Do not worry if it fails to find `openssl/ssl.h`, that means it tried to compile for Windows,
although it should already have made a build for Linux on x86-64 at that point

## Goals to reach:
- Add support for a REALLY amount of CPU architectures (even the shadier ones like MIPS, just for the sake of supporting a lot of devices)
- Add support for Windows, Linux and various BSD-based operating systems
  - Actually finish a build for Linux on x86-64
- Add console support, mainly 3DS and Wii U
- Actually finishing the project and maintaining it (see TODO section to see what I have to do)
- Make a guide on how to use PinsaScript (the language this software is meant to interpret)
- Make an independent repo for libpinsc
- Use libpinsc to make a PinsaScript compiler (could call it PinComp or something)

## TODO:
- Implement all instructions I previously implemented on PScrInt
  - NOTICE [DONE]
  - LOG [DONE]
  - DOWNLOAD [DONE]
  - COPY [DONE]
  - DELETE [done, untested]
  - NEWDIR [done, untested]
  - COPYDIR
  - DELDIR
  - RDELDIR
  - EXTRACT
  - ATTRYN
  - ATTRSEL
  - ATTRMSEL
  - ADDATTR [DONE]
  - REMATTR [DONE]
  - STOP [DONE]
  - ESTOP [DONE]
  - NOTHING [DONE]
- Implement aliases and new commands that were not in PScrInt
  - mkdir (newdir alias) [DONE]
  - trynewdir [done, untested]
  - trymkdir [DONE]
  - rmdir (deldir alias) [DONE]
  - trydeldir [WIP]
  - tryrmdir (trydeldir alias) [DONE]
  - rrmdir (rdeldir alias) [DONE]
  - rm (delete alias) [DONE]
- Implement script execution
  - Implement sections from PScrInt (parts of code that are executed only with certain attributes)
    - Implement attributes [DONE]
    - Implement multi-line execution
      - Implement single line execution [DONE]
        - Implement parsing [DONE]
- Implement script download
- Fix openssl/ssl.h with windows issue
  - implement openssl compilation from makefile
  - update makefile to automatically compile libcurl from source
    - Automatically download libcurl
- Implement platform restriction for scripts (A script could specify for what platform it was made - If such is attempted to be run on another platform, PinScreen will refuse to execute it)
- Make a main menu, either GUI or TUI (or both perhaps) (4th August 2025 update: actually GUI might be better)
  - Implement GUI (this will allow me to actually implement attryn, attrsel and attrmsel)
- interactions via console (for automation compatibility)


- Fix the makefile [DONE]
- Implement temp and output directory [DONE]

# Other notes
4th August 2025 (#1): I apologize for making no progress in a month
4th August 2025 (#2): Actually, I might have to compile OpenSSL from source via makefile