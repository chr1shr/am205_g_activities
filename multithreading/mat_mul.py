#!/usr/bin/python3

#############################################
# Adapted from AM205 Fall 2020 by Nick Derr #
# https://github.com/nderr/multithreading   #
#############################################

# Python implementation of matrix multiplication using shared
# memory parallelization. Each takes two arguments:
# N, such that the system size of the multiplication is 2^N.
# t, the number of threads to parallelize over.

#################################
# 1. Imports and arg processingt #
#################################

# Grab sys and timing modules
import sys
from time import time

# Pull user input
if len(sys.argv) < 2 or len(sys.argv) > 4:
    print("Usage: ./mat_mul.py [-v] N [t]")
    print("")
    print(" -v: use vectorized matrix multiply (optional)")
    print("  N: vector system is size 2^N (accept int,float)")
    print("  t: number of threads (optional, accept int)")
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

    # Grab reference to matrix and vector
    global M
    global v

    # Loop over matrix columns
    total=0.
    for i in range(v.shape[0]):
        total=total+M[r,i]*v[i]

    # Return dot product
    return total

# Function for parallel matrix multiplication
def mat_mul(nt):

    # Generator for components of dot product,
    # each iterate of comps holds a pointer to the
    # dot function and the argument to pass (row index)
    fgen=(jl.delayed(dot)(r) for r in range(v.shape[0]))

    # Calculate components by forking rows
    out=jl.Parallel(n_jobs=nt)(fgen)

    # Wrap in numpy object
    return np.array(out)

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
        w=M.dot(v) # or equil. use w=np.dot(M,v)

    # Record time and count iterate
    T=time()-t0
    iters=iters+1

# Print output
print("{:g}".format(T/iters))