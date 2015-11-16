#include <iostream>
#include <sstream>
#include "print_compiler.hpp"

using namespace std;

template <typename Target= string, typename Source= string>
Target to(Source arg)
{
    stringstream interpreter;
    Target result;
    
    if (!(interpreter << arg)
	|| !(interpreter >> result)
	|| !(interpreter >> std::ws).eof())
	throw "->";
    return result;
}

int main (int argc, char* argv[]) 
{
    print_compiler();

    auto x1= to<string, double>(1.2);
    auto x2= to<string>(1.2);
    auto x3= to<>(1.2);
    auto x4= to(1.2);

    return 0; 
}
