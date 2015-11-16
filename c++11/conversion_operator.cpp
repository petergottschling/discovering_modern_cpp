#include <iostream>
#include "print_compiler.hpp"

using namespace std;

struct compressed_matrix;

struct dense_matrix
{
    dense_matrix() = default;
    dense_matrix(const compressed_matrix&) { cout << "Constructor\n"; }

};

struct compressed_matrix
{
    operator dense_matrix() { cout << "Conversion\n"; return dense_matrix(); }

};

void f(const dense_matrix&) {}

int main () 
{
    print_compiler();

    compressed_matrix A;
    f(dense_matrix(A));
    f(A);


    return 0;
}

