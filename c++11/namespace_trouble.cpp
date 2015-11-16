#include <vector>
#include <algorithm>
#include "print_compiler.hpp"

namespace A {

    template <typename Seq>
    void f(const Seq& seq)
    {
	find(seq.begin(), seq.end(), 7);
    }
}

namespace B {

    template <typename I, typename V>
    void find(I i1, I i2, const V& v) {}
}

using namespace B; 

int main (int argc, char* argv[]) 
{
    print_compiler(); 

    std::vector<int> v= {3, 4, 7, 9};
    A::f(v);

    return 0;
}
  
