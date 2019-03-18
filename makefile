CFLAGS =
CXXFLAGS = -Wpedantic -Wall -Wextra -Wno-deprecated -Wno-deprecated-declarations -ggdb -std=c++11
CPPFLAGS = -DSFML
LDFLAGS = -static-libstdc++
LDLIBS = -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio -lsfml-network

# source directory
SRC := src

# where to find additional c++ source and header files
# make sure to use the $(SLASH) variable for the directory seperator if
# a subdirectory is included
# example: dir$(SLASH)nextdir
cppdirs = 

# output directory
BUILD := build

# name of output program
program = DerangedFarmer


# autodetect os
OSTARGET ?= UNKNOWN

ifeq ($(OSTARGET),UNKNOWN)
	ifeq ($(OS),Windows_NT)
		OSTARGET := WINDOWS
	else
		UNAME := $(shell uname -s)
		ifeq ($(UNAME),Linux)
			OSTARGET := LINUX
		endif
		ifeq ($(UNAME),Darwin)
			OSTARGET := MACOSX
		endif
	endif
endif

ifeq ($(OSTARGET),LINUX)
	# OS specific options
	CFLAGS +=
	CXXFLAGS += -I/usr/include $(addprefix -I,$(INCDIRS))
	CPPFLAGS +=
	LDFLAGS += -L/usr/lib
	LDLIBS +=
	RM := rm -f
	RMDIR := rm -rf
	MKDIR := mkdir -p
	SLASH = /
	CP := cp
	PREFIX ?= /usr/local

	# compiler/linker programs
	CC := gcc
	CPP := g++
	LD := g++

	# extension of output program
	#program +=
endif
ifeq ($(OSTARGET),MACOSX)
	# OS specific options
	CFLAGS +=
	CXXFLAGS += -I/usr/include $(addprefix -I,$(INCDIRS))
	CPPFLAGS +=
	LDFLAGS += -L/usr/lib
	LDLIBS +=
	RM := rm -f
	RMDIR := rm -rf
	MKDIR := mkdir -p
	CP := cp
	SLASH = /
	PREFIX ?= /usr/local

	# compiler/linker programs
	CC := gcc
	CPP := g++
	LD := g++

	# extension of output program
	#program +=
endif
ifeq ($(OSTARGET),WINDOWS)
	# OS specific options
	CFLAGS +=
	CXXFLAGS += -Iinclude $(addprefix -I,$(INCDIRS))
	CPPFLAGS +=
	LDFLAGS += -Llib
	LDLIBS += -lmingw32
	RM := del /F/Q
	RMDIR := rmdir /S/Q
	MKDIR := mkdir
	CP := robocopy
	SLASH = \\
	PREFIX ?=

	# compiler/linker programs
	CC := gcc
	CPP := g++
	LD := g++

	# extension of output program
	program := $(addsuffix .exe,$(program))
endif

INCDIRS = $(SRC) $(addprefix $(SRC)/,$(cppdirs))
VPATH = $(INCDIRS)
cppsrc = $(wildcard $(SRC)/*.cpp $(addsuffix /*.cpp,$(INCDIRS)))
objects = $(patsubst $(SRC)/%.o,$(BUILD)/%.o,$(cppsrc:.cpp=.o))
depends = $(objects:.o=.d)
DESTDIR =

all: $(BUILD)/$(program)
	@echo build complete!

$(BUILD)/$(program): $(objects)
	@$(LD) -o $@ $^ $(LDFLAGS) $(LDLIBS)
	@echo linking $^ into $@ using these libraries $(LDLIBS)

$(BUILD)/%.o: %.cpp
	@$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@
	@echo compiling $< to $@

$(objects) $(depends): | $(BUILD)

$(BUILD):
	@$(MKDIR) $(BUILD) $(addprefix $(BUILD)$(SLASH),$(cppdirs))
	@echo creating directories

# rule to generate a dependency file
$(BUILD)/%.d: %.cpp
	@$(CPP) $(CXXFLAGS) $< -MM -MT $(@:.d=.o) >$@
	@echo generating dependencies for $<

# include all dependency files in the makefile
-include $(depends)

.PHONY: clean install uninstall
clean:
#	$(RM) $(subst /,$(SLASH),$(objects)) $(subst /,$(SLASH),$(depends)) $(subst /,$(SLASH),$(BUILD)/$(program))
	@echo cleaning...
	@$(RMDIR) $(BUILD)
	@echo done.

install: $(BUILD)/$(program)
ifeq ($(OSTARGET),WINDOWS)
	-$(CP) /S $(BUILD) $(DESTDIR)$(PREFIX)bin $(program)
	-$(CP) /S data $(DESTDIR)$(PREFIX)bin$(SLASH)data
	-$(CP) ./ $(DESTDIR)$(PREFIX)bin *.dll
else
	$(MKDIR) $(DESTDIR)$(PREFIX)/bin/$(program)
	$(CP) $< $(DESTDIR)$(PREFIX)/bin/$(program)
	$(CP) -r ./data $(DESTDIR)$(PREFIX)/bin/$(program)
endif

uninstall:
ifeq ($(OSTARGET), WINDOWS) 
	$(RMDIR) $(DESTDIR)$(PREFIX)/bin
else 
	$(RMDIR) $(DESTDIR)$(PREFIX)$(SLASH)bin$(SLASH)$(program)
endif
