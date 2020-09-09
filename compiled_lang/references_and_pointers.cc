// AM205 Fall 2020
// Intro to compiled language workshop
// Instrs. Luna & Baptiste

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

int main(){

    // Let's create two numbers
    int number = 10;
    int secondNumber =20;

    //##############
    // References
    //##############

    // Let ref be the reference (alias) of variable number
    int &ref = number;
    printf("number = %d ; ref = %d\n", number, ref);

    // Since "ref" is "number", if we change one, we change the other
    ref = 1000;
    printf("Change ref to be 1000, number = %d, ref = %d\n", number, ref);

    // It's not allowed to reasigned a reference to another variable
    // So the line below would change the value of "ref" and "number"
    // but it doesn't change which piece of memeory "ref" is pointing to
    ref = secondNumber;
    printf("Set ref to be secondNumber, first number = %d, second number = %d,  ref = %d\n", number, secondNumber, ref);

    // So if we change "ref", we are still changing "number", but "secondNumber" is unchanged
    ref = 1000;
    printf("Modify ref to be 1000, first number = %d, second number = %d, ref = %d\n", number, secondNumber, ref);

    //##############
    // Pointers
    //##############

    // To declare and initialize a pointer, we need * in front of the variable name "np"
    // on the left, and & operator on the right hand side, to get the address of "number"
    int * np = &number;
    printf("The address of my pointer is %p, the value stored is %d\n", np, *np);

    // Use * again as the "derefernce" operator to get the value stored at the address
    *np = 999;

    // Changing the value of the memory "np" is pointing to
    // also changes the value of "number", since they are the same physical memory
    printf("Change value pointed to by np to 999, the variable number = %d,  pointer points to %d\n", number, *np);

    // a pointer can be reassigned to another address, unlike a reference variable
    np = &secondNumber;
    printf("After changing pointer to point to second number, first number = %d, second number = %d, and  pointer points to %d\n", number, secondNumber, *np);
}
