#!/usr/bin/python3
import numpy as np
import matplotlib.pyplot as plt
from math import *

# Linear advection example on [-1,1] using simple upwinding scheme.

# Grid size
m=200
mp2=m+2 # pad with 2 ghost nodes
# PDE-related constants.
c=1.
dx=2.0/(m-1)
dt=0.05*dx
nu=c*dt/dx
T=1. # final simulation time
snaps=10 # number of snapshots to output (excluding t=0)
iters=int(T/dt)//snaps # iterations to perform between snapshots

u=np.empty(mp2) # memory for the current step
u1=np.empty(mp2) # memory for the next step
us=np.empty((m,snaps+1)) # memory for all snapshots

# Initial condition
k=100
for j in range(m):
    x=-1+dx*j
    u[j]=1./(1+np.exp(-k*x)) # sigmoid function
# The ghost nodes at u[m]=u[-2], u[m+1]=u[-1] correspond to
# positions x=-1-2dx, x=-1-dx, respectively.
u[-1]=1./(1+np.exp(-k*(-1-dx)))
u[-2]=1./(1+np.exp(-k*(-1-2*dx)))
u1=np.copy(u)
us[:,0]=u[:m]

# Integrate the PDE
for i in range(1,snaps+1):
    for k in range(iters):
        for j in range(m):
            u1[j]=u[j]-0.5*nu*(u[j-2]-4*u[j-1]+3*u[j]) # 2nd order upwinding scheme
        u=np.copy(u1)
    us[:,i]=u[:m]

# Output results
fig, ax = plt.subplots(1,1,figsize=(6,3))
x=np.linspace(-1,1,m)
cmap=plt.cm.gnuplot
for i in range(snaps+1):
    ax.plot(x,us[:,i],color=cmap(i*iters*dt),alpha=0.8)
ax.set_ylim(-0.5,1.5)
ax.set_xlabel('x')
ax.set_ylabel('u')
fig.tight_layout()
plt.show()
