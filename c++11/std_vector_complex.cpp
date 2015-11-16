#include <iostream>
#include <complex>
#include <vector>
#include "print_compiler.hpp"

using vector= std::vector<std::complex<double>>;

inline std::ostream& operator<<(std::ostream& os, const vector& v)
{
    os << "[";
    for (unsigned i= 0; i < v.size(); i++)
	os << v[i] << (i+1 < v.size()? ", " : "");
    return os << "]";
}

template <typename T>
inline std::ostream& operator<<(std::ostream& os, const std::complex<T>& c)
{
    return os << "(" << real(c) << ", " << imag(c) << ")";
}

int main (int argc, char* argv[]) 
{
    print_compiler();

    vector v1= {2};
    vector v1d= {{2}};

    vector v2= {2, 3};
    vector v2d= {{2, 3}};
    vector v2dc= {{2, 3}, };
    vector v2w= {{2}, {3}};
    vector v2c= {{2, 3, }};
    vector v2dw= {{{2}, {3}}};

    vector v3= {2, 3, 4};
    vector v3d= {{2, 3, 4}};

    std::cout << "v1 is " << v1 << std::endl;
    std::cout << "v1d is " << v1d << std::endl;

    std::cout << "v2 is " << v2 << std::endl;
    std::cout << "v2d is " << v2d << std::endl;
    std::cout << "v2dc is " << v2dc << std::endl;
    std::cout << "v2w is " << v2w << std::endl;
    std::cout << "v2c is " << v2c << std::endl;
    std::cout << "v2dw is " << v2dw << std::endl;
 
    std::cout << "v3 is " << v3 << std::endl;
    std::cout << "v3d is " << v3d << std::endl;

    return 0 ;
}

