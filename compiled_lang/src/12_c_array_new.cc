// *************************************************************************************************
// Harvard Applied Math 205 - Fall 2021.
// Introduction to Compiled Languages
// *************************************************************************************************
// Example of initializing a C-style array in C++ created with operator new.
// Show how to access the array as a pointer.
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
     // Declare an array of N doubles; this time, use operator new instead of an automatic array
    double* x = new double [N];
    // Declare a pointer to double pointing to the start of the array
    // ptr is the SAME THING as x for all intents and purposes!
    // C and C++ arrays are almost the same as pointers.
    double* ptr = x;
    // norm2 is the accumulated squared norm of the vector entries
    double norm2 {0.0};

    // Time the operation to initialize array con compute veector norm
    clock_t time = clock();
    // ptr++ increment the pointer by 1 address
    for(int i=0; i<N; i++, ptr++)
    {
        // Set the value pointed to by ptr to sin(i)
        double t {static_cast<double>(i)};
        *ptr = sin(t); 				
        // Add up the square of each value
        // This statement shows that you can recover x with the expression (*ptr)
        norm2 += (*ptr) * (*ptr);
        // In a "real" (non-teaching) program, you would be more likely to write something like
        // norm2 += (t*t);
    }
    // Calculate the norm from the accumulated squared norm by taking its square root
    double norm {sqrt(norm2)};
    time = clock() - time;

    // Report norm and time used
    printf("Created a vector with %d entries, x[i] = sin(i).\n", N);
    printf("Array was created using operator new, access was via pointers.\n");
    printf("The norm of this vector is %10.8f\n", norm);
    printf("Calculation took %f seconds\n", (float)time/CLOCKS_PER_SEC);

    // Delete the array; done with it now
    delete [] x;
}
