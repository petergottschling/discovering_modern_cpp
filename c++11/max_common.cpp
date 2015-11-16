#include <iostream>
#include <type_traits>

#if 0
template <typename T>
inline T max(T x, T y)
{
    return x < y ? y : x;
}
#endif

template <typename T, typename U>
inline typename std::common_type<T, U>::type 
max(T x, U y)
{
    typename std::common_type<T, U>::type x1(x), y1(y);
    return x1 < y1 ? y1 : x1;
}

#if 0
template <typename T, typename U>
inline auto
max(T x, U y) -> decltype(x + y)
{
    decltype(x + y) x1(x), y1(y);
    return x1 < y1 ? y1 : x1;
}
#endif

int main (int argc, char* argv[]) 
{
    std::cout << max(8, 9) << '\n';
    std::cout << max(8, 9.3) << '\n';

    return 0 ;
}
