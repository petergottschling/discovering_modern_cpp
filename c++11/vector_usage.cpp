#include <iostream>
#include <vector>
#include <algorithm>
#include "print_compiler.hpp"

using namespace std;

int main (int argc, char* argv[]) 
{
    print_compiler();

    vector<int> v= {3, 4, 7, 9};
    auto it= find(v.begin(), v.end(), 4);
    cout << "After " << *it << " comes " << *(it+1) << '\n';
    auto it2= v.insert(it+1, 5); // insert value 5 at position 2
    v.erase(v.begin()); // delete entry at position 1
    cout << "Size = " << v.size() << ", capacity = " << v.capacity() << '\n';
    v.shrink_to_fit(); // drop extra entries
    v.push_back(7);
    for (auto i : v)
	cout << i << ",";
    cout << '\n';

    return 0;
}

