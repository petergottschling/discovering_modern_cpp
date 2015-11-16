#include <iostream>
#include <typeinfo>

// Since variadic templates are recursive, must have a base case
template <typename T>
inline T sum(T t) { return t; }

template <typename T, typename ...P>
T sum(T t, P ...p)
{
    return t + sum(p...);
}


int main (int argc, char* argv[]) 
{
    auto s= sum(-7, 3.7f, 9u, -2.6);
    std::cout << "s is " << s << " and its type is " << typeid(s).name() << '\n';

    auto s2= sum(-7, 3.7f, 9u, -42.6);
    std::cout << "s2 is " << s2 << " and its type is " << typeid(s2).name() << '\n';

    return 0 ;
}
