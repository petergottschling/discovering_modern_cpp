#include <iostream>
#include <limits>
#include "our_complex.hpp"
#include "simple_random.hpp"
#include "print_compiler.hpp"

using namespace std;

const double eps= 10 * numeric_limits<double>::epsilon();

inline bool similar(complex x, complex y)
{
    double sum= abs(x) + abs(y);
    if (sum < 1000 * numeric_limits<double>::min())
	return true;
    return abs(x - y) / sum <= eps;
}

struct distributivity_violated {};

inline void test(complex a, complex b, complex c)
{
    if (!similar(a * (b + c), a * b + a * c)) {
	cerr.precision(3);
	cerr << "Test detected that " << a << " * (" << b << " + " << c << ") != "
	     << a  << " * "  << b << " + " << a  << " * " << c << endl;
	cerr.precision(15);
	cerr << "Compared values are: " << a * (b + c) << endl
	     << "                and: " << a * b + a * c << endl;
	throw distributivity_violated();
    }
}

const double from= -10.0, upto= 10.0;

inline complex mypick()
{    return complex(pick(from, upto), pick(from, upto)); }

int main () 
{
    print_compiler();

    const int max_test= 20;
    randomize();
    for (int i= 0; i < max_test; i++) {
	complex a= mypick();
	for (int j= 0; j < max_test; j++) {
	    complex b= mypick();
	    for (int k= 0; k < max_test; k++) {
		complex c= mypick();
		test(a, b, c);
	    }
	}
    }
    return 0;
}

