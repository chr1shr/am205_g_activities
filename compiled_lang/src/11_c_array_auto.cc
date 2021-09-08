// *************************************************************************************************
// Harvard Applied Math 205 - Fall 2021.
// Introduction to Compiled Languages
// *************************************************************************************************
// Example of initializing an automatic C-style array in C++.
// Initially written by Yuexia Luna Lin, AM 205 Fall 2020.
// Revised by Michael S. Emanuel
// 2021-09-01
// *************************************************************************************************

// *************************************************************************************************
// Library dependencies
#include <cmath>
    using std::sqrt;
// Old style C libraries
#include <stdio.h>
#include <time.h>

// *************************************************************************************************
int main() 
{
    // The size of our array; size must be known at compile time!
    constexpr int N {100};
    // Declare an array of N doubles 
    double x[N];
    // norm2 is the accumulated squared norm of the vector entries
    double norm2 {0.0};

    // Time the operation to initialize array con compute veector norm
    clock_t time = clock();
    // Iterate over N rows of the vector
    for(int i=0; i<N; i++) 
    {
        // This verbose construction tells C++ that we mean to convert the integer i to a double.  
        // Otherwise g++ complains about a potentially narrowing conversion.
        double t {static_cast<double>(i)};
        // Set the value of i-th element
        x[i] = sin(t);
        // Accumluated the square of each term in norm2
        norm2 += x[i] * x[i];
    }
    // Calculate the norm from the accumulated squared norm by taking its square root
    // The sqrt function is declared in cmath
    double norm {sqrt(norm2)};
    time = clock() - time;

    // Report norm and time used
    printf("Created a vector with %d entries, x[i] = sin(i).\n", N);
    printf("Array was created as an automatic array.\n");
    printf("The norm of this vector is %10.8f\n", norm);
    printf("Calculation took %f seconds\n", (float)time/CLOCKS_PER_SEC);
}
