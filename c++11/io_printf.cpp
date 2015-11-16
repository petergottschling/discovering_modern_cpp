#include <cstdio>
#include "print_compiler.hpp"

int main (int argc, char* argv[]) 
{
    print_compiler();

    double x= 3.6;
    printf("The square of %f is %f\n", x, x*x);
    printf("The square of %6.2f is %14.9f\n", x, x*x);

    // int i= 7;
    // char s[]= "i is %s\n";
    // printf(s, i);
    // printf("i is %s\n", i);

    return 0;
} 

