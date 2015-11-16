#include <iostream>
#include "print_compiler.hpp"

namespace c1 { 
    namespace c2 {

	struct cc {};

	void f(const cc& o)
	{    std::cout << "c1::c2::f()\n";	}

	struct dd {};

    } // namespace c2

    void f(const c2::cc& o)
    {    std::cout << "c1::f()\n";	}

} // namespace c1

void f(c1::c2::cc& o)
{    std::cout << "f()\n";	}

namespace d1 {

    using c1::c2::dd;

    // void f(const c1::c2::cc& o)
    // {    std::cout << "d1::f()\n";	}

}

namespace e1 {

    void f(const c1::c2::cc& o)
    {    std::cout << "e1::f()\n";	}

}


namespace f1 {

    // void f(const c1::c2::cc& o)
    // {    std::cout << "f1::f2::f()\n";	}

    namespace f2 {

	void g()
	{
	    // using d1::f; using e1::f;

	    c1::c2::cc o;
	    const c1::c2::cc c(o);
	    f(o);
	    f(c);
	}

	void f(const c1::c2::cc& o)
	{    std::cout << "f1::f2::f()\n";	}

    } // namespace f2

} // namespace f1 

namespace d1 {
    struct xyz {
	dd x;
    };
}

int main (int argc, char* argv[]) 
{
    print_compiler();
    f1::f2::g();
    d1::xyz x;

    using namespace d1;
    xyz y;

    return 0 ;
}

