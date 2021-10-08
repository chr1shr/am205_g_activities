import numpy as np
import matplotlib.pyplot as plt

# Lagrange interpolant, with (xp,yp) as control points,
# and x the points at which to evaluate.
def lagr(x, xp, yp):
	n = len(xp)
	p = np.zeros(len(x)) # polynomial output
	for k in range(n):
		L = np.ones(len(x))
		for j in range(n):
			if j != k:
				L *= (x - xp[j])/(xp[k] - xp[j])
		p += yp[k]*L
	return p

# Chebychev points
def cheby(n):
	j = np.linspace(1,n,n)
	return np.cos((2*j-1)*np.pi/(2*n))

# sigmoid function - looks like a step with increasing k.
def sigmoid(x,k):
	return 1./(1+np.exp(-k*x))

# sharpness of the sigmoid
k = 5 # 5, 10, 100

# number of interpolation points to use on [-1,1]
n = 16
# try interpolation with n points.
#xp = np.linspace(-1,1,n) # evenly-spaced
xp = cheby(n) # Chebyshev
yp = sigmoid(xp,k)

# finely sample interpolant at 1000 points.
x = np.linspace(-1,1,1000)
p = lagr(x,xp,yp) # interpolant.
y = sigmoid(x,k) # exact solution.


# plot the interpolant and true solution.
fig, ax = plt.subplots(1,1,figsize=(5,5))
ax.plot(x,y,label='sigmoid')
ax.plot(x,p,label='interpolant')
ax.scatter(xp,yp,marker='x',zorder=100,label='interpolation points')
ax.set_ylim(-0.25,1.5)
ax.set_xlabel('x')
ax.set_ylabel('y')
ax.legend()
plt.show()