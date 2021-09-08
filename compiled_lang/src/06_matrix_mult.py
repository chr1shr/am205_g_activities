import numpy as np
import numpy.random as random
import time

# **********************************************************************************************************************
def main():
    """Program to test matrix / vector multiplication in Python"""
    # Create a large matrix  and a large vector
    n: int = 10000
    # n: int = 1000
    # Number of trials to run
    num_trials_np: int = 100
    num_trials_mm: int = 1

    # Start timer
    t0 = time.time()
    # Initialize them to something random
    A: np.ndarray = random.rand(n, n)
    x: np.ndarray = random.rand(n)

    # Report time to initialize matrices
    t: float = time.time() - t0
    print("********************************************************************************")
    print(f"Allocate and initialize a random {n}x{n} matrix, and a random {n}x1 vector.");
    print(f"Time: {t:5.4f} seconds.")

    # Test matrix multiplication using numpy
    test_np_dot(A, x, num_trials_np)

    # Test matrix multiplication using matrix_mult
    test_matrix_mult(A, x, num_trials_mm)

    # Test matrix multiplication using matrix_mult_list
    A_list = A.tolist()
    x_list = x.tolist()
    m: int = n
    test_matrix_mult_list(A_list, x_list, m, n, num_trials_mm)

# **********************************************************************************************************************
# Three functions to test different ways of multiplying matrices in python
# test_np_dot tests the numpy.dot function
# test_matrix_mult tests the function matrix_mult; it uses numpy arrays and python loops
# test_matrix_mult_list tests the function matrix_mult_list; it uses python lists and python loops
# **********************************************************************************************************************

# **********************************************************************************************************************
def test_np_dot(A: np.array, x: np.ndarray, num_trials: int):
    """Test the numpy.dot function for matrix / vector products"""
    # Unpack shape
    m, n = A.shape
    # Do a matrix-vector dot product for num_trials trials
    t0 = time.time()
    for i in range(num_trials):
        y: np.ndarray = np.dot(A, x)
    # Compute the mean entry in y
    mean_entry: float = np.average(y)

    # Report time for matrix / vector product
    t: float = time.time() - t0
    mt: float = t / num_trials * 1000.0
    print("********************************************************************************")
    print(f"Matrix / vector product of size {m:d}x{n:d}, repeated {num_trials} times using numpy.dot.")
    print(f"Time: {t:5.4f} seconds.")
    print(f"Mean Time: {mt:5.4f} milliseconds per trial.")
    print(f"Mean entry of y=Ax: {mean_entry:8.3f}.")

# **********************************************************************************************************************
def test_matrix_mult(A: np.ndarray, x: np.ndarray, num_trials: int):
    """Test the hand-rolled function matrix_mult for matrix / vector products"""
    # Unpack shape
    m, n = A.shape
    # Do a matrix-vector dot product for num_trials trials
    t0: float = time.time()
    for i in range(num_trials):
        y: np.ndarray = matrix_mult(A, x)
    # Compute the mean entry in y
    mean_entry: float = np.average(y)

    # Report time for matrix / vector product
    t: float = time.time() - t0
    mt: float = t / num_trials * 1000.0
    print("********************************************************************************")
    print(f"Matrix / vector product of size {m:d}x{n:d}, repeated {num_trials} times using matrix_mult.")
    print(f"Mean entry of y=Ax: {mean_entry:8.3f}.")
    print(f"Time: {t:5.3f} seconds.")
    print(f"Mean Time: {mt:5.3f} milliseconds per trial.")

# **********************************************************************************************************************
def test_matrix_mult_list(A: list, x: list, m: int, n: int, num_trials: int):
    """Test the hand-rolled function matrix_mult_list for matrix / vector products"""

    # Do a matrix-vector dot product for num_trials trials
    t0: float = time.time()
    for i in range(num_trials):
        y: np.ndarray = matrix_mult_list(A, x, m, n)
    # Compute the mean entry in y
    mean_entry: float = np.average(y)

    # Report time for matrix / vector product
    t: float = time.time() - t0
    mt: float = t / num_trials * 1000.0
    print("********************************************************************************")
    print(f"Matrix / vector product of size {m:d}x{n:d}, repeated {num_trials} times using matrix_mult_list.")
    print(f"Mean entry of y=Ax: {mean_entry:8.3f}.")
    print(f"Time: {t:5.3f} seconds.")
    print(f"Mean Time: {mt:5.3f} milliseconds per trial.")

# **********************************************************************************************************************
# Two routines to multiply matrices by hand
# matrix_mult uses numpy arrays to store the data and python loops
# matrix_mult_list uses python lists to store the data and python loops
# **********************************************************************************************************************

# **********************************************************************************************************************
def matrix_mult(A: np.ndarray, x: np.ndarray) -> np.ndarray:
    """Multiply matrix A by vector x by hand in Python"""
    # Extract size m x n from A
    m, n = A.shape
    # Initialize an array for the answer y
    y: np.ndarray = np.zeros(m)
    # Iterate over rows i
    for i in range(m):
        # Iterate over rows j
        for j in range(n):
            y[i] += A[i,j] * x[j]
    # Return the product vector, y
    return y

# **********************************************************************************************************************
def matrix_mult_list(A: list, x: list, m: int, n: int) -> list:
    """Multiply matrix A by vector x by hand in Python"""
    # Initialize a list of zeroes for the answer
    y = list()
    for i in range(n):
        y.append(0.0)
    # Iterate over rows i
    for i in range(m):
        # Iterate over rows j
        for j in range(n):
            y[i] += A[i][j] * x[j]
    # Return the product vector, y
    return y

# **********************************************************************************************************************
if __name__ == "__main__":
    main()
