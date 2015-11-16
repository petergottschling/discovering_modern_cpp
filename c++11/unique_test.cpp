#include <iostream>
#include <sstream>
#include <vector>
#include <list>
#include <algorithm>
#include "print_compiler.hpp"

template <typename Seq>
void print(const Seq& seq)
{
    for (auto& s : seq)
	std::cout << s << ' ';
    std::cout << '\n';
}

template <typename Seq>
void make_unique(Seq& seq)
{
    using std::begin; using std::end; using std::distance;
    std::sort(begin(seq), end(seq));
    auto it= std::unique(begin(seq), end(seq));
    seq.resize(distance(begin(seq), it));
}


int main () 
{
    std::vector<int> seq= {3, 4, 7, 9, 2, 5, 7, 8, 3, 4, 3, 9};
    print(seq);
    // sort(seq.begin(), seq.end());
    // print(seq);
    // auto it= unique(seq.begin(), seq.end());
    // print(seq);
    // seq.resize(distance(seq.begin(), it));
    make_unique(seq);
    print(seq);

    return 0;
}

