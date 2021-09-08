// *************************************************************************************************
// Harvard Applied Math 205 - Fall 2021.
// Introduction to Compiled Languages
// *************************************************************************************************
// Hello World C++ program.
// This program does slightly more than nothing.
// It demonstrates how to use the basic input / output facilities of C++.
//
// Michael S. Emanuel
// 2021-08-26
// *************************************************************************************************

// The #include directive tells the preprocessor to include the text of another C++ source file.
// This is always a "header file" in practice, with declarations (not definitions) of functions.
// This directive includes the declarations for the streaming input / output operations.
#include <iostream>

// The using declaration brings the name cout into the namespace of our file
// cout is the name of the default output stream (text written to terminal in a console program).
using std::cout;

// *************************************************************************************************
int main()
{
    // The traditional "hello world" program is supposed to write out
    // "Hello, world!"
    // However, I think that's a bit boring so I decided to quote a movie I liked.
    cout << "Hello. My name is Inigo Montoya.  You killed my father.  Prepare to die!\n";
    return 0;
}