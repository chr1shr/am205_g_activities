// *************************************************************************************************
// Harvard Applied Math 205 - Fall 2021.
// Introduction to Compiled Languages
// *************************************************************************************************
// Implmentation of iterative square root function.
//
// Michael S. Emanuel
// 2021-08-27
// *************************************************************************************************

// *************************************************************************************************
// Library dependencies
#include <cmath>

// Local dependencies
#include "matrix_mult.hh"

// *************************************************************************************************
// Matrix / vector multiplication function - hand rolled
// *************************************************************************************************
// y is a pointer to the ANSWER - an mx1 column vector, y = Ax
// A is a pointer to an mxn matrix
// x is a pointer to an nx1 vector
// m is the number of rows in A and y
// n is the number of columns in A and rows in x
void matrix_mult_mse(double* y, const double* A, const double* x, int m, int n)
{
    // Iterate over the row number i
    for(int i=0; i<m; i++) 
    {
        // Initialize sum in this row at zero
        y[i] = 0.0;
        // Accumulate the n entries in row i
        for(int j=0; j<n; j++) 
        {
            // Offset for the (i,j) entry in A
            int k = n*i + j;
            // One term in the sum for y[i]
            y[i] += A[k] * x[j];
        }
    }
}

// *************************************************************************************************
// Matrix / vector multiplication function - using BLAS
// *************************************************************************************************
void matrix_mult_blas(double* y, const double* A, const double* x, int m, int n)
{
    // Declaration of DEGEMV as ported to CBLAS; found in blas-netlib.h
    // void cblas_dgemv(CBLAS_LAYOUT layout,
    //                  CBLAS_TRANSPOSE TransA, 
    //                  const int M, const int N,
    //                  const double alpha, const double *A, const int lda,
    //                  const double *X, const int incX, const double beta,
    //                  double *Y, const int incY);

    // Arguments for call to BLAS routine DGEMV
    CBLAS_LAYOUT layout {CblasRowMajor};
    CBLAS_TRANSPOSE TransA {CblasNoTrans};
    const  double alpha {1.0};
    const int lda {m};
    const int incX {1};
    const int incY {1};
    const double beta {0.0};
    // Delegate to DGEMV
    cblas_dgemv(layout, TransA, m, n, alpha, A, lda, x, incX, beta, y, incY);
}

// *************************************************************************************************
// Random sampling for matrix entries
// *************************************************************************************************

// *************************************************************************************************
// Initialize a uniform distribution between 0 and 1
std::uniform_real_distribution<double> make_uniform_dist()
{
    // Initialize a uniform distribution between 0 and 1
    std::uniform_real_distribution<double> unif(0.0, 1.0);
    return unif;
}

// *************************************************************************************************
// Initialize a random number generator a consistent seed
rng_t make_rng(int seed)
{
    rng_t rng;
    std::seed_seq ss{seed};
    rng.seed(ss);
    return rng;
}

// *************************************************************************************************
// Initialize a matrix or a vector with uniform random numbers
// *************************************************************************************************

// *************************************************************************************************
void random_matrix(double* A, int m, int n, rng_t& rng)
{
    // Initialize a uniform distribution between 0 and 1 using the RNG
    std::uniform_real_distribution<double> unif {make_uniform_dist()};

    // Iterate over the row, i, going up to m
    for(int i=0; i<m; i++) 
    {
        // Iterate over the column, j, going up to n
        for(int j=0; j<n; j++)
        {
            // Offset for the (i, j) matrix entry
            int k = n*i + j;
            // Populate A[i, j] with a random number in [0, 1)
            A[k] = unif(rng);
        }
    }
}

// *************************************************************************************************
void random_vector(double* x, int n, rng_t& rng)
{
    // Initialize a uniform distribution between 0 and 1 using the random number generator
    std::uniform_real_distribution<double> unif {make_uniform_dist()};

    // Iterate over the row, i, going up to M
    for(int i=0; i<n; i++) 
    {
        // Populate x[i] with a random number in [0, 1)
        x[i] = unif(rng);
    }
}
