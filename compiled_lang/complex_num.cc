#include <stdio.h>
#include <complex>
#include <math.h>
#include <iostream>

int main(){
    using namespace std;

    // Half length of the subject of complex plane we will
    // represent
    double L = 4;
    // The number of grid points along one dimension
    int N = 16;
    // The grid spacing
    double dh = 2*L/( (double) (N-1));

    // declare and initialize the complex number at the lower left corner
    std::complex<double> z_corner (-L , -L);
    // declare an 1D array, which we will use index manipulation to
    // represent a 2D array
    std::complex<double>  * initial_guess = new std::complex<double> [N*N];

    // Imagine a 2D NxN array, we take the second row and put it behind
    // the first row, and take the third and put it behind the second row,
    // so on and so forth
    // In the end, we have 1D array of length NxN
    // To get the (j,i) element in the original 2D array,
    // we will need to multiply the row index by N, and add the column index,
    // i.e. index_{1D} = j*N + i.
    for (int j=0;j<N;j++) {
        for (int i=0;i<N;i++) {
            initial_guess [i+j*N] = z_corner + complex<double>(dh*i, dh*j);
            cout << "Row " << j << " Col " << i << " comp. num. " << initial_guess[i+j*N] << endl;
        }
    }

    delete [] initial_guess;
}
