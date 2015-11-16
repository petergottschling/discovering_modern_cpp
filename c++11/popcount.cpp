#include <iostream>
#include <cstddef>
#include "print_compiler.hpp"

using namespace std;

constexpr size_t popcount(size_t x)
{
    return x == 0 ? 0 : popcount(x & x-1) + 1;
}



int main (int argc, char* argv[]) 
{
    print_compiler();

    constexpr size_t bits= popcount(0x5555);
    static_assert(popcount(0x5555) == 8, "popcount(0x5555) != 8");

    return 0;
}

