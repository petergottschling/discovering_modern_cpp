#include <iostream>

extern void f();
extern int i;
extern const int c;

int main (int argc, char* argv[]) 
{
    f();
    std::cout << "i is " << i << '\n';
    // std::cout << "c is " << c << '\n'; c has internal linkage

    return 0 ;
}

