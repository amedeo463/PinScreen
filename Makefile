# This makefile will compile binaries for all currently supported platforms #

PREFIX = builds/PinScreen-
REQUESTS_C = ./libpinsc/cpr
TEMP = ./temp

# All things that need to be built
BUILD_TARGETS = $(PREFIX)linux-x86_64 \
                $(PREFIX)windows-x86_64.exe
#

# Main
all: prepwork
	@echo Nothing left to do, quitting
#


## Building preparations ##
prepwork: main.cpp ./libpinsc $(TEMP) ./builds/
	@$(MAKE) $(BUILD_TARGETS)

# Create temporary folder
$(TEMP):
	@echo Creating temp folder
	@mkdir $(TEMP)
#

# Download and modify requests.c (NOT USED ANYMORE)
#$(REQUESTS_C):
#	@echo Downloading requests.c library
#	@git clone https://github.com/mactul/requests.c.git $(REQUESTS_C)
#	
#	@# Oh dear (remove the .git folder as it's useless)
#	@rm -rf $@/.git
#
#	@sed -i'' -e 's/defined(_WIN32) || defined(WIN32)/defined(WINDOWS)/g' $(REQUESTS_C)/*.c
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
$(PREFIX)$(1):
	@echo building for platform $(3)
	@$(4) main.cpp -o $$@ -D $(2) -static -lcurl
#

# NOT USED ANYMORE #
## Link library together
#$(TEMP)/$(3)/requests.a: $(TEMP)/$(3)/requests.o $(TEMP)/$(3)/utils.o $(TEMP)/$(3)/easy_tcp_tls.o $(TEMP)/$(3)/parser_tree.o
#	@echo linking into $$@
#	@ar cr $$@ $$^
##
## Compile C files into objects
#
#SOURCES = $(wildcard $(REQUESTS_C)/*.c)                             # AI made these two lines, and somehow made the makefile run
#OBJECTS = $(patsubst $(REQUESTS_C)/%.c,$(TEMP)/$(3)/%.o,$(SOURCES)) # I'm not going to touch them until I find out how they work
#
#$(TEMP)/$(3)/%.o: $(REQUESTS_C)/%.c
#	@mkdir -p $(TEMP)/$(3)/
#	@echo Compiling $$^ to $$@
#	@$(5) -c $$^ -o $$@ -Wall -Wextra -pedantic -O3 -DNDEBUG -D $(2) -I $(REQUESTS_C)/
##
# #
endef
#

# Build macro calls for each build
$(eval $(call BUILD_BIN,linux-x86_64,LINUX,linux-x86_64,x86_64-linux-gnu-g++,x86_64-linux-gnu-gcc))
$(eval $(call BUILD_BIN,windows-x86_64.exe,WINDOWS,windows-x86_64,x86_64-w64-mingw32-g++-posix,x86_64-w64-mingw32-gcc-posix))
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

# Clean build folder and rebuild
rebuild: buildcleanup
	@echo rebuilt binaries succesfully
#
# Clean build folder and temp folder and rebuild from scratch
fullrebuild: cleanup rebuild
	@$(MAKE)
#
# Reset repo to its original state and rebuild from scratch
fullestrebuild: libcleanup fullrebuild
	@$(MAKE)
#
## ##


# phony targets
.PHONY: cleanup buildcleanup libcleanup fullcleanup all prepwork rebuild fullrebuild fullestrebuild
#