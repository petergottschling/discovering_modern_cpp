#include <iostream>

using namespace std;

double rough_sqrt(double x)
{
    double s= x;
    for (int i= 0; i < 10; i++)
        s= (s + x/s) / 2.0;
    return s;
}

int main () 
{
    double two= 2.0;
    cout << "Rough sqrt(2.0) = " << rough_sqrt(two) << endl;
    cout << "two is still " << two << endl;
}
