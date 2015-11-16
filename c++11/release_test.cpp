#include <iostream>
#include <iomanip>
#include <memory>
#include "print_compiler.hpp"

using namespace std;

int *gp1= (int*)(7), *gp2= (int*)(8);

struct managed
{
    managed(int i) { cerr << "Managed called with " << i << endl; }
    ~managed() { cerr << "Managed destructed" << endl; }
};

struct dummy
{
    dummy() : m(1), p1(new int)
    {
        // throw 1;
	// try {
	//p1= std::move(new int); gp1= p1;
	    // throw 2;
	    try {
		p2= new int[12348]; gp2= p2;
	 	// throw 3;
            } catch (int) { cerr << "deleted p2 in catch" << endl; delete[] p2; throw; }
	// } catch (...) { cerr << "deleted p1 in catch" << endl; delete p1; throw; }
    }

    ~dummy() { cerr << "Destructor called." << endl; delete[] p2; }

    managed m;
    unique_ptr<int> p1;
    int *p2;
};



int main (int argc, char* argv[]) 
{
    print_compiler();

    try {
	dummy d;
    } 
    catch (int i) { 
	cerr << "Caught " << i << endl; 
	cerr << "gp1 = " << hex << gp1 << endl;
	cerr << "gp2 = " << hex << gp2 << endl;
    } 

    // delete gp1;
    // delete gp2;

    // *gp2= 77;

    cerr << "Finished.\n";

    return 0;
}

