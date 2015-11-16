#include <iostream>
#include "simple_random.hpp"
#include "print_compiler.hpp"

using namespace std;

void random_numbers()
{
    static random_device rd;
    static default_random_engine re(rd());
    poisson_distribution<> pd;

    cout << "Random numbers: ";
    for (int i= 0; i < 4; i++)
	cout << re << (i < 3 ? ", " : "");
    // for (int i= 0; i < 4; i++)
    // 	cout << pd(re) << (i < 3 ? ", " : "");
    cout << '\n';
}

int main () 
{
    print_compiler();

    // randomize();
    // cout << "Now, we roll dies:\n";
    // for (int i= 0; i < 15; i++)
    // 	cout << pick(1, 6) << endl;

    // cout << "\nLet's roll continuous dies now: ;-)\n";
    // for (int i= 0; i < 15; i++)
    // 	cout << pick(1.0, 6.0) << endl;

    random_numbers();
    random_numbers();

    return 0;
}

