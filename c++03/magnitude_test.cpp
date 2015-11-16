#include <iostream>
#include <cmath>
#include <complex>
#include <boost/numeric/mtl/mtl.hpp>


template <typename T>
struct Magnitude
{
    typedef T type;
};

template <typename T>
struct Magnitude<std::complex<T> >
{
    typedef T type;
};

template <typename T, typename P>
struct Magnitude<mtl::dense_vector<T, P> >
{
    typedef typename Magnitude<T>::type type;
};

template <typename T, typename P>
struct Magnitude<mtl::dense2D<T, P> >
{
    typedef typename Magnitude<T>::type type;
};

template <typename T, typename P>
struct Magnitude<mtl::compressed2D<T, P> >
{
    typedef typename Magnitude<T>::type type;
};



template <typename T>
T inline min_magnitude(const T& x, const T& y)
{
    using std::abs;
    typename Magnitude<T>::type ax= abs(x), ay= abs(y);
    return ax < ay ? ax : ay;
}

template <typename T>
class cc
{
    //typedef typename Magnitude<T>::type  my_mag;
};

template <typename T>
struct my_mag2
{
    typedef typename Magnitude<T>::type type;
};

int main (int argc, char* argv[]) 
{
    using namespace std;
    cc<short> oo;

    // my_mag2<short>::type sm;

    std::cout << min_magnitude(3.5, -2.3) << '\n';
    double               d1= 3., d2= 4.;
    cout << "min |d1, d2| = " << min_magnitude(d1, d2) << '\n';

    std::complex<float> c1(3.5), c2(-2.3, 1.0);
    cout << min_magnitude(c1, c2) << '\n';
   
    Magnitude<double>::type x;

    return 0 ;

}
