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
    outfile.open("f.txt");

    double o1= 5.2, o2= 6.2; 
    outfile << o1 << o2 << std::endl;
    // outfile << -5 << ' ' << i << std::endl;
    outfile.close();

    std::ifstream infile;
    with_io_exceptions(infile);
    infile.open("f.txt");

    int  i1, i2;
    char c= 'x';
    infile >> i1 >> c >> i2;
    std::cout << "i1 = " << i1 << ", i2 = " << i2 << "\n";


#if 0
    int j= 123, k= 123;
    // int oldpos= infile.tellg();
    cout << "pos is " << infile.tellg() << '\n';
    infile >> j;
    // cout << "pos is " << infile.tellg() << '\n';
    // infile >> k;
    // cout << "pos is " << infile.tellg() << '\n';
    // infile >> c;
    // cout << "pos is " << infile.tellg() << '\n';
    // int newpos= infile.tellg();
    cout << "Good bit is " << infile.good() << ".\n";
    // cout << "oldpos = " << oldpos << ", newpos = " << newpos << '\n';
    std::cout << "j = " << j << ", k = " << k << "\n";

    cout << "sizeof(int) " << sizeof(int) << '\n';
#endif 

    return 0;
} 

/* 
   5 -> 5
   -5 -> 4294967291
   .3 -> 0 (1 char), next unsigned input exception
   2.3 -> 2 (1 char), next unsigned input exception
   a -> exception


*/
