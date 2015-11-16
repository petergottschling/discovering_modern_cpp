#include <iostream>
#include <cmath>

template <long N>
struct fibonacci
{
    static const long value= fibonacci<N-1>::value + fibonacci<N-2>::value;
};

template <>
struct fibonacci<0>
{
    static const long value= 1;
};

template <>
struct fibonacci<1>
{
    static const long value= 1;
};

long inline fibonacci2(long n)
{
    return n < 2 ? 1 : fibonacci2(n-1) + fibonacci2(n-2);
}

int main (int argc, char* argv[]) 
{
    std::cout << fibonacci<45>::value << '\n';
    std::cout << 1836311903 << '\n';
    std::cout << fibonacci2(45) << '\n';

    return 0 ;

}
