#include <iostream>
#include <fstream>
#include <string>
#include "print_compiler.hpp"

using namespace std;

void with_io_exceptions(ios& io)
{    io.exceptions(ios_base::badbit | ios_base::failbit); }

int main (int argc, char* argv[]) 
{
    print_compiler();

    cin.exceptions(ios_base::badbit | ios_base::failbit);
    cout.exceptions(ios_base::badbit | ios_base::failbit);

    std::ofstream outfile;
    with_io_exceptions(outfile);
    outfile.open("fs.txt");

    outfile << "Goodbye cruel world\nI'm leaving you today\nGoodbye\nGoodbye\n";
    outfile.close();

    std::ifstream infile;
    with_io_exceptions(infile);
    infile.open("fs.txt");

    std::string s1, s2;
    infile >> s1 >> s2;
    std::cout << "s1 = " << s1 << ", s2 = " << s2 << "\n";



    return 0;
} 

