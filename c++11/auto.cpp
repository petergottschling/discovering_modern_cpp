#include <iostream>
#include <typeinfo>
#include <cmath>



int main (int argc, char* argv[]) 
{
    auto i= 2 * 7.5, j= std::sqrt(3.7);
    
    std::cout << "type of i is " << typeid(i).name() << ", type of j is " << typeid(j).name() << '\n';

    return 0 ;
}
