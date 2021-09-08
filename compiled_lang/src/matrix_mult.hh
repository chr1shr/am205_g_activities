// *************************************************************************************************
// Harvard Applied Math 205 - Fall 2021.
// Introduction to Compiled Languages
// Michael S. Emanuel
// 2021-08-26
// *************************************************************************************************
// Silly hand-rolled matrix multiplication functions.
// In a real program use the library functions e.g. xGEMV in BLAS
// *************************************************************************************************

// *************************************************************************************************
// Library dependencies
#include <random>
#include <cblas.h>

// Alias type of the random number generator
using rng_t = std::mt19937_64;

// Type for matrix / vector multiplication function
// typedef void (*mv_mult_type)(double* y, double *const A, double *const x, int m, int n);
using mv_mult_type = void (*)(double* y, const double* A, const double* x, int m, int n);

// *************************************************************************************************
// Multiply matrix A by vector x; save the answer in y.  Use hand rolled implementation.
// A is an mxn matrix
// x is a vector of size n
// y is a vector of size m
// m is the number of rows in A
// n is the number of columns in A; must match rows in y
void matrix_mult_mse(double* y, const double* A, const double* x, int m, int n);

// *************************************************************************************************
// Multiply matrix A by vector x; save the answer in y.  Delegate to BLAS DGEMV routine.
// A is an mxn matrix
// x is a vector of size n
// y is a vector of size m
// m is the number of rows in A
// n is the number of columns in A; must match rows in y
void matrix_mult_blas(double* y, const double* A, const double* x, int m, int n);

// *************************************************************************************************
// Uniform distribution and random number generator it uses
std::uniform_real_distribution<double> make_uniform_dist();
rng_t make_rng(int seed);

// *************************************************************************************************
// Initiailize random matrix and vetor
void random_matrix(double* A, int m, int n, rng_t& rng);
void random_vector(double* x, int n, rng_t& rng);
