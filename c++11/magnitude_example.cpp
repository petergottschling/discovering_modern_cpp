#include <iostream>
#include <cmath>
#include <complex>

#if 0
template <typename T>
struct Magnitude {};

template <>
struct Magnitude<int>
{
    using type= int;
};

template <>
struct Magnitude<float>
{
    using type= float;
};

template <>
struct Magnitude<double>
{
    using type= double;
};

template <>
struct Magnitude<std::complex<float> >
{
    using type= float;
};

template <>
struct Magnitude<std::complex<double> >
{
    using type= double;
};
#endif

template <typename T>
struct Magnitude
{
    using type= T;
};

template <typename T>
struct Magnitude<std::complex<T> >
{
    using type= T;
};





#if 0
template <typename T>
T inline min_magnitude(const T& x, const T& y)
{
    using std::abs;
    T ax= abs(x), ay= abs(y);
    return ax < ay ? x : y;
}


#else
template <typename T>
T inline min_magnitude(const T& x, const T& y)
{
    using std::abs;
    typename Magnitude<T>::type ax= abs(x), ay= abs(y);
    return ax < ay ? x : y;
}
#endif

int main (int argc, char* argv[]) 
{
    using namespace std;

    double               d1= 3., d2= 4.;
    cout << "min |d1, d2| = " << min_magnitude(d1, d2) << '\n';

    std::complex<double> c1(3.), c2(4.);
    cout << "min |c1, c2| = " << min_magnitude(c1, c2) << '\n';

    return 0 ;

}
