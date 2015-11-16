#include <iostream>
#include <list>

int main (int argc, char* argv[]) 
{
    int primes[]= {2, 3, 5, 7, 11, 13, 17, 19};
    for (int i : primes)
	std::cout << i << " ";
    std::cout << '\n';

    std::list<int> l= {3, 5, 9, 7};
    for (auto& i : l)
	i*= 77;
    const std::list<int>& lr= l; 
    for (auto& i : lr)
	std::cout << i << std::endl;

    for (auto it = l.cbegin(); it != l.cend(); ++it) {
	//*it= 7;
	int i= *it;
	std::cout << i << std::endl;
    }

    for (auto it = const_cast<const std::list<int>&>(l).begin(); 
	 it != const_cast<const std::list<int>&>(l).end(); ++it) {
	//*it= 7;
	int i= *it;
	std::cout << i << std::endl;
    }
	

    return 0 ;
}
