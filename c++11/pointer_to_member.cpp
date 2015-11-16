#include <iostream>
#include "print_compiler.hpp"

// from http://en.cppreference.com/w/cpp/language/operator_member_access

struct S
{
    mutable int mi;
    int f(int n) { return mi+n; }
    S(int n) : mi(n) {}
};
struct D : public S {
        D(int n) : S(n) {}
};

int main (int argc, char* argv[]) 
{
    print_compiler();

    int S::* pmi = &S::mi;
    int (S::*mpf)(int) = &S::f;
 
    const S s(7);
    // s.*pmi = 10; // cannot modify through mutable
    std::cout << s.*pmi << '\n';
 
    D d(7); // base pointers work with derived object
    D* dp = &d;
    std::cout << (d.*mpf)(7) << ' '
              << (dp->*mpf)(8) << '\n';

    return 0 ;
}

