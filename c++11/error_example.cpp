#include <iostream>
#include "print_compiler.hpp"

using namespace std;

#error "Everything is wrong in line" ## #__LINE__

int main (int argc, char* argv[]) 
{
    print_compiler();

    return 0;
}

