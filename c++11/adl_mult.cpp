#include <iostream>
#include "print_compiler.hpp"

namespace rocketscience { 
    namespace mat {
	struct sparse_matrix {};
	struct dense_matrix {};
	struct uber_matrix {};
	
	template <typename Scalar, typename Matrix>
	Matrix operator*(const Scalar& a, const Matrix& A) { ... }
    }
    namespace vec {
	struct sparse_vector {};
	struct dense_vector {};
	struct uber_vector {};

	template <typename Scalar, typename Vector>
	Vector operator*(const Scalar& a, const Vector& x) { ... }

	template <typename Matrix, typename Vector>
	Vector operator*(const Matrix& A, const Vector& x) { ... }
    }
}

int main (int argc, char* argv[]) 
{
    print_compiler();

    rocketscience::mat::uber_matrix A;
    rocketscience::vec::uber_vector x, y;

    y= A * x; // which overload is selected?

    return 0 ;
}

