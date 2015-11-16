#include <iostream>
#include <cmath>
#include "print_compiler.hpp"

using namespace std;

constexpr int const_abs(int i)
{
    return i < 0 ? -i : i;
}

constexpr int square_root(int x)
{
    double r= x, dx= x;
    while (const_abs((r * r) - dx) > 0.1) {
	r= (r + dx/r) / 2;
    }
    return static_cast<int>(r);
}

#define version 3

#if version == 1

constexpr bool is_prime(int i)
{
    if (i == 1) return false;
    if (i % 2 == 0) 
	return i == 2;
    for (int j= 3; j < i; j+= 2)
	if (i % j == 0)
	    return false;
    return true; 
}

#elif version == 2

constexpr bool is_prime(int i)
{
    if (i == 1) return false;
    if (i % 2 == 0) 
	return i == 2;
    int max_check= static_cast<int>(sqrt(i)) + 1;
    for (int j= 3; j < max_check; j+= 2)
	if (i % j == 0)
	    return false;
    return true; 
}

#elif version == 3

constexpr bool is_prime(int i)
{
    if (i == 1) return false;
    if (i % 2 == 0) 
	return i == 2;
    int max_check= square_root(i) + 1;
    for (int j= 3; j < max_check; j+= 2)
	if (i % j == 0)
	    return false;
    return true; 
}

#endif





int main (int argc, char* argv[]) 
{
    print_compiler();
    // constexpr double r17= std::sqrt(17);
    // constexpr int c4= std::ceil(r17);

    // for (int i= 0; i < 20; i++)
    // 	square_root(i);

    // Check that it is really computed at compile time
    constexpr bool is_17_prime= is_prime(17);

    // Iterate over the 
    for (int i= 1; i < 20; i++)
    	cout << i << " is " << (is_prime(i) ? "" : "not ") << "prime.\n";

    return 0;
}

