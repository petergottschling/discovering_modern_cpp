#include <iostream>
#include <vector>
#include "print_compiler.hpp"

struct X {};

int main (int argc, char* argv[]) 
{
    print_compiler();

    std::vector<X> v{66};
    std::cout << v.size() << '\n';

    return 0;
}

