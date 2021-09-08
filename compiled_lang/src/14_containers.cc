// *************************************************************************************************
// Harvard Applied Math 205 - Fall 2021.
// Introduction to Compiled Languages
// *************************************************************************************************
// Example of initializing a C++ vector<double> as a container.
// Initially written by Yuexia Luna Lin, AM 205 Fall 2020.
// Revised by Michael S. Emanuel
// 2021-09-01
// *************************************************************************************************

// *************************************************************************************************
// Library dependencies
#include <vector>
    using std::vector;
#include <cmath>
    using std::sqrt;
// Old style C libraries
#include <stdio.h>
#include <time.h>

// *************************************************************************************************
int main() 
{
    // The size of our vector; known at compile time!
    constexpr int N {100};
     // Declare an vector  of N doubles; this time, use operator new instead of an automatic array
    vector<double> x(N, 0.0);
    // norm2 is the accumulated squared norm of the vector entries
    double norm2 {0.0};

    // Time the operation to initialize array con compute veector norm
    clock_t time = clock();
    for(int i=0; i<N; i++)
    {
        // Set the value we are about to insert into the vector to x[i] = sin(i)
        double t {static_cast<double>(i)};
        // Write sin(i) at position i
        // This statement shows that you can access the i-th element of the vector with x[i].
        // This is what is called an lvalue in C++; you can not only read to it, but also assign to it.
        x[i] = sin(t);
        // Add up the square of each value
        norm2 += x[i]*x[i];
        // In a "real" (non-teaching) program, you would be more likely to write something like
        // norm2 += (t*t);
    }
    // Calculate the norm from the accumulated squared norm by taking its square root
    double norm {sqrt(norm2)};
    time = clock() - time;

    // Report norm and time used
    printf("Created a vector with %d entries, x[i] = sin(i).\n", N);
    printf("A std::vector was created and populated with array members x[i] appearing as lvalues.\n");
    printf("The norm of this vector is %10.8f\n", norm);
    printf("Calculation took %f seconds\n", (float)time/CLOCKS_PER_SEC);

    // We do NOT need to delete the vector!
    // The destructor automatically frees the memory when x drops out of scope.
    // This automatic resource management is one of the best features of standard library containers.
    // Memory leaks are much less common when using the built in containers than with direct
    // calls to operator new and delete.
    // Of course, the library implementation still needs to call these operators.
    // But it's easier to leave this to the best professional programmers to get this right just once...
}
