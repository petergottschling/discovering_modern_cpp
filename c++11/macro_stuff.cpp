#include <iostream>
#include "print_compiler.hpp"

// #define MYLIB_VERSION 104

#define SOMETHING 1
// compile with -D"SQUARE(x)=x*x"
#define SQUARE(x) (x)*(x)

int main (int argc, char* argv[]) 
{
    print_compiler();

#if defined(__GNUC__) && !(MYLIB_VERSION < 100)
    std::cout << "Do some gnu stuff.\n";
#endif

#ifdef __clang__ 
    std::cout << "Do some clang stuff.\n";
#elif defined(__GNUC__) 
    std::cout << "Do some gnu stuff.\n";
#endif

#if SOMETHING == 0
    std::cout << "Less than 100\n";
#else
    std::cout << "Not less than 100\n";
#endif

    std::cout << int(SOMETHING) << " = SOMETHING\n";
    std::cout << "SQUARE(3) = " << SQUARE(3) << "\n";

    return 0 ;
}

