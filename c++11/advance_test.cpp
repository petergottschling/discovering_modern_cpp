#include <iostream>
#include <list>
#include <forward_list>
#include <iterator>
#include "print_compiler.hpp"

using namespace std;

#if 0
template <typename Iterator, typename Distance>
inline void advance_aux(Iterator& i, Distance n, input_iterator_tag)
{
    assert(n >= 0);
    for (; n > 0; --n)
	++i;
}

template <typename Iterator, typename Distance>
inline void advance_aux(Iterator& i, Distance n, bidirectional_iterator_tag)
{
    if (n >= 0)
	for (; n > 0; --n)
	    ++i;
    else
	for (; n < 0; ++n)
	    --i;
}

template <typename Iterator, typename Distance>
inline void advance_aux(Iterator& i, Distance n, random_access_iterator_tag)
{
    i+= n;
}

template <typename Iterator, typename Distance>
inline void advance(Iterator& i, Distance n)
{
    advance(i, n, typename iterator_category<Iterator>::type());
}
#endif 


int main (int argc, char* argv[]) 
{
    print_compiler();
    forward_list<int> l= {3, 7, 9, 11};
    const auto it= l.end();
    advance(it, -2);
    // cout << *it << '\n';

    return 0;
}

