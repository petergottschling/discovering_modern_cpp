#include <iostream>
#include <iomanip>

using namespace std;

struct managed
{
    managed(int i) { cerr << "Managed called with " << i << endl; }
    ~managed() { cerr << "Managed destructed" << endl; }
};

struct dummy
{
    dummy() try : m(1), p1(new int), p2(new int[12345])
    {
        // throw 1;
	try {
	    p1= new int;
	    // throw 2;
	    try {
		// throw 25; // causes delete of unallocated data (hopefully initialized to 0)
		p2= new int[12348]; 
	 	// throw 3;
            } catch (int) { cerr << "deleted p2 in catch" << endl; delete[] p2; throw; }
	} catch (...) { cerr << "deleted p1 in catch" << endl; delete p1; throw; }
    } catch (...) { delete p1; delete[] p2; }

    ~dummy() { cerr << "Destructor called." << endl; delete p1; delete[] p2; throw 666; }

    managed m;
    int *p1, *p2;
};



int main (int argc, char* argv[]) 
{
    try {
	dummy d;
	throw 17;
    } 
    catch (int i) { 
	cerr << "Caught " << i << endl; 
    } 

    cerr << "Finished.\n";

    return 0;
}

