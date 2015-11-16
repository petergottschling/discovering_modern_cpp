#include <iostream>
#include <vector>
#include <complex>
#include <iterator>
#include <algorithm>
#include <numeric>
#include "print_compiler.hpp"

using namespace std;

template <typename T>
void print(const T& v)
{
    copy(v.begin(), v.end(), ostream_iterator<float>(cout, ", "));
    cout << '\n';
}
//                                                                   !
int main (int argc, char* argv[]) 
{
    print_compiler();
    vector<float> v= {3.1, 4.2, 7, 9.3, 2, 5, 7, 8, 3, 4}, 
	          w(10), x(10), y(10);
    iota(w.begin(), w.end(), 12.1);

    partial_sum(v.begin(), v.end(), x.begin());
    adjacent_difference(v.begin(), v.end(), y.begin());

    float alpha= inner_product(w.begin(), w.end(), v.begin(), 0.0f);
    float sum_w= accumulate(w.begin(), w.end(), 0.0f),
	  product_w= accumulate(w.begin(), w.end(), 1.0f, 
                                [](float x, float y){return x * y;});

    print(w);
    print(x);
    print(y);

    cout << "alpha = " << alpha << '\n';
    cout << "sum_w = " << sum_w << '\n';
    cout << "product_w = " << product_w << '\n';

    return 0;
}

