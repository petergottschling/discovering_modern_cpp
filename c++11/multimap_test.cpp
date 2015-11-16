#include <iostream>
#include <map>
#include "print_compiler.hpp"

using namespace std;

int main (int argc, char* argv[]) 
{
    print_compiler();

    multimap<int, double> mm= {{3, 1.3}, {2, 4.1}, {3, 1.8}, {4, 9.2}, {3, 1.5}};
    for (auto it= mm.lower_bound(3), end= mm.upper_bound(3); it != end; ++it)
	cout << "The value is " << it->second << '\n';

    return 0;
}

