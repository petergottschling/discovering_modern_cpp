#include <iostream>
#include <complex>
#include "print_compiler.hpp"

using namespace std;

namespace book {

    template <typename T>
    struct abs_functor
    {
	typedef T result_type;

	T operator()(const T& x)
	{
	    // std::cout << "T\n";
	    return x < T(0) ? -x : x;
	}
    };

    template <typename T>
    struct abs_functor<std::complex<T> >
    {
	typedef T result_type;

	T operator()(const std::complex<T>& x)
	{
	    // std::cout << "complex<T>\n";
	    return sqrt(real(x)*real(x) + imag(x)*imag(x));
	}
    };

  #if __cplusplus >= 201402

  #if 0 // clumsy
    template <typename T>
    auto abs(const T& x)
    {
	abs_functor<T> functor_object;
	return functor_object(x);
    }
  #endif

    template <typename T>
    decltype(auto) abs(const T& x)
    {
        return abs_functor<T>()(x);
    }

  #elif __cplusplus >= 201103

    template <typename T>
    auto abs(const T& x) -> decltype(abs_functor<T>()(x))
    {
        return abs_functor<T>()(x);
    }

  #elif __cplusplus >= 199711

    template <typename T>
    typename abs_functor<T>::result_type
    abs(const T& x) 
    {
        return abs_functor<T>()(x);
    }

  #else
    #warning "Your C++ compiler is prehistoric!!!"
  #endif 

}

int main (int argc, char* argv[]) 
{
    print_compiler();

    cout << "abs(-7.3) = " << book::abs(-7.3) << '\n';

  #if __cplusplus >= 201103
    cout << "abs(3-7i) = " << book::abs(std::complex<double>{3, -7}) << '\n';
  #else
    std::complex<double> z(3, -7);
    cout << "abs(3-7i) = " << book::abs(z) << '\n';
  #endif

    return 0;
}

