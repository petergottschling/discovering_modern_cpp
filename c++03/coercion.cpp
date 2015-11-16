#include <iostream>
#include <typeinfo>


int main (int argc, char* argv[]) 
{
    long l= 1234567890123;
    long l2= l + 1.0f - 1.0;   // imprecise
    long l3= l + (1.0f - 1.0); // correct
    int i= l + 1.0f - 1.0;     // too small

    std::cout << "l2 = " << l2 << "\nl + 1.0f = " << typeid(l + 1.0f).name()
	      << "\nl3 = " << l3 << "\ni= " << i << "\n";

    return 0 ;
}
