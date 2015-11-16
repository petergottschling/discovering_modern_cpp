#include <iostream>
#include <fstream>
#include <string>

// using namespace std;

// int f(ostream& o) { ...}

int main () 
{
    std::ofstream outfile;
    outfile.open("f.txt");

    int i= 5, j; 
    outfile << i << "\n" << std::endl;
    outfile.close();

    std::ifstream infile("f.txt");

    infile >> j;
    std::cout << "j = \n" << j << "\n";

    return 0 ;
}
