#include <iostream>

using std::cout;

// void f(int x) { cout << "int\n"; }
// void f(int y) { cout << "int\n"; } // Redefinition: only arg name different
// long f(int x) { cout << "int\n"; } // Redefinition: only return type different
// void f(int&& x) { cout << "int&&\n"; }
// void f(const int&& x) { cout << "const int&&\n"; } // superseded by int&&
void f(int& x) { cout << "int&\n"; }
void f(const int& x) { cout << "const int&\n"; }

int main (int argc, char* argv[]) 
{
    int       i= 3;
    const int ci= 4;

    f(3);
    f(i);
    f(ci);
}
