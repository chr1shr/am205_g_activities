// *************************************************************************************************
// Harvard Applied Math 205 - Fall 2021.
// Introduction to Compiled Languages
// Michael S. Emanuel
// 2021-08-26
// *************************************************************************************************
// Implmenetation of iterative square root function.
// *************************************************************************************************

// *************************************************************************************************
// Library dependencies
#include <cmath>

// Local dependencies
#include "sqrt_iter.hh"

// *************************************************************************************************
// Make a decent initial guess for the square root of x
double sqrt_guess(double x)
{
    // Decompose x into its mantissa and exponent in the form
    // x = m_x * 2^exp_x with m_x in {0} U [0.5, 1.0)
    int exp_x {0};
    double m_x {frexp(x, &exp_x)};
    // The exponent of the initial guess s is half the exponent of x
    int exp_s {exp_x / 2};
    // When exp_s is even, guess a mantissa of (1+m_x)/2
    // When exp_s is odd, guess a mantissa of (1+2m_x)/2 = 0.5 + m_x
    double m_s = (exp_x % 2) ? (1.0 + m_x)/2.0 : 0.5 + m_x;
    // Initialize s to the double with mantissa m_s and exponent exp_s
    return ldexp(m_s, exp_s);
}

// *************************************************************************************************
// Calculate the square root of x iteratively
double sqrt_iter(double x)
{
    // If x is negative, just return not a number (NaN) instead of throwing an exception
    if (x<0) {return nan("");}
    // s is the current guess for square root of x; initialize with helper function
    double s {sqrt_guess(x)};
    // Set tolerance for convergence at machine epsilon in double precision
    double tol = 1.11E-16;
    // For at most 16 iterations, refine s iteratively
    // Compute dual lower and upper bounds, replace s with the midpoint
    for (int i=0; i<16; i++)
    {
        // New dual bound to s;
        double t = x / s;
        // Current relative error estimate
        double err = (s<t) ? (t-s)/s : (s-t)/t;
        // Improve estimate of s
        s = (s + t) / 2.0;
        // Break out of loop if tolerance achived
        if (err < tol) {break;}
    }
    // By this point s should be a pretty good estimate for square root of x.
    return s;
}
