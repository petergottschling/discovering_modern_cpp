#define NDEBUG
#include <cassert>
#include <iostream>
#include "print_compiler.hpp"

using namespace std;

double square_root(double x)
{
    double result= -3.0;
    assert(result >= 0.0);
    assert(result >= 0.0 && "Value must be non-negative");
    return result;
}


int main (int argc, char* argv[]) 
{
    print_compiler();

    square_root(9);

    return 0;
}

