#include <iostream>
#include "print_compiler.hpp"

namespace rocketscience { 
    struct matrix {};
    void initialize(matrix& A) { /* ... */ }
    matrix operator+(const matrix& A, const matrix& B) { return A; }
    template <int N, typename T>
    void f(const T& ) { std::cout << "This is f\n"; }
}

int main (int argc, char* argv[]) 
{
    print_compiler();

    rocketscience::matrix A, B, C, D;
    A= B + C + D;

    A= rocketscience::operator+(rocketscience::operator+(B, C), D);

    //f<3>(A);

    return 0 ;
}

