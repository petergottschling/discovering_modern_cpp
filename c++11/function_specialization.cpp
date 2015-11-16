#include <iostream>
#include <cmath>
#include <cassert>

template <typename Base, typename Exponent>
Base inline power(const Base& x, const Exponent& y)
{
    std::cout << "Primary template\n";
    return std::pow(x, y);
}

template <>
double inline power<>(const double& x, const double& y) // Do not use this
{
    std::cout << "Specialized template\n";
    return std::pow(x, y);
}

int inline power(int x, int y)
{
    std::cout << "Overload\n";
    return std::pow(x, y);
}


// Functor version
// template <typename Base, typename Exponent>
// struct power_aux
// {
//     static Base eval(const Base& x, const Exponent& y)
//     {
// 	std::cout << "Primary template\n";
// 	return std::pow(x, y);
//     }
// };

// template <>
// struct power_aux<double, double>
// {
//     static double eval(double x, double y)
//     {
// 	std::cout << "double overload\n";
// 	return std::pow(x, y);
//     }
// };


// template <typename Base, typename Exponent>
// inline Base power(const Base& x, const Exponent& y)
// {
//     return power_aux<Base, Exponent>::eval(x, y);
// }

int main () 
{
    power(3, 4);
    power(3.0, 4.0);
    

    return 0 ;
}
