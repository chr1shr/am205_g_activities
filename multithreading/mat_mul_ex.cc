#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <omp.h>

/*****************************************************************/
/*********** Adapted from AM205 Fall 2020 by Nick Derr ***********/
/************ https://github.com/nderr/multithreading ************/
/*****************************************************************/

/** C++ implementation of matrix multiplication using shared
 * memory parallelization. Each takes two arguments:
 * N, such that the system size of the multiplication is 2^N.
 * t, the number of threads to parallelize over. */

// Generate uniform random numbers between -1 and 1
inline double rnd() {
    return -1+2./RAND_MAX*static_cast<double>(rand());
}

/** Performs a matrix multiplication of a random matrix times
 * a random vector of length 2^N, using t threads.
 * \param[in] N log_2(system size)
 * \param[in] t number of OMP threads. */
int main(int argc,char** argv) {

    // Print a syntax message if a command-line argument isn't provided
    if(argc!=3) {
        puts("Usage: ./dot_product N [t]\n");
        puts("  N: vector system is size 2^N (accept int,float)");
        puts("  t: number of OMP threads (optional, accept int)");
        exit(0);
    }

    // Set OMP thread num
    int nt=1;
    // Only do this part if we've compiled with OpenMP
#if _OPENMP

    if (argc==3) {
        // If we have three args, user has specified nt
        nt=atoi(argv[2]);
    } else {
        // Otherwise, use default from OMP_NUM_THREADS
        nt=omp_get_max_threads();
    }
#endif

    // Minimum T for timing purposes
    static const double Tmin=0.5; // half second

    // Pull in vector size, allocate two vectors and a matrix
    int N=pow(2,atoi(argv[1]));
    double *v=new double[N];
    double *w=new double[N];
    double *M=new double[N*N];

    // Fill vectors/matrix with random values
#pragma omp parallel for num_threads(nt)
    for(int i=0;i<N;i++) {
        w[i]=0;
        v[i]=rnd();
        for(int j=0;j<N;j++) M[i+j*N]=rnd();
    }

    // Perform matrix multiplication
    double t0=omp_get_wtime(),T=0;
    int iters=0;

    // Do matrix multiplies for a speficied time
    while(T<Tmin) {

#pragma omp parallel for num_threads(nt)
        for(int i=0;i<N;i++) {
            for(int j=0;j<N;j++) {
                w[i]+=M[i+j*N]*v[j]
            }
        }
        
        T=omp_get_wtime()-t0; // Update time
        iters++; // Count iterations
    }

    // Print time per mat mult
    printf("%g\n",T/iters);

    // Cleanup vectors and matrix
    delete[] v;
    delete[] w;
    delete[] M;
}
