# *************************************************************************************************
# Harvard Applied Math 205 - Fall 2021.
# Configuration and inputs for automated Makefile.
#
# Michael S. Emanuel
# 2021-08-24
# *************************************************************************************************

# *************************************************************************************************
# Inputs - manual settings that change the most
# *************************************************************************************************

# List of all executable targets; stem only
TGT_EXE := 	\
	00_minimal 01_hello 02_data_types 03_structures 04_functions 05_pointers \
	11_c_array_auto 12_c_array_new 13_complex 14_containers 15_refs_pointers 16_pass_by_ref_ptr 

# Rule specific variables for extra dependencies
04_functions: LINK_TGT := sqrt_iter
05_pointers: LINK_TGT := matrix_mult

# Create the object files to link against from the LINK_TGT variable
$(TGT_EXE) : LINK_OBJ = patsubst(%, $(OBJ_DIR)/%.o, $(LINK_TGT))

# *************************************************************************************************
# Check the operating system.  Supported OS Linux, Windows
# *************************************************************************************************
# https://stackoverflow.com/questions/714100/os-detecting-makefile

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

# If the OS is not Linux, Windows or Mac, quit early: unsupported.
ifndef detected_OS
	$(error Unspported operating system!)
endif

# *************************************************************************************************
# Make configuration
# *************************************************************************************************

# Make settings: warn on unset variables, use parallel processing
# MAKEFLAGS+=--warn-undefined-variables -j
MAKEFLAGS+= -j

# tab character
TAB := $(shell printf "\t")

# newline charactacter
NEWLINE := $(shell printf "\n")

# *************************************************************************************************
# Set directory layout
# *************************************************************************************************

# Source directory
SRC_DIR := src

# Object directory
OBJ_DIR := obj

# Executable output directory
EXE_DIR := exec

# *************************************************************************************************
# Compiler settings
# *************************************************************************************************

# C++ compiler is g++ on Linux and clang++ on Mac
ifeq ($(detected_OS), Linux)
	CXX := g++
endif
ifeq ($(detected_OS), Mac)
	CXX := clang++
endif

# C++ Compilation flags for release and debug mode
CXX_FLAGS_COMMON := -std=c++20 -Wall -Wextra -Wpedantic -Werror
# Maximum optimization in release mode
CXX_FLAGS_RLS := $(CXX_FLAGS_COMMON) -O3
# Minimum optimization, -g flag and DEBUG macro in debug mode
CXX_FLAGS_DBG := $(CXX_FLAGS_COMMON) -O0 -g -DDEBUG=""

# Flag whether to build in debug mode; set to 1 to turn this on
DEBUG := 0

# Selected compilation type (release vs. debug)
ifeq ($(shell test $(DEBUG) -gt 0; echo $$?),0)
	CXX_FLAGS := $(CXX_FLAGS_DBG)
else
	CXX_FLAGS := $(CXX_FLAGS_RLS)
endif

# Flags to automatically generate dependencies during compilation
# Do not include -MP, just -MMD; this provides output with just the dependencies for program.o
# This type of output is compatible with the strategy for generating the linkage dependencies.
DEP_FLAGS := -MMD

# *************************************************************************************************
# Macros
# *************************************************************************************************

# Manual macros
MACROS_MANUAL :=

# Macro for top-level directory of this installation
MACRO_TOP_DIR := -DTOP_DIR="\"$(TOP_DIR)\""

# Gather all macros passed to preprocessor using -D
CXX_MACROS := $(MACROS_MANUAL)

# *************************************************************************************************
# INCLUDE: Include paths for additional software libraries 
# *************************************************************************************************

# Additional include directories passed to compiler with -I flag
INCLUDE := 

# Add include location for MacPorts if we are on Mac OS
ifeq ($(detected_OS), Mac)
    INCLUDE += -I/opt/local/include
	INCLUDE += -I/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/System/Library/Frameworks/Accelerate.framework/Versions/Current/Frameworks/vecLib.framework/Headers/
endif

# *************************************************************************************************
# LD: Linker flags for additional libraries
# -L: additional library directories
# -l: additional libraries in library search path named lib<library_name>.a
# *************************************************************************************************

# Additional library directories -L from all sources
LD_DIRS := 

# Add library location for MacPorts if we are on Mac OS
ifeq ($(detected_OS), Mac)
    LD_DIRS += -L/opt/local/lib
endif
# LD_DIRS += -L/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/System/Library/Frameworks/Accelerate.framework/Versions/Current/Frameworks/vecLib.framework

# fmt (string formattng and printing)
LD_FMT := -lfmt

# Math library
LD_MATH := -lm

# BLAS/LAPACK (linear algebra)
LD_LAPACK := -llapack -lblas

# GNU Scientific Library (numerical computing)
LD_GSL := -lgsl

# GNU Multiprecision Library GMP
LD_GMP := -lgmp

# Selected libraries
LD_LIBS := $(LD_FMT) $(LD_LAPACK) $(LD_GMP)

# Combined LD_FLAGS arguments to linker - library search path and libraries
LD_FLAGS := $(LD_DIRS) $(LD_LIBS)

# *************************************************************************************************
# Prettified flags and full compilation command
# *************************************************************************************************

# Prettify flags
CXX_FLAGS := $(strip $(CXX_FLAGS))
INCLUDE := $(strip $(INCLUDE))
LD_FLAGS := $(strip $(LD_FLAGS))

# Command to compile one executable file; uses rule specific variable TGT_NAME
define CXX_COMPILE
$(CXX) -c $(SRC_DIR)/$(TGT_NAME).cc -o $(OBJ_DIR)/$(TGT_NAME).o \$(NEWLINE)
$(CXX_FLAGS) $(DEP_FLAGS) $(INCLUDE) $(CXX_MACROS)
endef

# Command to link one executable file; uses rule specific variables TGT_NAME and LINK_OBJ
define CXX_LINK
$(CXX) -o $(EXE_DIR)/$(TGT_NAME).x \
$(OBJ_DIR)/$(TGT_NAME).o $(LINK_OBJ) $(LD_FLAGS)
endef
