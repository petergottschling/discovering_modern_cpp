#include <iostream>
#include <list>
#include <deque>
#include <algorithm>
#include "print_compiler.hpp"

using namespace std;

int main (int argc, char* argv[]) 
{
    print_compiler();

    deque<int> l= {3, 4, 7, 9};
    auto it= find(l.begin(), l.end(), 4), it2= find(l.begin(), l.end(), 7);
    l.erase(it);
    cout << "it2 still points to " << *it2 << '\n';

    return 0;
}

