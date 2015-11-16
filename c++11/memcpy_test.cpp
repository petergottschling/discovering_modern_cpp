#include <iostream>
#include <cstring>
#include <type_traits>

#include "print_compiler.hpp"

using namespace std;

struct simple_point 
{ 
# ifdef __cplusplus
    simple_point(double x, double y) : x(x), y(y) {}
    simple_point() = default;
# endif

    double x, y;
};

int main (int argc, char* argv[]) 
{
    print_compiler(); 

    simple_point p1{3.0, 7.1}, p2;

    static_assert(std::is_trivially_copyable<simple_point>::value,
    		  "simple_point is not as simple as you think "
		  "and cannot be memcpyd!");
    std::memcpy(&p2, &p1, sizeof(p1));
    cout << "p2 = (" << p2.x << "," << p2.y << ")\n";
    cout << "p1 = (" << p1.x << "," << p1.y << ")\n";

    return 0;
}

