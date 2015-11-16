#include <iostream>
#include <fstream>
#include <sstream>
#include "print_compiler.hpp"

void print_something(std::ostream& os)
{
    os << "Hi stream, did you know that 3 * 3 = " << 3 * 3 << std::endl;
}

int main (int argc, char* argv[]) 
{
    print_compiler();

    std::ofstream myfile("example.txt");
    std::stringstream mysstream;

    print_something(std::cout);
    print_something(myfile);
    print_something(mysstream);

    std::cout << "mysstream is: " << mysstream.str(); // newline contained

    return 0;
}

