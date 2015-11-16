#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include "print_compiler.hpp"

using namespace std;

int main (int argc, char* argv[]) 
{
    std::list<int> seq= {3, 4, 7, 9, 2, 5, 7, 8};
    auto it= find(seq.begin(), seq.end(), 7), it2= it; // first 7
    ++it2;
    auto end= find(it2, seq.end(), 7);                 // second 7
    ++end;
    for (; it != end; ++it)
	std::cout << *it << ' ';
    std::cout << '\n';

    return 0;
}

