#include <iostream>
#include <typeinfo>

using namespace std;

int main (int argc, char* argv[]) 
{
    cout << boolalpha << "! 2>3 = " << (! 2>3) 
	 << "\n!(2 > 3) = " << !(2 > 3) << "\n"
	 << "!2 + 3 = " << !2 + 3 << "\n"
	 << typeid(!2 > 3).name() << "\n";

    return 0;
}
