#include <iostream>
#include <tuple>
#include <functional>
#include <typeinfo>
#include "print_compiler.hpp"

using namespace std;

struct dings
{
    dings() : i{}, p{} {};
    dings(int i) : i(i), p(new int) {}

    dings(const dings& that) : i(that.i), p(new int) { i= that.i; std::cout << "Copy constructor\n"; }
    dings(dings&& that) : i(that.i), p(that.p) { that.p= nullptr; std::cout << "Move constructor\n"; }

    ~dings() { delete p; }

    dings& operator=(const dings& that) { i= that.i; return *this; }
    dings& operator=(dings&& that) { p= that.p; that.p= nullptr; i= that.i; return *this; }

    int i;
    int* p;
};

tuple<dings, dings> f(bool c) 
{ 
    dings d(3), e(1);
    if (c)
	d.i= 2;
    std::cout << "d.p = " << d.p << '\n';
    std::cout << "e.p = " << e.p << '\n';

    // return forward_as_tuple(d, e);
    // cout << "Type is " << typeid(make_tuple(d, move(e))).name() << '\n';
    return make_tuple(move(d), move(e));
    // return make_tuple(dings(1), dings(2));
}

struct matrix {};
struct vector {};

tuple<matrix, vector> lu(const matrix& A)
{
    matrix LU;
    vector p;

#if 0
    assert(num_cols(A) == num_rows(A));
    unsigned n= num_rows(A);
    matrix LU(A);
    vector p(n);
    iota(p);

    for (unsigned i= 0; i < n-1; i++) {
	irange r(i+1, imax), ir(i, i+1); // Intervals [i+1, n-1], [i, i]
	unsigned rmax= max_abs_pos(A[irange(i, imax)][ir]).first + i;
	swap_row(A, i, rmax); 
	swap_row(P, i, rmax);
	
	if(abs(A[i][i]) == 0) throw matrix_singular();
       
	A[r][i]/= A[i][i];            // Scale column i
	A[r][r]-= A[r][i] * A[i][r];  // Decrease bottom right block of matrix
    }    
#endif
    return tuple<matrix, vector>(LU, p);
    // return make_tuple(LU, p);
    // return make_tuple(move(LU), move(p));
}


int main (int argc, char* argv[]) 
{
    print_compiler();

    // dings d, e;
    // tie(d, e)= f(true);

    auto td= f(true);
    auto d= get<0>(move(td));
    auto e= get<1>(move(td));

    std::cout << "d.i = " << d.i << '\n';
    std::cout << "e.i = " << e.i << '\n';

    std::cout << "d.p = " << d.p << '\n';
    std::cout << "e.p = " << e.p << '\n';

    matrix A;
    
    matrix LU;
    vector p;
    tie(LU, p)= lu(A);

    // tuple<matrix, vector> t= lu(A);
    // matrix LU= get<0>(t);
    // vector p= get<1>(t);

    // auto t= lu(A);
    // auto LU= get<0>(t);
    // auto p= get<1>(t);

    return 0;
}
