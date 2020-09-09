// AM205 Fall 2020
// Intro to compiled language workshop
// Instrs. Luna & Baptiste

#include <time.h>
#include <stdio.h>

struct myHugeDataset {
	double data[131072]; // not too crazy number of data points, 1MB of memory
    myHugeDataset () {
        for(int i=0; i<131072; i++) {
            data[i] = i;
        }
    }
};


// There are two ways to modifying this function to improve the performance
// You can try to figure them out before the workshop (hint: pass by reference or pass by pointer)
// We will also demo this during the workshop
double compute ( const myHugeDataset dataset) {
    // just do something, here we simply return the 400th element
	return dataset.data[399];
}

int main() {
    clock_t time_req;

	myHugeDataset dataset;
    double result;

    time_req = clock();
    for(int i=0;i<1000;i++){
        result = compute(dataset); // passed by value, data is copied every time
    }
    time_req = clock() - time_req;

    printf("We use %f seconds\n", (float)time_req/CLOCKS_PER_SEC);
    printf("The result is %f\n", result);
}
