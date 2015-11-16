#include <iostream>
#include <sstream>
#include <vector>
#include <list>
#include <algorithm>
#include "print_compiler.hpp"

struct value_not_found {};
struct value_not_found_twice {};

template <typename Range, typename Value>
void print_interval(const Range& r, const Value& v, std::ostream& os= std::cout)
{
    using std::begin; using std::end; 
    auto it= std::find(begin(r), end(r), v), it2= it; 
    if (it == end(r)) 
        throw value_not_found();
    ++it2;
    auto past= std::find(it2, end(r), v); 
    if (past == end(r)) 
        throw value_not_found_twice();
    ++past;
    for (; it != past; ++it)
	os << *it << ' ';
    os << '\n';
}

int main () 
{
    std::list<int> seq= {3, 4, 7, 9, 2, 5, 7, 8};
    print_interval(seq, 7);

    int array[]= {3, 4, 7, 9, 2, 5, 7, 8};
    std::stringstream ss;
    print_interval(array, 7, ss);
    std::cout << ss.str();

    return 0;
}

