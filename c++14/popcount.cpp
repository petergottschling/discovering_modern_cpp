#include <iostream>
#include <cstddef>
#include <cassert>

#include "print_compiler.hpp"

using namespace std;

constexpr size_t popcount(size_t x)
{
    int count= 0;
    for (; x != 0; ++count)
	x&= x - 1;
    return count;
}


int main (int argc, char* argv[]) 
{
    print_compiler();

    constexpr size_t bits= popcount(0x5555);
    static_assert(popcount(0x5555) == 8, "popcount(0x5555) != 8");    

    return 0;
}

