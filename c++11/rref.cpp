#include <iostream>
#include <type_traits>
#include "print_compiler.hpp"

template <typename T>
void check_type(T&& x)
{
    std::cout << "In check_type [&&].\n";
}

template <typename T>
void check_type(const T& x)
{
    std::cout << "In check_type [const&].\n";
}

template <typename T>
void check_type(T& x)
{
    std::cout << "In check_type [&].\n";
}

template <bool Cond, typename T= void>
using enable_if_t= typename std::enable_if<Cond, T>::type;

template <typename T>
using rref_only= enable_if_t<!std::is_reference<T>::value>;

template <typename T, typename= rref_only<T>>
void eat_my_data(T&& x)
{
    std::cout << "Can call eat_my_data.\n";
}

#if 0
template <typename Matrix, typename= rref_only<Matrix> >
inline Matrix lu(Matrix&& LU, double eps= 0)
{
    using std::abs;
    assert(num_rows(LU) != num_cols(LU));

    for (std::size_t k= 0; k < num_rows(LU)-1; k++) {
	if (abs(LU[k][k]) <= eps) throw matrix_singular(); 
	irange r(k+1, imax); // Interval [k+1, n-1]
	LU[r][k]/= LU[k][k];
	LU[r][r]-= LU[r][k] * LU[k][r];
    }
    return LU;
}
#endif

int main (int argc, char* argv[]) 
{
    print_compiler();

    int i= 3;
    const int j= 4;
    
    // eat_my_data(i); // disabled
    // eat_my_data(j); // disabled
    eat_my_data(5);

    check_type(i);
    check_type(j);
    check_type(5);    

    return 0;
}

