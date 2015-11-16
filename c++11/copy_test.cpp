#include <iostream>
#include <vector>
#include <iterator>
#include <list>
#include <algorithm>
#include "print_compiler.hpp"

using namespace std;

int main (int argc, char* argv[]) 
{
    print_compiler();
    vector<int> seq= {3, 4, 7, 9, 2, 5, 7, 8}, v;
    v.resize(seq.size());
    copy(seq.begin(), seq.end(), v.begin());

    copy(seq.begin(), seq.end(), ostream_iterator<int>(cout, ", "));

    return 0;
}

