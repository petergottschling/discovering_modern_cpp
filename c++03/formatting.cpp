#include <iostream>
#include <iomanip>
#include <cmath>



int main (int argc, char* argv[]) 
{
    using namespace std;
    double pi= M_PI;
    
    setprecision(3);

    int old_precision= cout.precision();
    cout << "pi is " << pi << '\n';
    cout << "pi is " << setprecision(16) << pi << '\n';
    cout << "pi is " << setw(30) << pi << '\n';
    cout << "pi is " << setfill('-') << left << setw(30) << pi << '\n';
    cout.setf(ios_base::showpos);
    cout << "pi is " << scientific << pi << '\n';
    cout << "pi is " << right << fixed << setw(30) << pi << '\n';
   
    cout << "63 octal is " << oct << 63 << '\n';
    cout << "63 hexadecimal is " << hex << 63 << '\n';
    cout << "63 decimal is " << dec << 63 << '\n';
    cout << "pi is " << pi << '\n';

    cout << "pi < 3 is " << (pi < 3) << '\n';
    // cout.setf(ios_base::boolalpha);
    cout << "pi < 3 is " << boolalpha << (pi < 3) << '\n';

    // clear all formatting
    cout.unsetf(ios_base::adjustfield | ios_base::basefield | ios_base::floatfield 
		| ios_base::showpos | ios_base::boolalpha);
    cout.precision(old_precision);
    cout << "pi is " << pi << '\n';


    return 0;
}

