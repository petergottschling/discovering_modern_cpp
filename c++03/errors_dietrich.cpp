#include <iostream>

using namespace std;



int main(int argc, char** argv) 
{
    // error 1
    int i=3;
    const int* p= &i; // allegededly forbidden

    // error 2, p. 50
    // int a= 1, c= (b= 2), b+1; // b undefined, b+1 not allowed in variable deklaration

    // error 3, p. 122
    // n and k switched

    // error 4, p. 151 (or obsolete)
    // Quader Q(); can be written for default-constructed object


    return 0;
}
