#include <iostream>
#include <cstdlib>
#include <cmath>

template <long N>
struct static_long
{
    static const long value= N;
};

int main (int argc, char* argv[]) 
{
    const long i= 7, j= 8;

    static_long<i>   si;

    const long k= i + j;
    static_long<k>   sk;

    long ll= 17;
    const long cl= ll;
    // static_long<cl>   scl; // error

    const long ri= std::floor(std::sqrt(i));
    static_long<ri>   sri; // compiles with g++ 4.7 but not 4.6

    // constexpr long cri= std::floor(std::sqrt(i));
    constexpr long ck= i + j;


    return 0 ;
}
