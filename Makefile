# This makefile will compile binaries for all currently supported platforms #

PREFIX = builds/PinScreen-
REQUESTS_C = ./libpinsc/requests.c
TEMP = ./temp

COMPILER = 
OS_CLASS = 
PLATFORM = 


# Main
all: prepwork $(PREFIX)Linux-x86_64 $(PREFIX)Windows.exe
	@echo Nothing left to do, quitting
#


## Building preparations ##
prepwork: main.cpp ./libpinsc temp $(REQUESTS_C)

# Create temporary folder
temp:
	@echo Creating temp folder
	@mkdir temp
#

# Download and modify requests.c
#TODO: automate the process of modifying source code to make it ad-hoc for the library
$(REQUESTS_C):
	@echo Downloading requests.c library
	@git clone https://github.com/mactul/requests.c.git $(REQUESTS_C)
	
	@# Oh dear (remove the .git folder as it's useless)
	@rm -rf $@.git
#
## ##


## Build targets ##
#TODO: Add support for FreeBSD and maybe OpenBSD and NetBSD. Also add support for TON of architectures.

# Linux
$(PREFIX)Linux-x86_64: COMPILER = x86_64-linux-gnu-g++ \
                       OS_CLASS = LINUX \
                       PLATFORM = Linux-x86_64
					   EXT = 
#
# Windows
$(PREFIX)Windows.exe: COMPILER = x86_64-w64-mingw32-g++-posix \
                      OS_CLASS = WINDOWS \
                      PLATFORM = Windows
					  EXT = .exe
#

# Common script for building all PC builds
$(PREFIX)%$(EXT): $(TEMP)/$(PLATFORM)/requests.a
	@echo building for platform $(PLATFORM)...
	@$(COMPILER) main.cpp $^ -o $@ -D $(OS_CLASS) -static
#

## ##

## Other targets ##
# Remove temp data
cleanup:
	@echo Removing temp data
	@rm -rf $(TEMP)/*
#

# Link library
$(TEMP)/%/requests.a: $(TEMP)/%/requests.o $(TEMP)/%/utils.o $(TEMP)/%/easy_tcp_tls.o $(TEMP)/%/parser_tree.o
	@mkdir $(@D)
	@echo linking into $@
	@ar cr $@ $^
#

# Compile C files into objects
$(TEMP)/$(PLATFORM)/%.o: $(REQUESTS_C)/%.c
	@sed -i 's/defined(_WIN32) || defined(WIN32)/defined(WINDOWS)/g' $^
	@echo Compiling $^ to $@
	@$(COMPILER) -c $^ -o $@ -Wall -Wextra -pedantic -O3 -DNDEBUG -I $(REQUESTS_C)
#
## ##