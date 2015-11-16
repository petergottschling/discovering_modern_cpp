#include <fstream>
#include "print_compiler.hpp"



int main (int argc, char* argv[]) 
{
    print_compiler();
    std::ofstream myfile("example.txt");
    myfile << "Writing this to a file. " << std::endl;

    return 0;
}
