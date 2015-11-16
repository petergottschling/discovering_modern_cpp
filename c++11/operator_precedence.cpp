#include <iostream>
#include <typeinfo>

class dings
{
  public:
    dings(int i= 0) : i(i) {}

    dings& operator=(const dings& that) & { i= that.i; return *this; }

    dings operator-() const { std::cout << "member unary -\n"; return *this; }
    dings operator+() const { std::cout << "unary +\n"; return *this; }

    dings& operator++() & { std::cout << "pre-increment\n"; i++; return *this; }
    // dings operator++(int) & { dings tmp(*this); std::cout << "post-increment\n"; i++; return tmp; }
    dings* operator&() & { std::cout << "operator&\n"; return this; }

    int i;
};

// dings operator-(const dings& d) { std::cout << "free unary -\n"; return d; }
int operator*(dings& d) { return 3; }
// dings& operator=(dings& d, int i) { d.i= i; return d; }
dings operator++(dings& d, int i) { dings tmp(d); std::cout << "post-increment\n"; d.i++; return tmp; }

dings operator+(const dings& x, const dings& y)
{
    return dings(x.i + y.i);
}


int main (int argc, char* argv[]) 
{ 
    int i;
    std::cout << "typeid(i) " << typeid(i).name() << '\n';

    i= 3;
    // ++i++;
    std::cout << "i is " << i << '\n';

    // dings ddd;
    // ddd= i++;

    
    double d= 5.3, e= 2.9;
    //std::cout << "d%e is " << d%3 << '\n';
    std::cout << "d is " << ++d << '\n';

    std::cout << "d % e = " << -9 % 4u  << '\n';
    
    dings di, d2(7), d3(8);
    -di;
    +di;
    di++;

    di.i= 3;
    // ++di++;
    std::cout << "di.i is " << di.i << '\n';
    &di;

    *di;

    // (di + di)= d2;

    return 0 ;
}
