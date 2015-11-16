#include <iostream>
#include "print_compiler.hpp"

enum Traffic_light { red, yellow, green };
enum class Warning { green, yellow, orange, red }; 

int main (int argc, char* argv[]) 
{
    print_compiler();

    std::cout << int(red) << '\n';
    std::cout << int(Warning::red) << '\n';

    return 0 ;
}

