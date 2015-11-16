#include <iostream>
#include <typeinfo>
#include <type_traits>

template <typename ...P> struct sum_type;

template <typename T, typename ...P>
struct sum_type<T, P...>
{
    typedef decltype(T() + typename sum_type<P...>::type()) type;
};

template <typename T>
struct sum_type<T>
{
    typedef T type;
};

// Since variadic templates are recursive, must have a base case
template <typename T>
inline T sum(T t) { return t; }

template <typename T, typename ...P>
typename std::common_type<T, P...>::type
//typename sum_type<T, P...>::type
inline sum(T t, P ...p)
{
    return t + sum(p...);
}


int main (int argc, char* argv[]) 
{
    auto ss= sum(-7, 3.7f);
    std::cout << "ss is " << ss << " and its type is " << typeid(ss).name() << '\n';

    auto s= sum(-7, 3.7f, 9u, -2.6);
    std::cout << "s is " << s << " and its type is " << typeid(s).name() << '\n';

    auto s2= sum(-7, 3.7f, 9u, -42.6);
    std::cout << "s2 is " << s2 << " and its type is " << typeid(s2).name() << '\n';

    return 0 ;
}
