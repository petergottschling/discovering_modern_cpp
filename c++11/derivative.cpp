#include <cmath>
#include <iostream>
#include <boost/mpl/bool.hpp>
#include <boost/lambda/lambda.hpp>

double sc(double x) 
{
    return sin(x) + cos(x);
}

struct sc_f
{
    double operator() (double x) const 
    { 
	return sin(x) + cos(x);
    }
};


class psc_f
{
  public:
    psc_f(double alpha) : alpha(alpha) {}

    double operator() (double x) const 
    { 
	return sin(alpha * x) + cos(x);
    }
  private:
    double alpha;
};

#if 0 
// with function pointers
double fin_diff(double f(double), double x, double h) 
{
    return ( f(x+h) - f(x) ) / h;
}
#endif


template <typename F, typename T>
inline T fin_diff(F f, const T& x, const T& h) 
{
    return ( f(x+h) - f(x) ) / h;
}





template <typename F, typename T>
class derivative
{
  public:
    derivative(const F& f, const T& h) : f(f), h(h) {}

    T operator()(const T& x) const
    {
	return ( f(x+h) - f(x) ) / h;
    }   
  private:
    const F& f;
    T        h;
};


template <typename F, typename T>
class second_derivative
{
  public:
    second_derivative(const F& f, const T& h) : h(h), fp(f, h) {}

    T operator()(const T& x) const
    {
	return ( fp(x+h) - fp(x) ) / h;
    }    
  private:
    T        h;
    derivative<F, T> fp;
};

#if 0
template <typename F, typename T, unsigned N>
class nth_derivative
{
    using prev_derivative= nth_derivative<F, T, N-1>;
  public:
    nth_derivative(const F& f, const T& h) : h(h), fp(f, h) {}

    T operator()(const T& x) const
    {
	return ( fp(x+h) - fp(x) ) / h;
    }    
  private:
    T        h;
    prev_derivative fp;
};

#else

template <typename F, typename T, unsigned N>
class nth_derivative
{
    using prev_derivative= nth_derivative<F, T, N-1>;
  public:
    nth_derivative(const F& f, const T& h) : h(h), fp(f, h) {}

    T operator()(const T& x) const
    {
	return N & 1 ? ( fp(x+h) - fp(x) ) / h 
	             : ( fp(x) - fp(x-h) ) / h;
    }	
  private:
    T        h;
    prev_derivative fp;
};


#if 0 // for meta-programming, maybe
template <typename F, typename T, unsigned N>
class nth_derivative
{
    using prev_derivative= nth_derivative<F, T, N-1>;
  public:
    nth_derivative(const F& f, const T& h) : h(h), fp(f, h) {}

    T operator()(const T& x) const
    {
	return diff(x, boost::mpl::bool_<N & 1>());
    }
	
  private:

    T diff(const T& x, boost::mpl::true_) const
    {
	return ( fp(x+h) - fp(x) ) / h;
    }    

    T diff(const T& x, boost::mpl::false_) const
    {
	return ( fp(x) - fp(x-h) ) / h;
    }    

    T        h;
    prev_derivative fp;
};
#endif

#endif 

#if 0
template <typename F, typename T>
class nth_derivative<F, T, 1>
{
  public:
    nth_derivative(const F& f, const T& h) : f(f), h(h) {}

    T operator()(const T& x) const
    {
	return ( f(x+h) - f(x) ) / h;
    }   
  private:
    const F& f;
    T        h;
};
#endif 

template <typename F, typename T>
class nth_derivative<F, T, 1>
  : public derivative<F, T>
{
    using derivative<F, T>::derivative;

  // public:
  //   nth_derivative(const F& f, const T& h) : derivative<F, T>(f, h) {}
};


#if 0
template <typename F, typename T, unsigned N> // Not clever
nth_derivative<F, T, N> 
make_nth_derivative(const F& f, const T& h)
{
    return nth_derivative<F, T, N>(f, h);
}
#endif




template <unsigned N, typename F, typename T>
nth_derivative<F, T, N> 
make_nth_derivative(const F& f, const T& h)
{
    return nth_derivative<F, T, N>(f, h);
}

struct et {};

template <typename F>
void error(const F& f)
{
    et e= f;
}

int main() 
{
    using namespace std;

    psc_f psc_o(1.0);
    cout << fin_diff(psc_o, 1., 0.001) << endl;
    cout << fin_diff(psc_f(2.0), 1., 0.001) << endl;
    cout << fin_diff(psc_f(2.0), 0., 0.001) << endl;
    cout << fin_diff(sc, 0., 0.001) << endl;

    using d_psc_f= derivative<psc_f, double>;
    using dd_psc_f= derivative<d_psc_f, double>;

    d_psc_f                                     d_psc_o(psc_o, 0.001);
    dd_psc_f                                     dd_psc_o(d_psc_o, 0.001);

    cout << "der. of sin(0) + cos(0) is " << d_psc_o(0.0) << '\n';
    cout << "2nd der. of sin(0) + cos(0) is " << dd_psc_o(0.0) << '\n';

    second_derivative<psc_f, double> dd_psc_2_o(psc_f(1.0), 0.001);
    cout << "2nd der. of sin(0) + cos(0) is " << dd_psc_2_o(0.0) << '\n';

    nth_derivative<psc_f, double, 2> dd_psc_3_o(psc_f(1.0), 0.001);
    cout << "2nd der. of sin(0) + cos(0) is " << dd_psc_3_o(0.0) << '\n';

    nth_derivative<psc_f, double, 6> d6_psc_o(psc_f(1.0), 0.00001);
    cout << "6th der. of sin(0) + cos(0) is " << d6_psc_o(0.0) << '\n';

    nth_derivative<psc_f, double, 12> d12_psc_o(psc_f(1.0), 0.00001);
    cout << "12th der. of sin(0) + cos(0) is " << d12_psc_o(0.0) << '\n';

    nth_derivative<psc_f, double, 22> d22_psc_o(psc_f(1.0), 0.00001);
    cout << "22nd der. of sin(0) + cos(0) is " << d22_psc_o(0.0) << '\n';

    // auto d7_psc_o= make_nth_derivative<psc_f, double, 7>(psc_o, 0.00001);

    // nth_derivative<psc_f, double, 7> d7_psc_o(psc_o, 0.00001);
    // auto d7_psc_o= nth_derivative<psc_f, double, 7>(psc_o, 0.00001);
    // nth_derivative<decltype(psc_o), decltype(0.00001), 7> d7_psc_o(psc_o, 0.00001);

    make_nth_derivative<7, psc_f, double>(psc_o, 0.00001);
    auto d7_psc_o= make_nth_derivative<7>(psc_o, 0.00001);

    cout << "7th der. of psc_o at x=3 is " 
	 << make_nth_derivative<7>(psc_o, 0.00001)(3.0) << '\n';

    using boost::lambda::_1;
    
    (3.5 * _1 + 4.0) * _1 * _1;

    cout << "2nd der. of 3.5*x^3+4*x^2 at x=2 is "
	      << make_nth_derivative<2>((3.5 * _1 + 4.0) * _1 * _1, 0.0001)(2) << '\n';

    cout << "2nd der. of 3.5*x^3+4*x^2 at x=2 is "
	 << make_nth_derivative<2>([](double x){ return (3.5 * x + 4.0) * x * x; }, 0.0001)(2) << '\n';

    auto d7_cub_l= make_nth_derivative<7>([](double x){ return (3.5 * x + 4.0) * x * x; }, 0.0001);
    auto d7_psc_l= make_nth_derivative<7>([](double x){ return sin(2.5*x) + cos(x); }, 0.0001);

    // error((3.5 * _1 + _1) * _1 * _1);
    return 0;
}

