#include <iostream>
#include <typeinfo>
#include <cmath>

using dings= int;

typedef float float_fun1(float, int);
using float_fun2= float (float, int);

typedef double da1[10];
using da2= double[10];

void print_f1(float_fun1 f)
{
    std::cout << "f(3.3, 3) = " << f(3.3, 3) << '\n';
}

void print_f2(float_fun2 f)
{
    std::cout << "f(3.3, 3) = " << f(3.3, 3) << '\n';
}

float my_pow(float x, int n)
{
    return std::pow(x, n);
}

template <unsigned Order, typename Value>
class tensor {};


template <typename Value>
using vector= tensor<1, Value>;

template <typename Value>
using matrix= tensor<2, Value>;

int main (int argc, char* argv[]) 
{
    dings a= 3;
    std::cout << "a is " << a << '\n';
    std::cout << "type of float_fun1 is " << typeid(float_fun1).name() << '\n';
    std::cout << "type of float_fun2 is " << typeid(float_fun2).name() << '\n';

    std::cout << "type of da1 is " << typeid(da1).name() << '\n';
    std::cout << "type of da2 is " << typeid(da2).name() << '\n';

    std::cout << "type of vector<float> is " << typeid(vector<float>).name() << '\n';
    std::cout << "type of matrix<float> is " << typeid(matrix<float>).name() << '\n';

    print_f1(my_pow);
    print_f2(my_pow);

    return 0 ;
}
