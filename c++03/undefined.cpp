#include <iostream>

int main () 
{
    int i= 1, v[]= {2, 4, 6, 8, 10};
    i= v[i++];
    std::cout << "i is " << i << '\n';
    // It is specificied that i is incremented after being read.
    // But i can be incremented before the assignment happens or afterwards.
    // Thus the statement above is equivalent to one of the following two implementations.

    // Version 1:
    int tmp= v[i];
    i++;
    i= tmp;

    // Version 2:
    i= v[i];
    i++;

    // Advise: do not modify a variable twice in one expression since the order of evaluation
    // is not specified.
    // Exception: comma operator that represents a sequential execution (unless inapropriately overloaded)
    i= 7, i++, i++; // i becomes 9 because the three expressions are executed consecutively

    // Amendment to the advice: if possible replace the comma by an semicolon; so you avoid the risk 
    // that the comma is strangly overloaded and you also have simpler expressions.

    return 0 ;
}
