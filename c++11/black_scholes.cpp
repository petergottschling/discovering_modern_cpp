#include <iostream>
#include <random>
#include "print_compiler.hpp"

using namespace std;

int main () 
{
    // print_compiler();

    default_random_engine re(random_device{}());
    normal_distribution<> normal;

    const double mu= 0.05, sigma= 0.3, delta= 0.5, years= 20.01, 
                 a= sigma * sqrt(delta), 
	         b= delta * (mu - 0.5 * sigma * sigma); 
    vector<double>  s= {345.2};    // Start with initial price

    for (double t= 0.0; t < years; t+= delta)
	s.push_back( s.back() * exp(a * normal(re) + b) )
}

