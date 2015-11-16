#include <iostream>
#include <cmath>
#include "print_compiler.hpp"

using namespace std;

constexpr bool is_prime_aux(int i, int div)
{
    return div >= i ? true : 
	(i % div == 0 ? false : is_prime_aux(i, div + 2));
}

constexpr bool is_prime(int i)
{
    return i == 1 ? false :
	(i % 2 == 0 ? i == 2 : is_prime_aux(i, 3));
}


int main (int argc, char* argv[]) 
{
    print_compiler();

    // Check that it is really computed at compile time
    constexpr bool is_17_prime= is_prime(17);

    // Iterate over the 
    for (int i= 1; i < 20; i++)
    	cout << i << " is " << (is_prime(i) ? "" : "not ") << "prime.\n";

    return 0;
}

