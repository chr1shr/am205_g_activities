import numpy as np
import numpy.random as random
import time

if __name__ == "__main__":
    # let's create a very large matrix
    # and a large vector
    N = 10000
    S = 100

    t = time.time()

    # initialize them to something random
    A = random.rand(N,N)
    b = random.rand(N)

    t = time.time() - t
    print("Initialize a random square matrix of size {}, and a random vector of size {}, took {:5.4f} seconds".format(N, N, t));

    # we do a matrix-vector dot product for a few times
    t = time.time()
    for i in range(S):
        np.dot(A, b)

    t = time.time() - t

    print("Matrix vector dot product of size {}, repeated {} times, took {:5.4f} seconds".format(N, S, t))
