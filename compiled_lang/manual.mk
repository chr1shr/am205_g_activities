# *************************************************************************************************
# Harvard Applied Math 205 - Fall 2021.
# Simple manual makefile
# *************************************************************************************************

# *************************************************************************************************
# Detect Operating System
# *************************************************************************************************

# Is the OS Linux?
ifeq ($(shell uname), Linux)
	detected_OS := Linux
endif

# Is the OS Windows?
ifeq ($(OS), Windows_NT)
    detected_OS := Windows
endif

# Is the OS Mac?
ifeq ($(shell uname), Darwin)
    detected_OS := Mac
endif

# *************************************************************************************************
# Configuration options
# *************************************************************************************************

# Make settings: warn on unset variables, use parallel processing
# MAKEFLAGS+=--warn-undefined-variables -j
MAKEFLAGS+=-j

# Directory layout
SRC_DIR := src
OBJ_DIR := obj
EXE_DIR := exec

# C++ compiler is g++ on Linux and clang++ on Mac
ifeq ($(detected_OS), Linux)
	CXX := g++
endif
ifeq ($(detected_OS), Mac)
	CXX := clang++
endif

# C++ Compilation flags
CXX_FLAGS := -std=c++20 -Wall -Wextra -Wpedantic -Werror -O3

# Additional include directories passed to compiler with -I flag
INCLUDE := 

# Add include location for MacPorts if we are on Mac OS
ifeq ($(detected_OS), Mac)
    INCLUDE += -I/opt/local/include
	INCLUDE += -I/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/System/Library/Frameworks/Accelerate.framework/Versions/Current/Frameworks/vecLib.framework/Headers/
endif

# Macros for C++ preprocessor
CXX_MACROS :=

# Library locations
LD_DIRS := 
# Add library location for MacPorts if we are on Mac OS
ifeq ($(detected_OS), Mac)
    LD_DIRS += -L/opt/local/lib
endif
# LD_DIRS += -L/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/System/Library/Frameworks/Accelerate.framework/Versions/Current/Frameworks/vecLib.framework

# Selected libraries
LD_LIBS := -lfmt -lblas -lgmp

# Combined LD_FLAGS arguments to linker - library search path and libraries
LD_FLAGS := $(strip $(LD_DIRS) $(LD_LIBS))

# *************************************************************************************************
# Collections of files and targets
# *************************************************************************************************

# All the executable targets (stem only)
TGT_EXE := \
	00_minimal 01_hello 02_data_types 03_structures 04_functions 05_pointers \
	11_c_array_auto 12_c_array_new 13_complex 14_containers 15_refs_pointers 16_pass_by_ref_ptr \
	21_pi 
# $(info TGT_EXE = $(TGT_EXE))

# Executable program files - build from targets list
EXECS := $(patsubst %, $(EXE_DIR)/%.x, $(TGT_EXE))
# $(info EXECS = $(EXECS))

# All the source files (full filename) using wildcard function
SRC_ALL := $(wildcard $(SRC_DIR)/*.cc)
# $(info SRC_ALL = $(SRC_ALL))

# All the targets (stem only)
TGT_ALL := $(patsubst src/%.cc, %, $(SRC_ALL))
# $(info TGT_ALL = $(TGT_ALL))

# All of the object files; written out as full file names with path e.g. obj/my_file.o
OBJ_ALL := $(patsubst %, obj/%.o, $(TGT_ALL))
# $(info OBJ_ALL = $(OBJ_ALL))

# *************************************************************************************************
# Convenience targets
# *************************************************************************************************

# Make conventional target "all" depend on all the executables
all: $(EXECS)

# Set phony targets
.PHONY: all clean

# Set the default goal
.DEFAULT_GOAL: all

# Target clean removes all the built executable and object files.
# Use wildcards to ensure any "orphaned" object files or executables are also deleted.
clean:
	@rm -f $(OBJ_DIR)/*.o $(EXE_DIR)/*.x

# Give help with list of makefile targets
help:
	$(info Make targets available:)
	$(info $(TAB)all       : build all executables)
	$(info $(TAB)clean     : delete all executables and object files)
	$(info $(TAB)help      : reports this help message)
	@:

# *************************************************************************************************
# Completely manual recipes to build two program (teaching purposes only!)
# *************************************************************************************************

# # Build 00_minimal executable program
# exec/00_minimal.x: src/00_minimal.cc
# 	$(CXX) src/00_minimal.cc -o exec/00_minimal.x \
# 	$(TAB) $(CXX_FLAGS) $(INCLUDE) $(CXX_MACROS) $(LD_FLAGS)

# # Build 01_hello executable program
# exec/01_hello.x: src/01_hello.cc
# 	$(CXX) src/01_hello.cc -o exec/01_hello.x \
# 	$(TAB) $(CXX_FLAGS) $(INCLUDE) $(CXX_MACROS) $(LD_FLAGS)

# *************************************************************************************************
# Manually list extra dependencies for executables that have them in rule specific variables
# *************************************************************************************************
exec/04_functions.x : LINK_OBJ = obj/sqrt_iter.o
exec/05_pointers.x  : LINK_OBJ = obj/matrix_mult.o obj/Timer.o

# *************************************************************************************************
# Static pattern rules
# *************************************************************************************************
# Static pattern rule to compile source files into object files
$(OBJ_ALL) : $(OBJ_DIR)/%.o : $(SRC_DIR)/%.cc
	$(CXX) -c $< -o $@ $(CXX_FLAGS) $(INCLUDE) $(CXX_MACROS)

# Define the command to link an executable from its dependent object files
define CXX_LINK
	$(CXX) -o $@ $^ $(LD_FLAGS)
endef

# Static pattern rule to link each executable from its corresponding object file
.SECONDEXPANSION:
$(EXECS) : $(EXE_DIR)/%.x : $(OBJ_DIR)/%.o $$(LINK_OBJ)
	$(CXX_LINK)

# Static pattern rule that each target name depends on its sister executable file
$(TGT_ALL) : % : $(EXE_DIR)/%.x
