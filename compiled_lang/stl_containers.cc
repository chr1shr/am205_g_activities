// AM205 Fall 2020
// Intro to compiled language workshop
// Instrs. Luna & Baptiste

#include <vector>
#include <array>
using namespace std;

int main() {

    //##############
    // Arrays
    //##############
    // declare and initialize an integer array of 10 intergers
    // notice “<>” containing template argumetns, indicating the data type and length of array
    // an advantage of STL arrays is that it knows its own size!
	array<int, 10> myArray = {0, 1 ,2, 3, 4, 5, 6, 7, 8, 9};

    printf("Size of array %lu \n", myArray.size());

    printf("Iterate through an array using at()\n");
    for(int i = 0; i < myArray.size(); i++){
        printf("My array element at %d is %d\n", i, myArray.at(i));
    }

    printf("Iterate through an array using []\n");
    for(int i = 0; i < myArray.size(); i++){
        printf("My array element at %d is %d\n", i, myArray[i]);
    }

    //##############
    // Vectors
    //##############

    // many ways of declaring and initializing a vector of doubles
    // a common thing is an empty vector, no element
    vector<double> myVector1;

    // another way is to use a constructor that takes number of elements, and initial values
    int numElems = 10;
    double initVal = 1E-200;
    vector<double> myVector2 (numElems, initVal); // a vector of 10 doubles, all initially 1E-200

    printf("vector1 %lu vector2 %lu\n", myVector1.size(), myVector2.size());

    printf("Iterate through a vector using an iterator\n");
    vector<double>::iterator iter;
    for(iter = myVector2.begin(); iter < myVector2.end(); iter++) {
        printf("My vector contains elements %f\n", *iter);
    }
}
