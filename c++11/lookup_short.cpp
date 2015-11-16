#include <iostream>
#include "print_compiler.hpp"

namespace c1 { 
    namespace c2 {
	struct cc {};
	void f(const cc& o) {}
    } // namespace c2
    void f(const c2::cc& o) {}
} // namespace c1

void f(const c1::c2::cc& o) {}

namespace f1 {
    void f(const c1::c2::cc& o) {}
    namespace f2 {
	void f(const c1::c2::cc& o) {}
	void g()
	{
	    c1::c2::cc o;
	    const c1::c2::cc c(o);
	    f(o);
	    f(c);
	}
    } // namespace f2
} // namespace f1 

int main (int argc, char* argv[]) 
{
    print_compiler();
    f1::f2::g();

    return 0 ;
}

