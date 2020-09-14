import numpy.random as nprnd
# Global variables to keep track of the mean and total games
sumlw=0
games=-1

def play(n,hist,lw,lc,y):

    # Needed to access the global variables
    global sumlw,games
    games+=1

    # On the first game, we can't calculate a mean of previous wins, so just
    # guess zero
    if(games==0):
        sumlw=lw
        return 1

    # On subsequent games, calculate the mean of the previous wins, rounded to
    # the nearest integer
    sumlw+=lw
    mean_lw =sumlw/games
    #return the nearest int from an exponential distribution sample with mean of all winners in previous rounds
    return int(nprnd.exponential(mean_lw)+0.5)
    # return int(float(sumlw)/float(games)+0.5)
