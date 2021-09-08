// *************************************************************************************************
// Harvard Applied Math 205 - Fall 2021.
// Introduction to Compiled Languages
// Michael S. Emanuel
// 2021-08-26
// *************************************************************************************************
// Program to demonstrate use of functions.
// It uses the hand rolled square root function declared in sqrt_iter.hh.
// This program also demonstrates the use of argc and argv for command line arguments.
// *************************************************************************************************

// *************************************************************************************************
// Library dependencies
#include <cmath>
#include <fmt/format.h>
    using fmt::print;

// Local dependencies
#include "sqrt_iter.hh"

// *************************************************************************************************
// main is like other C++ functions in most respects
// it is special in that program execution starts there
// it always has a return type of int. 
// it can optionally accept arguments main(int argc, char* argv[]) from the command line
int main(int argc, char* argv[])
{
    // Should be 0 or 1 arguments
    if (argc>2)
    {
        print("Usage: sqrt [x].\n");
        print("Reports the square root of a double x passed at the command line.\n");
        print("If x is omitted, it defaults to 2.0.\n");
        exit(1);
    }

    // Populate x, the number whose square root we calculate
    double x = 2.0;
    if (argc == 2)
        {x = atof(argv[1]);}

    // Calculate sqrt(x) with library and hand rolled functions
    double s_lib {sqrt(x)};
    double s_mse {sqrt_iter(x)};
    // The error in the hand rolled function iterative
    double err = fabs(s_mse - s_lib);
    
    // Report results
    print("x            = {:18.16f}.\n", x);
    print("sqrt(x)      = {:18.16f}.\n", s_lib);
    print("sqrt_iter(x) = {:18.16f}.\n", s_mse);
    print("error        = {:8.2e}.\n", err);
    print("rel error    = {:8.2e}.\n", err/s_lib);
}
