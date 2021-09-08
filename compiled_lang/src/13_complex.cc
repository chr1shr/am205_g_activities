// *************************************************************************************************
// Harvard Applied Math 205 - Fall 2021.
// Introduction to Compiled Languages
// *************************************************************************************************
// Example of initializing initial guesses for Newton Fractal
// Initially written by Yuexia Luna Lin, AM 205 Fall 2020.
// Revised by Michael S. Emanuel
// 2021-09-01
// *************************************************************************************************

// *************************************************************************************************
// Library dependencies
#include <stdio.h>
#include <complex>
    using std::complex;
#include <math.h>
#include <fmt/format.h>
    using fmt::print;

// *************************************************************************************************
// Function declarations
inline int ij2k(int i, int j, int N);

// *************************************************************************************************
int main()
{
    // Half length of the subject of complex plane we will represent; known at compile time
    constexpr double L {4.0};
    // The number of grid points along one dimension; known at compile time
    constexpr int N {17};
    // The grid spacing; known at compile time
    constexpr double dh = (2.0*L) / (N-1.0);

    // Declare and initialize the complex number at the lower left corner
    constexpr std::complex<double> z_corner {-L, -L};
    // Declare an 1D array, which we will use index manipulation to represent a 2D array
    std::complex<double>* initial_guess = new std::complex<double> [N*N];

    // Iterate over row i from 1 to N
    for (int i=0;i<N;i++) 
    {
        // Iterate over column j from 1 to N
        for (int j=0;j<N;j++) 
        {
            // The complex number z we want to save in this slot
            complex z = z_corner + complex<double>(dh*i, dh*j);
            // Save z into the array index k corresponding to (i, j)
            int k {ij2k(i, j, N)};
            initial_guess[k] = z;
            // Report (i,j) entry
            print("Matrix entry ({:i}, {:j}} = ({:+4.2f} {:+4.2f}i)", i, j, z.real(), z.imag());
        }
    }

    // Done with complex array, delete it
    delete [] initial_guess;
}

// *************************************************************************************************
// Imagine a 2D NxN array, we take the second row and put it behind the first row, 
// and take the third and put it behind the second row, so on and so forth.
// In the end, we have 1D array of length NxN.
// To get the (i,j) element in the original 2D array,
// we will need to multiply the row index by N, and add the column index,
// i.e. index_{1D} = i*N + j.
// As an aside, this indexing schems is typically called "row major."
inline int ij2k(int i, int j, int N)
{
    return N*i + j;
}
