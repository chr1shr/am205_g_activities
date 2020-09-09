#include <stdlib.h>
#include <stdio.h>
#include <time.h>
using namespace std;

// This example isn't particularly smartly written
// I have a plain old double for loop to do a dot product of a matrix and a vector
// But the magic is in how compiler can recognize bits of the code that can be optimize
// And do the work for us (sometimes) to improve performance

// Try compiling with optimization flag -O[...]
// The options can be -O, -O1, -O2, -O3, -Ofast (a bit racy)
// Try the following, and compare with python np.dot
// g++ -O3 -o test speed_test.cc
int main() {
    int N = 10000;
    int S = 100;
    clock_t t = clock();
    double ** A = new double * [N];
    double * b =  new double [N];
    double * y =  new double [N];
    for(int i=0;i<N;i++) {
        b[i] = rand();
        A[i] = new double [N];
        for(int j = 0;j<N;j++){
            A[i][j] = rand();
        }
    }
    t = clock() - t;
    printf("We use %f seconds for initialization\n", (float)t/CLOCKS_PER_SEC);

    t = clock();
    // Repeat for S times
    for(int s = 0; s < S; s++) {
        // This double for loop is the equivalent of np.dot (A, b)
        for(int i=0;i<N;i++) {
            y[i] = 0;
            for(int j=0;j<N;j++) {
                y[i] += A[i][j] * b[j];
            }
        }
    }
    t = clock() - t;
    printf("Matrix vector dot product of size %d, repeated %d times, took %8.7f seconds\n", N, S, (float)t/CLOCKS_PER_SEC);
}
