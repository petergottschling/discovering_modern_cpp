#include <iostream>
#include <vector>
#include <functional>
#include <boost/any.hpp>


#include "print_compiler.hpp"


template<typename T>
T copy(const T& to_copy)
{
    return T{ to_copy };
}

int main (int argc, char* argv[]) 
{
    print_compiler();

    std::vector<boost::any> v;
    // v.push_back(3);
    // v.push_back(3.3);
    std::cout << "size of v is " << v.size() << '\n';

    std::vector<boost::any> w= copy(v);
    std::cout << "size of w is " << w.size() << '\n';

    // std::cout << typeid(decltype(copy(std::vector<boost::any>{}))).name() << '\n';
    // copy(std::vector<std::function<void ()>>{}); // used to cause a compiler error

    return 0 ;
}

