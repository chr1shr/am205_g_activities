// *************************************************************************************************
// Harvard Applied Math 205 - Fall 2021.
// Introduction to Compiled Languages
// Michael S. Emanuel
// 2021-08-26
// *************************************************************************************************
// Program to demonstrate structures and enumerations.
// Also shows how to use the cool fmt::print function.
// *************************************************************************************************

// *************************************************************************************************
// Library dependencies
#include <string>
    using std::string;
#include <fmt/format.h>
    using fmt::print;

// *************************************************************************************************
// Enumeration for character alignments
enum class Alignment: int {good=1, neutral=2, evil=3};

// *************************************************************************************************
// Structure for Star Wars character attributes
struct Character
{
    string name;
    int age;
    double force_ability;
    Alignment alignment;
};

// *************************************************************************************************
// Declaration of function to print a character
void print_character(Character& c);

// *************************************************************************************************
int main()
{
    // Ages in Episode V according to yodasdatapad.com
    // Force ability and alginment made up by MSE
    // This snippet shows how to assign structure fields by name - helps prevent errors!
    Character luke {.name="Luke Skywalker", .age=22, .force_ability=7.0, .alignment=Alignment::good};
    Character darth {.name="Darth Vader", .age=44, .force_ability=8.0, .alignment=Alignment::evil};
    Character yoda {.name="Yoda", .age=899, .force_ability=9.0, .alignment=Alignment::good};

    // Print out character attributes
    print_character(luke);   
    print_character(darth);
    print_character(yoda);
}

// *************************************************************************************************
// Throwaway function to print character attributes
void print_character(Character& c)
{
    print("********************************************************************************\n");
    print("Name: {:s}\n", c.name);
    print("Age: {:d}\n", c.age);
    print("Force Ability: {:3.1f}\n", c.force_ability);
    string align_str {""};
    switch (c.alignment)
    {
        case Alignment::good:
            align_str = "good";
            break;
        case Alignment::neutral:
            align_str = "neutral";
            break;
        case Alignment::evil:
            align_str = "evil";
            break;
    }
    print("Alignment: {:s}.\n", align_str);
}
