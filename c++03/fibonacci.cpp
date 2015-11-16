#include <iostream>
#include <cmath>


template <long N>
struct fibonacci
{
    static const long value= fibonacci<N-1>::value + fibonacci<N-2>::value;
};

template <>
struct fibonacci<1>
{
    static const long value= 1;
};

template <>
struct fibonacci<2>
{
    static const long value= 1;
};

long fibonacci2(long x)
{
    return x < 3 ? 1 : fibonacci2(x-1) + fibonacci2(x-2);
}

int main (int argc, char* argv[]) 
{

    std::cout << fibonacci<45>::value << "\n";
    std::cout << fibonacci2(45) << "\n";

    return 0 ;

}
