#include <iostream>
#include <typeinfo>
#include "print_compiler.hpp"

void vector_add(unsigned size, const double v1[], const double v2[], double s[])
{
    for (unsigned i= 0; i < size; ++i)
	s[i]= v1[i] + v2[i];
    // std::cout << "Type of v1 is " << typeid(v1).name() << '\n';
}

int main (int argc, char* argv[]) 
{
    print_compiler();

#if 0
    double x[]= {2, 3, 4}, y[]= {4, 2, 0}, sum[3];
    vector_add(sizeof x / sizeof x[0], x, y, sum);
    for (unsigned i= 0; i < 3; ++i)
	std::cout << sum[i] << ", ";
    std::cout << '\n';
#endif
    
    double *x= new double[3], *y= new double[3], *sum= new double[3];
    for (unsigned i= 0; i < 3; ++i)
	x[i]= i+2, y[i]= 4-2*i;
    vector_add(3, x, y, sum);
    for (unsigned i= 0; i < 3; ++i)
	std::cout << sum[i] << ", ";
    std::cout << '\n';


    return 0;
}

