// *************************************************************************************************
// Harvard Applied Math 205 - Fall 2021.
// Introduction to Compiled Languages
// *************************************************************************************************
// Program to demonstrate pointers, references, new and delete.
// It calls a hand rolled matrix multiplication routine.
//
// Michael S. Emanuel
// 2021-08-26
// *************************************************************************************************

// *************************************************************************************************
// Library dependencies
#include <string>
    using std::string;
#include <fmt/format.h>
    using fmt::print;

// Local dependencies
#include "matrix_mult.hh"
#include "Timer.hh"

// *************************************************************************************************
// Declare functions used by main; defined lower in this file

struct init_t
{
    double* A;
    double* x;
    double* y;
};

// Initialize a random matrix and vector
init_t initialize(const int m, const int n);

// Test harness for matrix multiplication
void test_matrix_mult(mv_mult_type matrix_mult, string func_name, 
    double* A, double* x, double* y, int m, int n, int num_trials);

// *************************************************************************************************
int main() 
{
    // The size of the matrix A (number of rows and columns)
    constexpr int m {10000};
    constexpr int n {10000};
    // The number of trials
    constexpr int num_trials {100};

    // Initialize the matrix A and the vectors x, y
    init_t mats {initialize(m, n)};
    // Unpack the arrays A, x, y from mats
    double* A {mats.A};
    double* x {mats.x};
    double* y {mats.y};

    // Test the matrix_mult routine (hand rolled)
    test_matrix_mult(matrix_mult_mse, "matrix_mult_MSE", A, x, y, m, n, num_trials);

    // Test the matrix_mult routine (BLAS)
    test_matrix_mult(matrix_mult_blas, "matrix_mult_BLAS", A, x, y, m, n, num_trials);

    // Delete manually allocated arrays
    delete [] A;
    delete [] x;
    delete [] y;
}

// *************************************************************************************************
// Functions used by main
// *************************************************************************************************

// *************************************************************************************************
// Initialize a random matrix and vector
init_t initialize(const int m, const int n)
{
    // Start the timer
    Timer t;
    
    // Allocate memory for arrays with operator new
    // The asterisk after double means that A, x and y are POINTERS to a double
    // Here, each of them is a pointer to an array of doubles, a contiguous block in memory
    double* A {new double[m*n]};
    double* x {new double[n]};
    double* y {new double[m]};

    // Initialize a random number generator
    rng_t rng {make_rng(42)};

    // Initialize the matrix A and vector x with uniform random numbers in [0, 1]
    random_matrix(A, m, n, rng);
    random_vector(x, n, rng);

    // Report initialization time
    print("********************************************************************************\n");
    print("Allocate and initialize a random {:d}x{:d} matrix, and a random {:d}x1 vector.\n", n, n, n);
    print("Time: {:5.4f} seconds.\n", t.tock());

    // Wrap allocated and initialized arrays into a structure
    return init_t {.A=A, .x=x, .y=y};
}

// *************************************************************************************************
// Test harness for a selected matrix_mult function
void test_matrix_mult(mv_mult_type matrix_mult, string func_name, 
                        double* A, double* x, double* y, int m, int n, int num_trials)
{
    // Time matrix multiplication operation
    Timer t;
    // Repeat num_trials times
    for(int i=0; i<num_trials; i++) 
    {
        // Do the matrix multiplication with the selected function
        matrix_mult(y, A, x, m, n);
    }
    // Add up the rows of y
    double sum = 0.0;
    for (int i=0; i<n; i++) {sum += y[i];}
    print("********************************************************************************\n");
    print("Matrix / vector product of size {:d}, repeated {:d} times. Using function {:s}.\n", 
            n, num_trials, func_name);
    print("Mean entry of y=Ax: {:8.3f}.\n", sum/n);

    // Report matrix multiplication time
    double time {t.tock()};
    print("Time: {:5.3f} seconds.\n", time);
    print("Mean Time: {:8.3f} milliseconds per trial.\n", time / num_trials * 1000.0);
}
