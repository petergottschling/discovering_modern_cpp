#include <iostream>
#include "print_compiler.hpp"



int main (int argc, char* argv[]) 
{
    print_compiler();

    std::cout << sizeof(5l) << ' ' << sizeof(5.f) << '\n';
    std::cout << sizeof(5l+5.f) << ' ' << sizeof(5.f) << '\n';

    long l= 1234567890123;
    long l2= l + 1.0f - 1.0;
    long l3= l + (1.0f - 1.0);
    int i= l + 1.0f - 1.0;
    std::cout << "l2 = " << l2 << '\n';
    std::cout << "l3 = " << l3 << '\n';
    std::cout << "i = " << i << '\n';

    return 0 ;
}

