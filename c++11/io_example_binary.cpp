#include <iostream>
#include <fstream>
#include "print_compiler.hpp"

using namespace std;

void with_io_exceptions(ios& io)
{    io.exceptions(ios_base::badbit | ios_base::failbit); }

inline void write_data(std::ostream&) {}

template <typename T, typename ...P>
inline void write_data(std::ostream& os, const T& t, const P& ...p) 
{
    os.write(reinterpret_cast<const char *>(&t), sizeof t);
    write_data(os, p...);
}

inline void read_data(std::istream&) {}

template <typename T, typename ...P>
inline void read_data(std::istream& is, T& t, P& ...p) 
{
    is.read(reinterpret_cast<char *>(&t), sizeof t);
    read_data(is, p...);
}


int main (int argc, char* argv[]) 
{
    print_compiler();

    cin.exceptions(ios_base::badbit | ios_base::failbit);
    cout.exceptions(ios_base::badbit | ios_base::failbit);

    std::ofstream outfile;
    with_io_exceptions(outfile);
    outfile.open("fb.txt", ios::binary);

    double o1= 5.2, o2= 6.2; 
    outfile.write(reinterpret_cast<const char *>(&o1), sizeof o1);
    outfile.write(reinterpret_cast<const char *>(&o2), sizeof o2);

    // write_data(outfile, o1, o2);

    outfile.close();

    std::ifstream infile;
    with_io_exceptions(infile);
    infile.open("fb.txt", ios::binary);

    double  i1, i2;
    // read_data(infile, i1, i2);

    infile.read(reinterpret_cast<char *>(&i1), sizeof i1);
    infile.read(reinterpret_cast<char *>(&i2), sizeof i2);
    std::cout << "i1 = " << i1 << ", i2 = " << i2 << "\n";

    return 0;
} 

