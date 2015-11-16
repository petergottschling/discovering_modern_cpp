#include <iostream>
#include "print_compiler.hpp"
#include "multiref.hpp"

using namespace std;

int main (int argc, char* argv[]) 
{
    print_compiler();
    fix_pi();
    cout << "pi = " << pi << endl;

    tprint(2);
    std::cout << "&square is " << (void*)square << "\n";
    print_address();

    return 0;
}

