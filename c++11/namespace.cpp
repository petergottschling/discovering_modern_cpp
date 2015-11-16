#include <iostream>
#include <cmath>
#include "print_compiler.hpp"

struct global {};
struct same {};

namespace c1 { 

    struct c1c {}; 
    struct same {};

    namespace c2 {

	struct c2c {};
	struct same {};

	// struct c1 {};
	// namespace c1 {}

	struct cc {
	    global x;
	    c1c    y;
	    c2c    z;
	};

	struct csame {
	    ::same     x;
	    c1::same   y;
	    same       z;
	};

    } // namespace c2

} // namespace c1


int main (int argc, char* argv[]) 
{
    namespace c3= c1::c2;

    print_compiler();
    c1::c2::cc object;
    c1::c2::csame same_object;

    return 0 ;
}
