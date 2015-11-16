#include <iostream>
#include <complex>
#include "print_compiler.hpp"

using namespace std;

// template <typename T>
// inline T twice(const T& z)
// {    return 2 * z; }

template <typename T>
inline T twice(const T& z)
{    return T(2) * z; }

// template <typename T>
// complex<T> twice(const complex<T>& z)
// {    return T(2) * z; }

int main () 
{
    print_compiler();

    complex<double> z(3, 5), c;
    c= twice(z);

    return 0;
}

