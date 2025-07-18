# This makefile will compile binaries for all currently supported platforms #
# LINUX ONLY #

PREFIX = builds/PinScreen-
#REQUESTS_C = ./libpinsc/cpr
TEMP = ./temp
MAIN_CPP = ./main.cpp
LIBS = ./libs
LIBSOURCES = ./libsrc

# All things that need to be built
BUILD_TARGETS = $(PREFIX)linux-x86_64 \
                $(PREFIX)windows-x86_64.exe
#

# Main
all: prepwork
	@echo Nothing left to do, quitting
#


## Building preparations ##
prepwork: $(MAIN_CPP) ./libpinsc $(TEMP) ./builds/ $(LIBS) $(LIBSOURCES) libdownload
	@$(MAKE) $(BUILD_TARGETS)

# Create temporary folder
$(TEMP):
	@echo Creating temp folder
	@mkdir $(TEMP)

# Create builds folder
./builds/:
	@echo Creating builds folder
	@mkdir $(@D)

# Create library folder
$(LIBS):
	@echo Creating library folder
	@mkdir $@

$(LIBSOURCES):
	@echo Creating library sources folder
	@mkdir $@

libdownload: $(LIBSOURCES)/libcurl

$(LIBSOURCES)/libcurl:
	@echo Downloading libcurl
	@git clone https://github.com/curl/curl.git $@
	@echo Generating configure file
	@pwd
	sh ./libconfigen.sh
##


## Build targets ##
#TODO: Add support for FreeBSD and maybe OpenBSD and NetBSD. Also add support for TON of architectures.
# Build macro
define BUILD_BIN
# $(1): final part of the file
# $(2): OS class 
# $(3): OS with architecture
# $(4): additional flags

# Build binary
$(PREFIX)$(1): $(LIBS)/$(3)/libcurl
	@echo building for platform $(3)
	@$(3)-g++ $(MAIN_CPP) -o $$@ -D $(2) -lcurl $(4)
#

$(LIBS)/$(3)/libcurl: $(LIBS)/$(3) $(LIBSOURCES)/libcurl
	@echo building libcurl for $(3)
	@$(LIBSOURCES)/libcurl/configure --host=$(3) --with-openssl
	@cmake -S $(LIBSOURCES)/libcurl -B $$@ 

$(LIBS)/$(3):
	@mkdir $$@
	@mkdir $$@/libcurl
endef

# Build macro calls for each build
$(eval $(call BUILD_BIN,linux-x86_64,LINUX,x86_64-linux-gnu,$(curl-config --static-libs) -I/usr/include/x86_64-linux-gnu,))
$(eval $(call BUILD_BIN,windows-x86_64.exe,WINDOWS,windows-x86_64,x86_64-w64-mingw32-g++-posix,))
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
	@echo Clearing build folder
	@rm -rf builds/*
#

libcleanup:
	@echo Clearing libs folder
	@rm -rf $(LIBS)/*
# do all
fullcleanup: cleanup buildcleanup
#

# Clean build folder and rebuild
rebuild: buildcleanup all
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

debug: $(TEMP)
	@echo Building debug console
	@g++ debug.cpp -lcurl -o ./temp/ps-debug -I/usr/include/x86_64-linux-gnu
## ##


# phony targets
.PHONY: cleanup buildcleanup libcleanup fullcleanup all prepwork rebuild fullrebuild fullestrebuild debug libdownload
#