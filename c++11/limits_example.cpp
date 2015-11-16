#include <iostream>
#include <limits>
#include <vector>
#include <cmath>
#include "print_compiler.hpp"

using namespace std;

template <typename T>
inline void test(const T& x)
{
    cout << "x = " << x << " (";
    int oldp= cout.precision(numeric_limits<T>::digits10 + 1);
    cout << x << ")" << endl;
    cout.precision(oldp);
#if 0
    cout << "Maximal value of this type is " << numeric_limits<T>::max() << "\n";
    cout << "Minimal value of this type is " << numeric_limits<T>::min() << "\n";
    cout << "Minimal value of this type is " << numeric_limits<T>::lowest() << "\n\n";
#endif
}

template <typename T>
T square_root(const T& x)
{
    const T my_eps= 2 * x * numeric_limits<T>::epsilon();
    T r= x;

    while (std::abs((r * r) - x) > my_eps)
	r= (r + x/r) / T(2);
    return r;
}

template <typename Container>
typename Container::value_type
inline minimum(const Container& c)
{
    using vt= typename Container::value_type;
    vt min_value= numeric_limits<vt>::max();
    for (const vt& x : c)
	if (x < min_value)
	    min_value= x;
    return min_value;
}


int main (int argc, char* argv[]) 
{
    print_compiler();
    test(3);
    test(3u);
    test<short>(3);
    test<unsigned short>(3);
    test(1.f/3.f);
    test(1./3.0);
    test(1./3.0l);

    cout.precision(20);
    cout << "square_root(3.0) = " << square_root(3.0f) << '\n';
    cout << "square_root(3.0) = " << square_root(3.0) << '\n';
    cout << "square_root(3.0) = " << square_root(3.0l) << '\n';
    cout << "square_root(0.0) = " << square_root(0.0) << "\n\n";

    cout << "minimum({3, 4, -1}) = " << minimum(vector<int>({3, 4, -1})) << '\n';
    cout << "minimum({}) = " << minimum(vector<int>({})) << '\n';

    cout << numeric_limits<int>::epsilon() << endl;

    return 0;
}

