#!/usr/bin/python3
import random_choice
import test_strategy

# Number of players and total games
n=36
trials=10000

# Counters for who won
rcw=0
tsw=0
now=0

# Data about the runs
hist=[0 for i in range(100)]
lc=[0 for i in range(n)]
lw=0

# Function to ensure choices are in the allowable range
def ra(x):
    if x<0:
        return 0
    elif x>99:
        return 99
    return x

# Simulate a large number of trials 
for i in range(trials):
    cc=[0 for i in range(n)]

    # First n-1 players use the random_choice strategy
    for i in range(n-1):
        cc[i]=ra(random_choice.play(n,hist,lw,lc,i))

    # Last player uses the test_strategy strategy
    cc[n-1]=ra(test_strategy.play(n,hist,lw,lc,n-1))
    
    # Tally the guesses
    c=[0 for i in range(100)]
    for i in cc:
        c[i]+=1
        hist[i]+=1

    # Find the winning number
    lw=0
    while lw<100:
        if c[lw]==1:
            break
        lw+=1

    # See who won
    if lw==100:
        now+=1
    elif cc[n-1]==lw:
        tsw+=1
    else:
        rcw+=1

    # Move this round's choices to lc 
    lc=cc
    
# Print the probabilities of winning
f=100.0/trials
print(("Wins for random_choice :%6.2f%% (%.2f%% per player)") % (rcw*f,rcw*f/(n-1)))
print(("Wins for test_strategy :%6.2f%%") % (tsw*f))
print(("No winner              :%6.2f%%") % (now*f))
