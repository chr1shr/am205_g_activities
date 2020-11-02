import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation

# plot the "trail" of the pendulum
def plot_trail(x, y, trail, colors, ax):
    line, = ax.plot(x,y,color=colors[-1],alpha=0.5)
    scat = ax.scatter(x[-trail:],y[-trail:],c=colors,s=60)
    return scat, line

# plot the bob position
def plot_bob(x, y, x0, y0, color, ax):  
    line, =ax.plot([x0,x],[y0,y],color=color+[0.7],lw=3)
    scat = ax.scatter(x,y,c=[color],s=100,zorder=2000)
    return scat, line

# take an existing scatter object and update positions and colors (used for animation).
def update_scatter(scat, x, y, colors=False):
    scat.set_offsets(np.hstack([x,y]).reshape(2,-1).T)
    if(colors):
        scat._facecolors = colors
        scat._edgecolors = colors
    
def update_line(line, x, y):
    line.set_data(x, y)

# animation for simple pendulum.
def animate_simple_pendulum(sol):
    fr = 2
    trail = min([30,fr])
    colors1 = [[0.2,0.5,0.9,a/float(trail-1)] for a in range(trail)]

    # initialize plot 
    fig, ax = plt.subplots(1,1,figsize=(8,8))
    trail1, path1 = plot_trail(sol[:fr,0],sol[:fr,1],trail,colors1,ax)
    bob1, rod1 = plot_bob(sol[fr,0],sol[fr,1],0,0,[0.2,0.5,0.9],ax)

    ax.scatter(0,0,c=[[0.1,0.4,0.6]],s=100,zorder=2000)
    ax.set_xticks([])
    ax.set_yticks([])
    ax.set_xlim(-1.25,1.25)
    ax.set_ylim(-1.5,1)

    def animate(i):
        '''Plot updates for animation.'''
        fr = i+2
        trail = min([30,fr])
        colors1 = [[0.2,0.5,0.9,a/float(trail-1)] for a in range(trail)]
        
        update_scatter(trail1, sol[fr-trail:fr,0], sol[fr-trail:fr,1], colors1)
        update_scatter(bob1, sol[fr,0], sol[fr,1])
        
        update_line(path1, sol[:fr,0], sol[:fr,1])
        update_line(rod1, [0,sol[fr,0]],[0,sol[fr,1]])
        
        return path1, trail1, bob1, rod1,

    ani = animation.FuncAnimation(fig, animate, frames=len(sol)-2, interval=2, blit=True)
    plt.close(fig)
    return ani

# animation for double pendulum.  
def animate_double_pendulum(sol):
    fr = 2
    trail = min([30,fr])
    colors1 = [[0.2,0.5,0.9,a/float(trail-1)] for a in range(trail)]
    colors2 = [[0.9,0.2,0.5,a/float(trail-1)] for a in range(trail)]

    # initialize plot 
    fig, ax = plt.subplots(1,1,figsize=(8,8))
    trail1, path1 = plot_trail(sol[:fr,0],sol[:fr,1],trail,colors1,ax)
    trail2, path2 = plot_trail(sol[:fr,4],sol[:fr,5],trail,colors2,ax)
    bob1, rod1 = plot_bob(sol[fr,0],sol[fr,1],0,0,[0.2,0.5,0.9],ax)
    bob2, rod2 = plot_bob(sol[fr,4],sol[fr,5],sol[fr,0],sol[fr,1],[0.9,0.2,0.5],ax)

    ax.scatter(0,0,c=[[0.1,0.4,0.6]],s=100,zorder=2000)
    ax.set_xticks([])
    ax.set_yticks([])
    ax.set_xlim(-2.25,2.25)
    ax.set_ylim(-2.5,2)

    def animate(i):
        '''Plot updates for animation.'''
        fr = i+2
        trail = min([30,fr])
        colors1 = [[0.2,0.5,0.9,a/float(trail-1)] for a in range(trail)]
        colors2 = [[0.9,0.2,0.5,a/float(trail-1)] for a in range(trail)]
        
        update_scatter(trail1, sol[fr-trail:fr,0], sol[fr-trail:fr,1], colors1)
        update_scatter(trail2, sol[fr-trail:fr,4], sol[fr-trail:fr,5], colors2)
        update_scatter(bob1, sol[fr,0], sol[fr,1])
        update_scatter(bob2, sol[fr,4], sol[fr,5])
        
        update_line(path1, sol[:fr,0], sol[:fr,1])
        update_line(path2, sol[:fr,4], sol[:fr,5])
        update_line(rod1, [0,sol[fr,0]],[0,sol[fr,1]])
        update_line(rod2, [sol[fr,0],sol[fr,4]], [sol[fr,1],sol[fr,5]])
        
        return path1, trail1, bob1, rod1, path2, trail2, bob2, rod2,

    ani = animation.FuncAnimation(fig, animate, frames=len(sol)-2, interval=2, blit=True)
    plt.close(fig)
    return ani
