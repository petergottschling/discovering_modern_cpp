#include <iostream>
#include <typeinfo>
#include <type_traits>

template <typename T>
inline T sum(T t) { return t; }

template <typename ...P, typename T>
typename std::common_type<P..., T>::type
sum(P ...p, T t)
{
    return sum(p...) + t;
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
