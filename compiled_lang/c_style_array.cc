// AM205 Fall 2020
// Intro to compiled language workshop
// Instrs. Luna & Baptiste

#include <math.h>
#include <stdio.h>
#include <time.h>

double init(double x) {
	return sin(x); // sin, sqrt, and other common math function are defined in math.h
}

int main() {

    // declare an array of 100 doubles 
    double myVec [131072];
    double norm=0;

    clock_t time = clock();
    for(int i=0;i<131072;i++) {
        double x = (double) i;
        myVec[i] = init(x); 				// set the value of i-th element
        norm += myVec[i] * myVec[i];		// add up the square of each value
    }
    norm = sqrt(norm);
    time = clock() - time;

    printf("The norm of my vector is %10.8f\n", norm); // print out 7.07191497 
    printf("We use %f seconds\n", (float)time/CLOCKS_PER_SEC);

    // What happens if the array is larger, try a very large number e.g. 131072 and see
}

