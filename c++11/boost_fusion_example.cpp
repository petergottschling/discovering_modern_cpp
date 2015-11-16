#include <iostream>
#include <complex>
#include <string>
#include <tuple>
#include <boost/fusion/include/for_each.hpp>
#include <boost/fusion/adapted/std_tuple.hpp> 

struct printer
{
    template <typename T>
    void operator()(const T& x) const
    {	std::cout << "Entry is " << x << std::endl;    }
};

int main () 
{
    auto t= std::make_tuple(3, 7u, "Hallo", std::string("Hi"), 
			    std::complex<float>(3, 7));
    boost::fusion::for_each(t, printer{});
}

