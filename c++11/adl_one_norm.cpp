#include <iostream>
#include "print_compiler.hpp"

namespace rocketscience { 
    namespace mat {
	struct sparse_matrix {};
	struct dense_matrix {};
	struct uber_matrix {};
	
	template <typename Matrix>
	double one_norm(const Matrix& A) { return 3; }
    }
    namespace vec {
	struct sparse_vector {};
	struct dense_vector {};
	struct uber_vector {};
	
	template <typename Vector>
	double one_norm(const Vector& x) { return 4; }
    }
    // using vec::dense_vector;
    using namespace vec;

    template <typename T>
    double one_norm(const T&) { return 5; }
}

int main (int argc, char* argv[]) 
{
    print_compiler();

    rocketscience::mat::uber_matrix A;
    rocketscience::vec::uber_vector x;

    std::cout << "one_norm(A) = " << one_norm(A) << '\n';
    std::cout << "one_norm(x) = " << one_norm(x) << '\n';

    rocketscience::dense_vector y;
    std::cout << "one_norm(y) = " << one_norm(y) << '\n';

    return 0 ;
}

