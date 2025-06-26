# This makefile will compile binaries for all currently supported platforms #

PREFIX = builds/PinScreen-
REQUESTS_C = ./libpinsc/requests.c
TEMP = ./temp

# All things that need to be built
BUILD_TARGETS = $(PREFIX)linux-x86_64 \
                $(PREFIX)windows-x86_64.exe
#

# Main
all: prepwork $(BUILD_TARGETS)
	@echo Nothing left to do, quitting
#


## Building preparations ##
prepwork: main.cpp ./libpinsc temp $(REQUESTS_C) ./builds/

# Create temporary folder
temp:
	@echo Creating temp folder
	@mkdir temp
#

# Download and modify requests.c
$(REQUESTS_C):
	@echo Downloading requests.c library
	@git clone https://github.com/mactul/requests.c.git $(REQUESTS_C)
	
	@# Oh dear (remove the .git folder as it's useless)
	@rm -rf $@/.git

	@sed -i 's/defined(_WIN32) || defined(WIN32)/defined(WINDOWS)/g' $(REQUESTS_C)/*.c
#

# Create builds folder
./builds/:
	@mkdir $(@D)
## ##


## Build targets ##
#TODO: Add support for FreeBSD and maybe OpenBSD and NetBSD. Also add support for TON of architectures.
# Build macro
define BUILD_BIN
# $(1): final part of the file
# $(2): OS class 
# $(3): OS with architecture
# $(4): g++ Compiler invoke
# $(5): gcc Compiler invoke

# Build binary
$(PREFIX)$(1): $(TEMP)/$(3)/requests.a
	@echo building for platform $(3)
	@$(4) main.cpp $$^ -o $$@ -D $(2) -static
#
# Link library together
$(TEMP)/$(3)/requests.a: $(TEMP)/$(3)/requests.o $(TEMP)/$(3)/utils.o $(TEMP)/$(3)/easy_tcp_tls.o $(TEMP)/$(3)/parser_tree.o
	@echo linking into $$@
	@ar cr $$@ $$^
#
# Compile C files into objects
$(TEMP)/$(3)/%.o: $(REQUESTS_C)/%.c
	@mkdir -p $(TEMP)/$(3)/
	@echo Compiling $$^ to $$@
	@$(5) -c $$^ -o $$@ -Wall -Wextra -pedantic -O3 -DNDEBUG -D $(2) -I $(REQUESTS_C)/
#
endef
#

# Build macro calls for each build
$(eval $(call BUILD_BIN,linux-x86_64,LINUX,linux-x86_64,x86_64-linux-gnu-g++,linux-x86_64,x86_64-linux-gnu-gcc))
$(eval $(call BUILD_BIN,windows-x86_64.exe,WINDOWS,windows-x86_64,x86_64-w64-mingw32-g++-win32,x86_64-w64-mingw32-gcc-win32))
#
## ##

## Other targets ##
# Remove temp data
cleanup:
	@echo Removing temp data
	@rm -rf $(TEMP)/*
#
# Remove builds in build folder
buildcleanup:
	@echo Cleaning build folder
	@rm -rf builds/*
#
# Remove requests.c repo
libcleanup:
	@echo Removing requests.c from libpinsc folder
	@rm -rf $(REQUESTS_C)
#
# do all
fullcleanup: cleanup buildcleanup libcleanup
#

## ##


# phony targets
.PHONY: cleanup buildcleanup libcleanup fullcleanup all prepwork
#