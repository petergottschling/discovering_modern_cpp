#include <iostream>
#include <fstream>
#include <string>
#include "print_compiler.hpp"

using namespace std;

int main (int argc, char* argv[]) 
{
    print_compiler();

    std::ifstream infile;
    std::string filename{"some_missing_file.xyz"};
    bool opened= false;
    while (!opened) {
	infile.open(filename);
	if (infile.good()) {
	    opened= true;
	} else {
	    std::cout << "The file '" << filename << "' doesn't exist, give a new file name: ";
	    std::cin >> filename;
	}
    }

    int i;
    double d;
    infile >> i >> d;

    if (infile.good())
	std::cout << "i is " << i << ", d is " << d << '\n';
    else
	std::cout << "Could not correctly read the content.\n";
    infile.close();

    return 0;
} 

