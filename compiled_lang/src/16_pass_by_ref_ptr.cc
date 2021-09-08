// *************************************************************************************************
// Harvard Applied Math 205 - Fall 2021.
// Introduction to Compiled Languages
// *************************************************************************************************
// Example of passing arguments by value in a function.
// Contrast with passing arguments by reference or pointer.
// Initially written by Yuexia Luna Lin, AM 205 Fall 2020.
// Revised by Michael S. Emanuel
// 2021-09-01
// *************************************************************************************************

// *************************************************************************************************
// Library dependencies
#include <time.h>
#include <stdio.h>

// *************************************************************************************************
// Not too crazy number of data points, 1MB of memory for array of doubles
constexpr int N {131072};

struct myHugeDataset 
{
    // Member: one array of N doubles
	double data[N]; 
    // Constructor: put consecutive ints into data
    myHugeDataset() 
    {
        for(int i=0; i<N; i++) {data[i] = i;}
    }
};

// *************************************************************************************************
// There are two ways to modifying this function to improve the performance
// You can try to figure them out before the workshop (hint: pass by reference or pass by pointer)
// We will also demo this during the workshop
double compute (const myHugeDataset dataset) 
{
    // just do something, here we simply return the 400th element
	return dataset.data[399];
}

// *************************************************************************************************
int main() 
{
    clock_t time_req;

	myHugeDataset dataset;
    double result;

    time_req = clock();
    for(int i=0;i<1000;i++)
    {
        // passed by value, data is copied every time
        result = compute(dataset); 
    }
    time_req = clock() - time_req;

    printf("We use %f seconds\n", (float)time_req/CLOCKS_PER_SEC);
    printf("The result is %f\n", result);
}
