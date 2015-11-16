#include <iostream>
#include <cstdlib>
#include "print_compiler.hpp"

using namespace std;

int main (int argc, char* argv[]) 
{
    print_compiler();
    int i= 3;
    if (argc > 1) 
	i= atoi(argv[1]);

    asm ( "# start here" );
    int j= i / 64;
    asm ( "# end here" );
    cout << "j = " << j << endl;

    return 0;
}

