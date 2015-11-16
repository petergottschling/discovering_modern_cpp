#include <iostream>
#include <set>
#include "print_compiler.hpp"

int main (int argc, char* argv[]) 
{
    print_compiler();
    using namespace std;

    multiset<int> s= {1, 3, 4, 7, 9, 1, 1, 4};
    s.insert(4);
    for (int i= 0; i < 6; ++i)
	cout << i << " appears " << s.count(i) << " time(s).\n";

    return 0;
}

