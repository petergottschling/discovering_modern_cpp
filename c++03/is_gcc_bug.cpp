#include <typeinfo>
#include <iostream>

using namespace std;

struct plziy {};

struct complex
{
    complex() {}
    complex(plziy) {}
};



int main () 
{
    plziy ppp;
    complex c, cp(ppp), cp2(plziy());

    c= cp;
    // c= cp2; // error no operator=
    cout << "c is " << typeid(c).name() 
	 << ", cp is " << typeid(cp).name() 
	 << ", cp2 is " << typeid(cp2).name() << '\n';

    return 0 ;
}
