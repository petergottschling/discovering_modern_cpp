#include <iostream>
#include "print_compiler.hpp"

using namespace std;

int main (int argc, char* argv[]) 
{
    print_compiler();
    for (int i= 0; i < argc; ++i)
	cout << argv[i] << '\n';

    if (argc >= 3)
    cout << argv[1] << " times " << argv[2] << " is " 
	 << stof(argv[1]) * stof(argv[2]) << ".\n";


    return 3;
}

