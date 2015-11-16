#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include "print_compiler.hpp"

using namespace std;

struct no_seven {};
struct one_seven {};

int main (int argc, char* argv[]) 
{
    print_compiler();
    vector<int> seq= {3, 4, 7, 9, 2, 5, 7, 8};
    auto it= find(seq.begin(), seq.end(), 7); // first 7
    if (it == seq.end()) 
	throw no_seven{};
    auto end= find(it+1, seq.end(), 7); // second 7
    if (end == seq.end()) 
	throw one_seven{};
    for (; it != end+1; ++it)
	cout << *it << ' ';
    cout << '\n';

    return 0;
}

