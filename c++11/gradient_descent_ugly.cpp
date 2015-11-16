#include <iostream>
#include <cmath>
#include "print_compiler.hpp"

// http://yihui.name/en/2007/09/process-of-minimization-by-gradient-descent/
// xie@yihui.name

using namespace std;

double f(double x, double y)
{
    return x * x + 3 * sin(y);
}

double gx(double x, double y)
{    
    return 2 * x; 
}

double gy(double x, double y)
{
    return 3 * cos(y);
}

void gradient_descent(double* x, double* y, double s, double eps,
		      double(*f)(double, double), 
		      double(*gx)(double, double), 
		      double(*gy)(double, double))
{
    double val= f(*x, *y), delta;
    do {
	*x-= s * gx(*x, *y);
	*y-= s * gy(*x, *y);
	double new_val= f(*x, *y);
	delta= abs(new_val - val);
	val= new_val;
    } while (delta > eps);
}

void gradient_descent_f(double* x, double* y, double s, double eps)
{
    double val= *x * *x + 3 * sin(*y), delta;
    do {
	*x-= s * 2 * *x;
	*y-= s * 3 * cos(*y);
	double new_val= *x * *x + 3 * sin(*y);
	delta= abs(new_val - val);
	val= new_val;
    } while (delta > eps);
}

int main (int argc, char* argv[]) 
{
    print_compiler();

    double x= -6, y= 1;
    gradient_descent(&x, &y, 0.05, 0.001, &f, &gx, &gy);
    cout << "Found local minimum at (" <<  x << ", " << y << ")\n";

    gradient_descent_f(&x, &y, 0.05, 0.001);
    cout << "Found local minimum at (" <<  x << ", " << y << ")\n";

    return 0;
}

