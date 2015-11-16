#include <iostream>
#include "print_compiler.hpp"

using namespace std;

template <typename T>
void f(const T& x, const T& y) {}


int main (int argc, char* argv[]) 
{
    print_compiler();

    enum dings { bums, bla };

    f(3, +bla);

    int a[3];
    int *p;

    f(+a, p);

    return 0;
}

