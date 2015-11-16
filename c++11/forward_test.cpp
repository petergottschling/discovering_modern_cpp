#include <iostream>
#include <utility>
#include <typeinfo>
#include "print_compiler.hpp"

using namespace std;

template <typename T>
void g(T&& t, int, float)
{
    cout << "g Rvalue\n";
}

template <typename T>
void g(T& t, int, float)
{
    cout << "g Lvalue\n";
}

template <typename T>
void h(T&& t)
{
    cout << "h Rvalue\n";
}

template <typename T, typename U, typename V>
void f(T&& t, U&& u, V&& v)
{
    // auto s= std::forward<T>(t);
    // cout << "typeof s = " << typeid(s).name() << '\n';
    g(forward<T>(t), forward<U>(u), forward<V>(v));
}



int main (int argc, char* argv[]) 
{
    print_compiler();

    string st{"Hallo"};
    f(st, 3, 4.2f);
    f(string{"Hallo"}, 3, 4.2f);

    h(st);
    h(string{"Hallo"});

    return 0 ;
}
