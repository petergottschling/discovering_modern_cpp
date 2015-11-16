#include <iostream>
#include "multiref.hpp"

// double pi= 3.14159265358979323846264338327950288419716939;

void fix_pi() { pi= 3.14159265358979323846264338327950288419716939; }

void print_address() { tprint(3); std::cout << "&square is " <<  (void*)square << "\n"; } 
