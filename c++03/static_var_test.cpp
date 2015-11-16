#include <iostream>

using namespace std;

int main (int argc, char* argv[]) 
{
    for (int i= 0; i < 10; i++) {
	int j= 7;
	{
	    static int k= 3;
	    std::cout << "k = " << ++k << "\n";
	}
    }


    return 0;
}
