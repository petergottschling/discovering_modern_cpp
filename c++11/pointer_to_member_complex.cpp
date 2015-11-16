#include <iostream>
#include "print_compiler.hpp"

// adapted from http://en.cppreference.com/w/cpp/language/operator_member_access

class complex
{
  public:
    explicit complex(double rn = 0.0, double in = 0.0) : r(rn), i(in) {}

    double r, i;
};


int main (int argc, char* argv[]) 
{
    print_compiler();

    double complex::* member_focus= &complex::i;

    complex c(7.0, 8.0), c2(9.0);
    complex *p= &c;

    std::cout << "c's focussed member is " << c.*member_focus << '\n';
    std::cout << "p's focussed member is " << p->*member_focus << '\n'; 

    member_focus = &complex::r; // focus on another member
    p= &c2; // point to another complex

    std::cout << "c's focussed member is " << c.*member_focus << '\n';
    std::cout << "p's focussed member is " << p->*member_focus << '\n'; 

    return 0 ;
}

