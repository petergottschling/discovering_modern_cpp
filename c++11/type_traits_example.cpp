#include <iostream>
#include <cstring>
#include <type_traits>
#include <initializer_list>
#include <iterator>
#include "print_compiler.hpp"

using namespace std;

struct simple_point 
{ 
# ifdef __cplusplus
    simple_point(double x, double y) : x(x), y(y) {}
    simple_point() = default;
    simple_point(initializer_list<double> il) 
    {
	auto it= begin(il);
	x= *it;
	y= *next(it);
    }
# endif

    double x, y;
};

int main (int argc, char* argv[]) 
{
    print_compiler();

    // simple_point p1(3.0, 7.0), p2;
    simple_point p1, p2;
    p1.x= 3.0; p1.y= 7.0;


    static_assert(std::is_trivially_copyable<simple_point>::value,
    		  "simple_point is not as simple as you think and cannot be memcpyd!");
    std::memcpy(&p1, &p2, sizeof(p1));
    cout << "simple_point is pod = " << boolalpha << is_pod<simple_point>::value << endl;
    
}

