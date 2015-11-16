#include <iostream>
#include <typeinfo>
#include "print_compiler.hpp"



int main (int argc, char* argv[]) 
{
    print_compiler();
    
    std::cout << "typeof nullptr = " << typeid(nullptr).name() << '\n';

    return 0 ;
}

