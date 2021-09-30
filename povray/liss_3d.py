#!/usr/bin/python3
from math import *

# Create POV-Ray include file with a 3D curve in it, made of cylinders and
# spheres
f=open("liss_3d.inc","w")

# Number of cylinders, and dt size
n=3200
h=2.*pi/n

# 3D parametric function describing a Lissajous curve
def pos(t):
    return (sin(t)+cos(6*t),cos(5*t),cos(7*t))

# Loop over values of t along the curve
(x,y,z)=pos(0)
for i in range(1,n+1):

    # Print a sphere
    f.write("sphere{<%.4f,%.4f,%.4f>,r}\n"%(x,y,z))
    
    # Print a cylinder that connects from this sphere to the next one
    (nx,ny,nz)=pos(i*h)
    f.write("cylinder{<%.4f,%.4f,%.4f>,<%.4f,%.4f,%.4f>,r}\n"%(x,y,z,nx,ny,nz))
    (x,y,z)=(nx,ny,nz)
f.close()
