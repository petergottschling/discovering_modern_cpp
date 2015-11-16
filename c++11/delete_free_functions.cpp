#include <iostream>
#include "print_compiler.hpp"

using namespace std;

void only_double(double x)
{
    cout << "Only for double!!!\n";
}

template <typename T>
void only_double(T) = delete;

int main (int argc, char* argv[]) 
{
    print_compiler();

    only_double(3.5);
    only_double(3);

    return 0;
}

