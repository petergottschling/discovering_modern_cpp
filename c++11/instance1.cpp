#include <iostream>
#include <vector>
#include "print_compiler.hpp"

extern template class std::vector<int>;

int main (int argc, char* argv[]) 
{
    print_compiler();

    std::vector<int> v= {2, 3, 4};
    std::cout << "v[1] = " << v[1] << '\n';

    return 0;
}

