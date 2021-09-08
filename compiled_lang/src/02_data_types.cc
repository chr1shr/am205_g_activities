// *************************************************************************************************
// Harvard Applied Math 205 - Fall 2021.
// Introduction to Compiled Languages
// Michael S. Emanuel
// 2021-08-26
// *************************************************************************************************
// Program to demonstrate the most commonly used built-in data types
// Please note that I use brace initialization.
// I am following the style recommended by Bjarne Stroustrop in "The C++ Programming Language" (4th Ed.)
// *************************************************************************************************

// *************************************************************************************************
#include <string>
    using std::string;
#include <fmt/format.h>
    using fmt::print;
#include <numbers>
    using std::numbers::pi;

// *************************************************************************************************
int main()
{
    // Built-in Integral data types
    bool b {true};                      // The bool data type is true or false
    short s {0x7FFF};                   // Short integer; platform dependent, usually 16 bits
    int i {0x7FFFFFFF};                 // Default integer; platform dependent, usually 32 bits
    long li {0x7FFFFFFFFFFFFFFF};       // Long integer; platform dependent, usually 64 bits
    unsigned int ui {0xFFFFFFFF};       // Unsigned flavor of default integer; same size as int

    // Integer types of fixed size
    uint8_t ui8 {0xFF};                 // 8-bit unsigned integer; use this for numbers, not char!
    int16_t i16 {0x7FFF};               // Guaranteed to be 16 bits; signed
    int32_t i32 {0x7FFFFFFF};           // Guaranteed to be 32 bits; signed
    int64_t i64 {0x7FFFFFFFFFFFFFFF};   // Guaranteed to be 64 bits; signed
    uint64_t ui64 {0xFFFFFFFFFFFFFFFF}; // Guaranteed to be 64 bits; unsigned

    // Floating point data types
    float f {pi};                       // The float data type is 32 bit IEEE single precision
    double d {pi};                      // The double data type is 64 bit IEEE double precision
    double err {f-d};                   // Rounding error between float and double

    // Textual data types
    char c {'a'};                       // The char data type is a 1 byte character
    string str {"Hello"};               // Suggestion - use std::string rather than const char*

    // Address of variables
    int * ptri {&i};              // Pointer to integer; 32 or 64 bits based on architecture

    // Report values - built in integral types
    print("Built-In Integral Types:\n");
    print("Type                 : Decimal              : Hex                  : Size\n");
    print("bool b               : {:20} : (0x{:16X}) : {:d}\n", b, b, sizeof(b));
    print("short s              : {:20d} : (0x{:16X}) : {:d}\n", s, s, sizeof(s));
    print("int i                : {:20d} : (0x{:16X}) : {:d}\n", i, i, sizeof(i));
    print("long li              : {:20d} : (0x{:16X}) : {:d}\n", li, li, sizeof(li));
    print("unsigned int ui      : {:20d} : (0x{:16X}) : {:d}\n", ui, ui, sizeof(ui));

    // Report values - fixed size integer types
    print("Integer Types of fixed size:\n");
    print("8 bit uint ui8       : {:20d} : (0x{:16X}) : {:d}\n", ui8, ui8, sizeof(ui8));
    print("16 bit int i16       : {:20d} : (0x{:16X}) : {:d}\n", i16, i16, sizeof(i16));
    print("32 bit int i32       : {:20d} : (0x{:16X}) : {:d}\n", i32, i32, sizeof(i32));
    print("64 bit int i64       : {:20d} : (0x{:16X}) : {:d}\n", i64, i64, sizeof(i64));
    print("64 bit unsigned ui64 : {:20d} : (0x{:16X}) : {:d}\n", ui64, ui64, sizeof(ui64));

    // Report values - floating point types
    print("\nFloating Point Types:\n");
    print("float f    : {:18.16f}. {:d} bytes.\n", f, sizeof(f));
    print("double d   : {:18.16f}. {:d} bytes.\n", d, sizeof(d));
    print("double err : {:18.16f}.\n", err);

    // Report values - textual types
    print("\nTextual types:\n");
    print("char c     : {} ({:d} as an int) ({:d} bytes).\n", c, c, sizeof(c));
    print("string str : {} ({:d} bytes).\n", str, sizeof(str));

    print("\nPointer type:\n");
    print("int * ptri {}. {:d} bytes.\n", static_cast<void*>(ptri), sizeof(pi));
}
