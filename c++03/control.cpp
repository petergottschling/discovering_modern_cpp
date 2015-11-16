#include <iostream>

int f(int i) { return i; }

int main () 
{
    double x= true ? 1u : 2l;


    int age= 45;
    int j= (age= 2, 3);

    if (age > 35) 
	std::cout << "Du bist alt!\n";
    else {
	std::cout << "Schlaf weiter.\n";
    }

    if (age > 67) 
	std::cout << "Genies deine Rente.\n";

    if (age > 35) { // else zum 1. if
	if (age > 67) 
	    std::cout << "Genies deine Rente.\n"; 
    } else 
	std::cout << "Geh arbeiten.\n";


    if (age > 35) { // else zum 2. if
	if (age > 67) 
	    std::cout << "Genies deine Rente.\n";
	else 
	    std::cout << "Geh arbeiten.\n";
    }

    f(age= 7);
    int i= 8;
    int sign= i > 0 ? 1 : -1;

    f(i > 0 ? 1 : -1);
    // entspricht
    if (i > 0)
	f(1);
    else
	f(-1);
	
    int sum= 0;
    for (int i= 0; i < 10; i++) {
	if (i == 7) continue;
	sum+= i;
    }

    for (int i= 0; i < 10; i++) {
	if (i != 7) {
	    sum+= i;
	}
    }

    switch(i) {
    case 0: std::cout << "is null\n"; break;
    case 1: ;
    case 2: std::cout << "is eins\n"; break;
    default: std::cout << "is was anderes\n"; break;
    }


    std::cout << sum << '\n';

    return 0 ;
}
