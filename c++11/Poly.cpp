// Bjarne p. 658  

#include <iostream>
#include <typeinfo>
#include "print_compiler.hpp"

struct Poly {
    virtual void f() {}
};

struct Non_poly {};

struct D1
  : Poly
{};

struct D2
  : Non_poly
{};

void f(Non_poly& npr, Poly& pr)
{
    std::cout << typeid(npr).name() << '\n';
    std::cout << typeid(pr).name() << '\n';
}

int main (int argc, char* argv[]) 
{
    print_compiler();
    D1 d1;
    D2 d2;
    
    f(d2, d1);
    // f(*static_cast<Poly*>(nullptr), *static_cast<Null_poly*>(nullptr));

    return 0 ;
}

