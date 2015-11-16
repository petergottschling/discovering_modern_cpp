#include <iostream>

template <typename ...P>
void variadic_stuff(P ...p)
{
    std::cout << "sizeof...(p) " << sizeof...(p) << '\n';
    //std::cout << "sizeof... p " << sizeof... p << '\n';
    std::cout << "sizeof...(P) " << sizeof...(P) << '\n';
    // std::cout << "sizeof... P " << sizeof... P << '\n';
}


int main (int argc, char* argv[]) 
{
    int i[8];
    // std::cout << "alignof(i) " << alignof(i) << '\n';
    // std::cout << "alignof i " << alignof i << '\n';
    std::cout << "alignof(int) " << alignof(int) << '\n';
    // std::cout << "alignof int " << alignof int << '\n';

    std::cout << "sizeof(i) " << sizeof(i) << '\n';
    std::cout << "sizeof i " << sizeof i << '\n';
    std::cout << "sizeof(int) " << sizeof(int) << '\n';
    // std::cout << "sizeof int " << sizeof int << '\n';
    
    variadic_stuff(3, 'a', 9.4);

    return 0 ;
}
