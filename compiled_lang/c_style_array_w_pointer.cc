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

     // declare an array of 100 doubles and a pointer to the beginning of the array
    double * myVec = new double [100], *ptr = myVec;
    double norm=0;

    clock_t time = clock();
    for(double x=0;x<100.0;x+=1.0, ptr++){// ptr++ increment the pointer by 1 address
        *ptr = init(x); 				// set the value pointed to by ptr
        norm += (*ptr) * (*ptr);		// add up the square of each value
    }
    norm = sqrt(norm);
    delete [] myVec;
    time = clock() - time;

    printf("The norm of my vector is %10.8f\n", norm); // print out 7.07191497 
    printf("We use %f seconds\n", (float)time/CLOCKS_PER_SEC);

    // What happens if the array is larger, try a larger number e.g. 131072 and see
}

