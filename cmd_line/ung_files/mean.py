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
        return 0

    # On subsequent games, calculate the mean of the previous wins, rounded to
    # the nearest integer
    sumlw+=lw
    return int(float(sumlw)/float(games)+0.5)
