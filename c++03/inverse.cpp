#include <iostream>
#include <cassert>
#include <boost/numeric/mtl/mtl.hpp>

using namespace std;
using namespace mtl;

typedef dense2D<double> Matrix;
// using Matrix= dense2D<double>; // C++11

dense_vector<double> unit_vector(unsigned k, unsigned n)
{
    dense_vector<double>  e_k(n, 0.0);
    e_k[k]= 1.0;

    // for (unsigned i= 0; i < n; ++i)
    // 	   e_k[k]= static_cast<double>(i == k);
    // for (unsigned i= 0; i < n; ++i)
    // 	   e_k[k]= i == k; 

    return e_k;
}


Matrix inverse_upper(const Matrix& U)
{
    const unsigned n= num_rows(U);
    Matrix Inv(n, n);
    Inv= 0.0;
    for (unsigned k= 0; k < n; k++) { 
	irange  r(0,k+1);
	Inv[r][k]= upper_trisolve(U[r][r], unit_vector(k, k+1));
    }
    return Inv;
}

Matrix inverse_lower(const Matrix& L)
{
    Matrix T(trans(L));
    return Matrix(trans(inverse_upper(T)));
}


Matrix inverse(const Matrix& A)
{
    const unsigned n= num_rows(A);
    if (num_cols(A) != n)
	throw "Matrix must be square";

    Matrix Inv(n, n);

    Matrix LU(A); // Kopie von A
    dense_vector<unsigned>  Pv(n);
    lu(LU, Pv);
    compressed2D<unsigned> P(permutation(Pv));
    Matrix I(mat::identity(n, n)), L(I + strict_lower(LU)), U(upper(LU));
    Inv= inverse_upper(U) * inverse_lower(L) * P;

    return Inv;
}


int main (int argc, char* argv[]) 
{
    const unsigned size= 3;
    const double   eps= 0.001; // C++11: constexpr double   eps= 0.001; 
    Matrix   A(size, size);
    A= 4, 1, 2,
       1, 5, 3,
       2, 6, 9;

    cout << "A ist\n" << A;

    Matrix LU(A); // Kopie von A
    dense_vector<unsigned>  Pv(size);
    lu(LU, Pv);
    Matrix P(permutation(Pv));

    cout << "LU ist\n" << LU;
    cout << "Permutation vector is " << Pv << "\nPermutationsmatrix ist\n" << P;

    Matrix I(mat::identity(size, size)), L(I + strict_lower(LU)), U(upper(LU));
    cout << "L ist\n" << L << "U ist\n" << U;

    Matrix UI(inverse_upper(U));
    cout << "Inverse von U ist\n" << UI << "UI * U ist\n" << Matrix(UI * U);
    assert(one_norm(Matrix(UI * U - I)) < eps);

    Matrix LI(inverse_lower(L));
    cout << "Inverse von L ist\n" << LI << "LI * L ist\n" << Matrix(LI * L);
    assert(one_norm(Matrix(LI * L - I)) < eps);


    Matrix AI(UI * LI * P);
    cout << "Inverse von A ist\n" << AI << "AI * A ist\n" << Matrix(AI * A);
    assert(one_norm(Matrix(AI * A - I)) < eps);
    
    Matrix A_inverse(inverse(A));
    cout << "Inverse von A ist\n" << A_inverse << "A_inverse * A ist\n" << Matrix(A_inverse * A);
    assert(one_norm(Matrix(A_inverse * A - I)) < eps);

    return 0 ;
}
