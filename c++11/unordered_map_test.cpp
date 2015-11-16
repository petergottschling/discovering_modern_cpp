#include <iostream>
#include <unordered_map>
#include "print_compiler.hpp"

using namespace std;

int main (int argc, char* argv[]) 
{
    print_compiler();

    unordered_map<string, double> constants= {{"e", 2.7}, {"pi", 3.14}, {"h", 6.6e-34}};
    cout << "The Planck constant is " << constants["h"] << '\n';
    constants["c"]= 299792458;
    cout << "The Coulomb constant is " << constants["k"] << '\n';
    cout << "The value of pi is " << constants.find("pi")->second << '\n';
    auto it_phi= constants.find("phi");
    if (it_phi != constants.end())
	cout << "The golden ratio is " << it_phi->second << '\n';
    cout << "The Euler constant is " << constants.at("e") << "\n\n";
    for (auto& c : constants)
	cout << "The value of " << c.first << " is " << c.second << '\n';

    return 0;
}

