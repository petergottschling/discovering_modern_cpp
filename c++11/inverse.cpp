#include <iostream>
#include <cassert>
#include <boost/numeric/mtl/mtl.hpp>

using namespace std;
using namespace mtl;

using Matrix= dense2D<double>; 

dense_vector<double> inline unit_vector(unsigned k, unsigned n)
{
    dense_vector<double>  e_k(n, 0.0);
    e_k[k]= 1.0;
    return e_k;
}


Matrix inline inverse_upper(const Matrix& U)
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

Matrix inline inverse_lower(const Matrix& L)
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

    Matrix LU(A);                    // copy of A
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
    Matrix   A= {{4, 1, 2},
	         {1, 5, 3},
	         {2, 6, 9}};
    cout << "A is\n" << A;

    Matrix LU(A);                      // copy of A
    dense_vector<unsigned>  Pv(size);
    lu(LU, Pv);
    Matrix P(permutation(Pv));

    cout << "LU is\n" << LU;
    cout << "Permutation vector is " << Pv << "\nPermutation matrix is\n" << P;

    Matrix I(mat::identity(size, size)), L(I + strict_lower(LU)), U(upper(LU));
    cout << "L is\n" << L << "U is\n" << U;

    Matrix UI(inverse_upper(U));
    cout << "Inverse of U is\n" << UI << "UI * U is\n" << UI * U;
    assert(one_norm(Matrix(UI * U - I)) < 0.001);

    Matrix LI(inverse_lower(L));
    cout << "Inverse of L is\n" << LI << "LI * L is\n" << LI * L;
    assert(one_norm(Matrix(LI * L - I)) < 0.001);


    Matrix AI(UI * LI * P);
    cout << "Inverse of A is\n" << AI << "AI * A is\n" << AI * A;
    assert(one_norm(Matrix(AI * A - I)) < 0.001);
    
    Matrix A_inverse(inverse(A));
    cout << "Inverse of A is\n" << A_inverse << "A_inverse * A is\n" << A_inverse * A;
    assert(one_norm(Matrix(A_inverse * A - I)) < 0.001);

    return 0 ;
}
