#include <iostream>

// static // would not be find in other translation units
void f()
{
    std::cout << "In f().\n";
}

int i= 7;
const int c= 8;
