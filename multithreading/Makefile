# Detect the operating system
detected_OS := $(shell sh -c 'uname 2>/dev/null || echo Unknown')

# Set the compiler and flags based on the operating system
# Supported OS are Mac OSX ("Darwin") and Linux ("Linux")

# Is the OS Mac?
ifeq ($(detected_OS), Darwin)
cxx := g++-mp-7 -O3
cflags := -fopenmp -Wall -ansi -pedantic
lp_lflags := -llapack -lblas
endif

# Is the OS Linux?
ifeq ($(detected_OS), Linux)
cxx := g++-9 -O3
cflags := -fopenmp -Wall -ansi -pedantic
lp_lflags := -llapack -lblas
endif

# Lists of files to be built
execs=hello_world race_condition# mat_mul

all: $(execs)

# A Makefile target to remove all the built files
clean:
	rm -f $(execs)
	
# Makefile rule to build an executable. Note $@ is a shorthand for the file to
# be built and $^ is a shorthand for all the dependencies. (Can also use $< to
# mean the first dependency only.)
hello_world: hello_world.cc
	$(cxx) $(cflags) -o $@ $^

race_condition: race_condition.cc
	$(cxx) $(cflags) -o $@ $^

# mat_mul: mat_mul.cc
# 	$(cxx) $(cflags) -o $@ $^

# The PHONY command tells GNU Make than "clean" is a phony target, which means
# that it doesn't correspond to an actual file called "clean'.
.PHONY: clean