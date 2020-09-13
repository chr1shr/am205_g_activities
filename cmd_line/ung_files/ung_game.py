#!/usr/bin/python3
import os
import numpy as np

# This program was used during the workshop to play the unique number game, by
# reading in people's guesses from text files within a "ung" directory

# Data about the runs
hist=[0 for i in range(100)]

# Number of games
g=1

# Count players and obtain names
fn=[]
for filename in os.listdir(os.getcwd()+"/ung"):
    fn.append(filename)
n=len(fn)

# Initialize arrays for guesses and total wins
z=np.empty((n,g),dtype=np.int8)
tw=np.zeros((n+1),dtype=np.int32)

# Read in the guesses
i=0
for filename in os.listdir(os.getcwd()+"/ung"):
    print(filename)
    with open(os.path.join(os.getcwd()+"/ung", filename), 'r') as f:
        for l in range(g):
            z[i,l]=int(f.readline())
    i+=1

# Play the game(s)
for l in range(g):

    # Tally the players' guesses
    ma=0
    c=[0 for i in range(100)]
    for i in range(n):
        c[z[i,l]]+=1
        if z[i,l]>ma:
            ma=z[i,l]

    # Print a histogram of guesses
    for j in range(ma+1):
        print(j,"#"*c[j])

    # Find the winning number
    w=-1
    for j in range(ma+1):
        if c[j]==1:
            w=j
            break
    
    # Find the winner
    if w==-1:
        print("No winner")
        tw[n]+=1
    else:
        for i in range(n):
            if z[i,l]==w:
                break
        print(fn[i],"wins!")
        tw[i]+=1
    print()

# For multi-games, print the total scores
if g>1:
    print("Total wins:")
    for i in range(n):
        print(fn[i],":",tw[i])
    print("Draws :",tw[n])
