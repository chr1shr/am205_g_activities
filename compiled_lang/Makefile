# *************************************************************************************************
# Harvard Applied Math 205 - Fall 2021.
# Introduction to Compiled Languages
# *************************************************************************************************
# Automated makefile for compiled languages tutorial.
#
# Michael S. Emanuel
# 2021-08-24
# *************************************************************************************************

# *************************************************************************************************
# Incorporate the configuration file
# *************************************************************************************************
include build/config.mk

# *************************************************************************************************
# Convenience targets: all, clean, default, depend, help, report
# *************************************************************************************************
# Set default goal - all is defined below
.DEFAULT_GOAL := all

# The PHONY command tells GNU Make that "all", "clean" etc are phony targets
.PHONY: all clean help

# Clean command is silent
.SILENT: clean help

# Define target "all" to build all executables
all: $(TGT_EXE)
	@:

# Target clean removes all the built executable and object files.
# Use wildcards to ensure any "orphaned" object files or executables are also deleted.
clean:
	@rm -f $(OBJ_DIR)/*.x $(OBJ_DIR)/*.o $(EXE_DIR)/*.x

# Target clobber removes everything, object files and dependencies
clobber: clean
	@rm -f $(OBJ_DIR)/*.d

# Give help with list of makefile targets
help:
	$(info Make targets available:)
	$(info $(TAB)all       : build all executables)
	$(info $(TAB)clean     : delete all executables and object files)
	$(info $(TAB)clobber   : delete all executable, object files, and automatically generated dependency files)
	$(info $(TAB)help      : reports this help message)
	@:

# *************************************************************************************************
# Collections of files and targets
# *************************************************************************************************

# Targets with C++ source files
TGT_ALL := $(patsubst $(SRC_DIR)/%.cc, %, $(wildcard $(SRC_DIR)/*.cc))
# TGT_EXE is entered manually at the top of the file
TGT_NEX := $(filter-out $(TGT_EXE), $(TGT_ALL))

# C++ source files
CPP_EXE := $(patsubst %, $(SRC_DIR)/%.cc, $(TGT_EXE))
CPP_NEX := $(patsubst %, $(SRC_DIR)/%.cc, $(TGT_NEX))
CPP_ALL := $(CPP_EXE) $(CPP_NEX)

# Object files
OBJ_EXE := $(patsubst %, $(OBJ_DIR)/%.o, $(TGT_EXE))
OBJ_NEX := $(patsubst %, $(OBJ_DIR)/%.o, $(TGT_NEX))
OBJ_ALL := $(OBJ_EXE) $(OBJ_NEX)

# Executable program files
EXECS := $(patsubst %, $(EXE_DIR)/%.x, $(TGT_EXE))

# *************************************************************************************************
# Automatically generate dependencies
# *************************************************************************************************

# Dependency files are adjacent to corresponding object files, e.g. obj/file_name.d
# Use Substitution References; see GNU make manual 6.3.1
# https://www.gnu.org/software/make/manual/make.html#Substitution-Refs
DEP_EXE := $(OBJ_EXE:.o=.d)
DEP_NEX := $(OBJ_NEX:.o=.d)
DEP_ALL := $(OBJ_ALL:.o=.d)

# Incorporate automatic dependencies: each object depends on its sister dependency file
-include $(DEP_ALL)

# *************************************************************************************************
# Compile object files: filename.cc -> filename.o, filename.d
# *************************************************************************************************

# Rule to make directories if they are missing
$(OBJ_DIR): ; mkdir $(OBJ_DIR)
$(EXE_DIR): ; mkdir $(EXE_DIR)

# Rule specific variables for compiling a source file
$(OBJ_ALL) : TGT_NAME = $(patsubst $(OBJ_DIR)/%.o,%,$@)
$(DEP_ALL) : TGT_NAME = $(patsubst $(OBJ_DIR)/%.d,%,$@)

# Rules to build object files; also builds dependency files
$(OBJ_ALL) : $(OBJ_DIR)/%.o : $(SRC_DIR)/%.cc $(OBJ_DIR)/%.d | $(OBJ_DIR)
	$(info ******************************************************************************** )
	$(info Compiling: $(TGT_NAME))
	$(CXX_COMPILE)

# Rules to build dependency files for executable programs; also compiles object files
# This is only needed when "bootstrapping" at the beginning with missing dependency files.
$(DEP_ALL) : $(OBJ_DIR)/%.d : $(SRC_DIR)/%.cc | $(OBJ_DIR)
	$(info ******************************************************************************** )
	$(info Compiling: $(TGT_NAME))
	$(CXX_COMPILE)

# *************************************************************************************************
# Build convenience targets my_program from exec/my_program.x
# *************************************************************************************************

# Rule specific variable for TGT_NAME in the rule for each executable file
$(EXECS) : TGT_NAME = $(patsubst $(EXE_DIR)/%.x,%,$@)

# Static Pattern Rule to build an executable file given its convenience target
# Running make my_program creates the file exec/my_program.x
$(TGT_EXE): % : $(EXE_DIR)/%.x
	@:

# *************************************************************************************************
# Link executable files from object files: program.o plus all non-executable object files.
# *************************************************************************************************

# Rule specific variables for linkage of executables against objects
$(EXECS) : DEP_FILE = $(file < $(OBJ_DIR)/$(TGT_NAME).d)
$(EXECS) : LINK_OBJ = $(filter $(patsubst $(SRC_DIR)/%.hh, $(OBJ_DIR)/%.o, $(DEP_FILE)), $(OBJ_NEX))

# Static Pattern Rule to link executables from program.o and all non-executable object files
.SECONDEXPANSION:
$(EXECS): $(EXE_DIR)/%.x : $(OBJ_DIR)/%.o $(OBJ_DIR)/%.d $$(LINK_OBJ) | $(EXE_DIR)
	$(info ******************************************************************************** )
	$(info Linking: $(TGT_NAME))
	$(CXX_LINK)

# *************************************************************************************************
# Debugging / testing
# *************************************************************************************************

# Check collections of files / targets
# $(info TGT_EXE = $(TGT_EXE) )
# $(info TGT_NEX = $(TGT_NEX) )
# $(info CPP_EXE = $(CPP_EXE) )
# $(info CPP_NEX = $(CPP_NEX) )
# $(info OBJ_EXE = $(OBJ_EXE) )
# $(info OBJ_NEX = $(OBJ_NEX) )
# $(info DEP_EXE = $(DEP_EXE) )
# $(info DEP_NEX = $(DEP_NEX) )
