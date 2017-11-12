#include <iostream>
#include <cmath>
#include <complex>
#include "print_compiler.hpp"

// http://yihui.name/en/2007/09/process-of-minimization-by-gradient-descent/
// xie@yihui.name

using namespace std;
using cdouble= complex<double>;

double f(cdouble z)
{
    double x= real(z);
    return x * x + 3 * sin(imag(z));
}

cdouble g(cdouble z)
{    
    return {2.0 * real(z), 3.0 * cos(imag(z))}; 
}

template <typename Value, typename P1, typename P2, typename F, typename G>
Value gradient_descent(Value x, P1 s, P2 eps, F f, G g)
{
    auto val= f(x), delta= val;
    do {
	x-= s * g(x);
	auto new_val= f(x);
	delta= abs(new_val - val);
	val= new_val;
    } while (delta > eps);
    return x;
}

int main (int argc, char* argv[]) 
{
    print_compiler();

    cdouble z(-6, 1);
    auto nz= gradient_descent(z, 0.05, 0.001, f, g);
    cout << "Found local minimum at (" <<  real(nz)<< ", " << imag(nz) << ")\n";

    return 0;
}

