#include <iostream>
#include <cmath>
#include <cassert>

// void print(double& x) 
// { std::cout << "non-const" << x << '\n'; }

void print(const double& x) 
{ std::cout <<"const " << x << '\n'; }

double inline square(double x)
{
    //x+= 1.0;
    //print(x);
    return x * x;
}

double inline cubic(const double& x)
{
    // x+= 1.0; // error x cannot be changed
    print(x);
    return x * x * x;
}

int inline power(int x, int exp)
{
    int p= 1.0;
    for (int i= 0; i < exp; i++)
	p*= x;
    return p;
}

int inline power(int x)
{
    return x;
}

int inline divide(int a, int b) 
{ 
    //    assert(b != 0);
    return a/b; 
}

void increment(int& x)
{
    x++;
}

float divide(float a, float b)
{
    return std::floor(a / b);
}

double divide(double a, double b)
{
    return std::floor(a / b);
}

double squareroot(double x)
{
    if (x < 0.0)
	throw "Square root of negative value";
    double t= x;
    for (int i= 0; i < 100; i++)
	t= (t + x/t) / 2.0;

    assert (std::abs(t * t - x) < 0.001);

    return t;
}

double root(double x, int degree= 2)
{
    return x;
}

int main () 
{
    root(3.5, 3);
    root(7.0);

    std::cout << "Square of 5 is " << square(5) << '\n';
    double y= 5.0;
    std::cout << "Cubic of 5 is " << cubic(y) << '\n';
    int x= 3, i= 4;
    std::cout << "3 ^ 4 is " << power(x-i, x+i) << '\n';
    std::cout << "power(x) is " << power(x) << '\n';

    std::cout << "divide(5, 3) " << divide(5, 3) << '\n';
    std::cout << "divide(5.0, 3.0) " << divide(5.0f, 3.0f) << '\n';
    std::cout << "divide(5.0, 3.0) " << divide(5.0, 3.0) << '\n';
    std::cout << "sqrt(5.) is " << squareroot(5.) << '\n';

    increment(x);
    //increment(x + 9);

    return 0 ;
}
