#include <iostream>
#include <set>
#include "print_compiler.hpp"

int main (int argc, char* argv[]) 
{
    print_compiler();
    using namespace std;
    

    set<int> s= {1, 3, 4, 7, 9};
    s.insert(5);
    for (int i= 0; i < 6; ++i)
	cout << i << " appears " << s.count(i) << " time(s).\n";

    for (int i : s)
	cout << i << " is in the set.\n";


    return 0;
}

