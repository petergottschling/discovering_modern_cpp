#include <iostream>
#include <memory>
#include "print_compiler.hpp"

using namespace std;

struct X
{
    static int c;
    X() { std::cout << "X [" << ++c << "]  constructed at address " << this << std::endl; }
    ~X() { std::cout << "X [" << c-- << "] destructed at address " << this << std::endl; }
    int i= 3;
};

int X::c= 0;

template <typename T>
void vector_add(unsigned size, const T& v1, const T& v2, T& s)
{
    for (unsigned i= 0; i < size; ++i)
	s[i]= v1[i] + v2[i];
}

std::unique_ptr<double> f()
{    return std::unique_ptr<double>{new double}; }

int main () 
{
    print_compiler();

    unique_ptr<double> dp{new double};
    *dp= 7;

    double* raw_dp= dp.get();

    // shared_ptr<double> sp;
    // sp= dp;

    // double d;
    // unique_ptr<double> dd{&d};

    // double* rp= dp;
    unique_ptr<double> dp2{move(dp)};
    dp2= move(dp);
    // unique_ptr<double> dp2{dp};
    // dp2= dp;

    unique_ptr<double> dp3;
    dp3= f();

    // unique_ptr<double> da{new double[3]};
    unique_ptr<double[]> da{new double[3]};
    for (unsigned i= 0; i < 3; ++i)
    	da[i]= i+2;
    
    unique_ptr<double[]> x{new double[3]}, y{new double[3]}, sum{new double[3]};
    for (unsigned i= 0; i < 3; ++i)
	x[i]= i+2, y[i]= 4-2*i;
    vector_add(3, x, y, sum);
    for (unsigned i= 0; i < 3; ++i)
	std::cout << sum[i] << ", ";

#if 0
    X x;
    std::shared_ptr<X> p1= f();
    std::cout << "After f" << std::endl;
    std::shared_ptr<X> p2(new X);
    
    std::cout << "@p2 = " << p2 << std::endl;

    // std::shared_ptr<X> p3(new X), p4(new X);
    // p3= p4;
    // p4= p3;

    X* px= new X;
    std::shared_ptr<X> p5{px}, p6{px};
#endif




    return 0;
}

