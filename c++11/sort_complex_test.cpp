#include <iostream>
#include <vector>
#include <complex>
#include <iterator>
#include <algorithm>
#include "print_compiler.hpp"

using namespace std;

int main (int argc, char* argv[]) 
{
    print_compiler();
    std::vector<int> seq= {3, 4, 7, 9, 2, 5, 7, 8, 3, 4, 3, 9};
    sort(seq.begin(), seq.end(), [](int x, int y){return x > y;});
    copy(seq.begin(), seq.end(), ostream_iterator<int>(cout, ", "));
    cout << '\n';

    using cf= complex<float>;
    vector<cf> v= {{3, 4}, {7, 9}, {2, 5}, {7, 8}};
    sort(v.begin(), v.end(), [](cf x, cf y){return abs(x) < abs(y);});

    copy(v.begin(), v.end(), ostream_iterator<cf>(cout, ", "));
    cout << '\n';

    auto lex= [](cf x, cf y){return real(x)<real(y) || real(x)==real(y) && imag(x)<imag(y);};
    sort(v.begin(), v.end(), lex);

    copy(v.begin(), v.end(), ostream_iterator<cf>(cout, ", "));
    cout << '\n';


    return 0;
}

