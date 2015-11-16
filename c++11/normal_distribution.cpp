#include <iostream>
#include <random>
#include <typeinfo>
#include <functional>
#include "print_compiler.hpp"

using namespace std;

int main () 
{
    print_compiler();

    // default_random_engine re(random_device{}());
    // normal_distribution<> normal;

    // for (int i= 0; i < 6; i++)
    // 	cout << normal(re) << endl;

    auto normal= bind(normal_distribution<>{}, default_random_engine(random_device{}()));
    // auto normal= [re= default_random_engine(random_device{}()), n= normal_distribution<>{}]() mutable { return n(re); }; // C++14

    for (int i= 0; i < 6; i++)
    	cout << normal() << endl;

    // cout << "Type of normal is " << typeid(normal).name() << endl;

    return 0;
}

