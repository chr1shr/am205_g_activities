#!/usr/bin/env python

#############################################
# Adapted from AM205 Fall 2020 by Nick Derr #
# https://github.com/nderr/multithreading   #
#############################################

# Python implementation of matrix multiplication using shared
# memory parallelization. Each takes two arguments:
# N, such that the system size of the multiplication is 2^N.
# t, the number of threads to parallelize over.

#################################
# 1. Imports and arg processing #
#################################

# Grab sys and timing modules
import sys
from time import time

# Pull user input
if len(sys.argv) < 2 or len(sys.argv) > 4:
    print("Usage: ./mat_mul.py [-v] N [t]")
    print("")
    print("  N: vector system is size 2^N (accept int,float)")
    print("  t: number of threads (optional, accept int)")
    print(" -v: use vectorized matrix multiply (optional)")
    sys.exit(0)

# Check if to use vectorized mat mul
vec=sys.argv[1]=='-v'

# Arg number for system size and threads
nArg=2 if vec else 1
tArg=3 if vec else 2

# Set number of threads if provided
userThreads=len(sys.argv)>tArg
if userThreads:
    nt=int(sys.argv[tArg])
else:
    nt=-1

# If vectorized, pass thread number through
# OMP environment variable
if nt>0 and vec:
    from os import environ
    environ['OMP_NUM_THREADS']=str(nt)
# OMP env change has to happen before imports

import joblib as jl
import numpy as np

########################
# 2. System allocation #
########################

# Set system size
N=int(2.**float(sys.argv[nArg]))

# Create random vector and matrix
v=np.random.uniform(size=(N,1),low=-1,high=1)
M=np.random.uniform(size=(N,N),low=-1,high=1)

#############################################
# 3. Helper function definitions for joblib #
#############################################

# Function for dotting a matrix row and the in-vector
def dot(r):
    #########################################
    ########### FILL IN CODE HERE ###########
    #########################################
    
    # Step 1: Grab reference to matrix and vector
    # Hint: Use "global" on two variables

    # global ?
    # global ?

    # Step 2: Loop over matrix columns to produce
    # requested value for each item in loop

    # total=0. # Create the dot product variable
    # then do a for loop

    # Step 3: Return dot product

    # return total

    #########################################
    ################## END ##################
    #########################################

# Function for parallel matrix multiplication
def mat_mul(nt):

    #########################################
    ########### FILL IN CODE HERE ###########
    #########################################
    
    # Step 1: Generator for components of dot product
    # Hint: Follow the example

    # fgen=(jl.delayed(?)(?) for ? in range(N))

    # Step 2: Parallel sum by forking rows

    # out=jl.Parallel(n_jobs=?)(?)

    # Step 3: Wrap in numpy object and return

    # return np.array(out)

    #########################################
    ################## END ##################
    #########################################

##############################################
# 4. Actual matrix multiplication and timing #
##############################################

# Minimum time for testing
Tmin=1
T=0

# Do mat muls until minimum time is reached
iters=0
t0=time()
while T<Tmin:

    # Case 1: Use joblib parallelized function
    if not vec:
        w=mat_mul(nt)
    # Case 2: Use numpy vectorized function
    else:
        #########################################
        ########### FILL IN CODE HERE ###########
        #########################################
        
        # Call numpy library function

        #########################################
        ################## END ##################
        #########################################

    # Record time and count iterate
    T=time()-t0
    iters=iters+1

# Print output
print("{:g}".format(T/iters))