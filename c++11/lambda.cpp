#include <iostream>
#include <cmath>

#if 0
template <typename F, typename T>
T inline fin_diff(F const& f, const T& x, const T& h) 
{
  return ( f(x+h) - f(x) ) / h ;
}
#endif

template <typename F, typename T>
T inline fin_diff(F f, const T& x, const T& h) 
{
  return ( f(x+h) - f(x) ) / h ;
}

template <typename F, typename T>
T inline fin_diff_mutable(F& f, const T& x, const T& h) 
{
  return ( f(x+h) - f(x) ) / h ;
}

class psc_f
{
  public:
    psc_f(double p) : parameter(p) {}

    double operator() ( double x ) const 
    { 
	return sin( parameter * x ) + cos(x);
    }

  private:
    double parameter;
};

struct dings
{
    dings() {}
    dings(const dings&) { std::cout << "Copy constructor of dings\n"; }
};

struct lambda_f
{
    lambda_f(double phi, double xi) : phi(phi), xi(xi) {}
    double operator()(double x) const
    {
	return sin(phi * x) + cos(x) * xi;
    }
    const double phi;
    const double xi;
};

struct lambda_ref_f
{
    lambda_ref_f(double& phi, double& xi) : phi(phi), xi(xi) {}
    double operator()(double x) const
    {
	return sin(phi * x) + cos(x) * xi;
    }
    double& phi;
    double& xi;
};

int main (int argc, char* argv[]) 
{
    using namespace std;

#if 1
    psc_f sin_1( 1.0 ) ;
    cout << fin_diff( sin_1, 1., 0.001 ) << endl ;
    cout << fin_diff( psc_f(2.0), 1., 0.001 ) << endl ;
    cout << fin_diff( psc_f(2.0), 0., 0.001 ) << endl ;
#endif

    cout << fin_diff([](double x){ return sin(x) + cos(x); }, 1., 0.001 ) << endl;
    cout << fin_diff([](double x){ return sin(2.5*x) + cos(x); }, 1., 0.001 ) << endl;
    
    auto sc_l= [](double x){ return sin(x) + cos(x); };
    auto psc_l= [](double x){ return sin(2.5*x) + cos(x); };
    cout << fin_diff(sc_l, 1., 0.001 ) << endl;
    

    double phi= 3.5, xi= 0.2;
    //cout << fin_diff([](double x) {return sin(phi * x) + cos(x); }, 1., 0.001 ) << endl;
    cout << fin_diff([phi](double x) {return sin(phi * x) + cos(x); }, 1., 0.001 ) << endl;
    cout << "phi = " << phi << '\n';

    double a, b, c;
    a= fin_diff([](double x){ return sin(2.5 * x); }, 1., 0.001);
    b= fin_diff([](double x){ return sin(3.0 * x); }, 1., 0.001);
    c= fin_diff([](double x){ return sin(3.5 * x); }, 1., 0.001);


    auto l2= [phi](double x) {return sin(phi * x) + cos(x); };
    phi= 2.9;
    cout << fin_diff(l2, 1., 0.001 ) << endl;

    auto sin_phi= [phi](double x){ return sin(phi * x); };
    auto sin2= [phi,xi](double x){ return sin(phi*x) + cos(x)*xi; }; 
    
    // auto l2inc= [phi](double x) mutable {phi+= 0.6; return sin(phi * x) + cos(x); };
    auto l2inc= [phi](double x) {double phi2= phi+0.6; return sin(phi2 * x) + cos(x); };
    cout << fin_diff(l2inc, 1., 0.001 ) << endl;

    cout << fin_diff([&phi](double x)->double { return sin(phi * x) + cos(x); }, 1., 0.001 ) << endl;
    auto l3= [&phi](double x)->double { return sin(phi * x) + cos(x); };

    cout << fin_diff(l3, 1., 0.001 ) << endl;
    phi= 9.9;
    cout << fin_diff(l3, 1., 0.001 ) << endl;

    dings d;
    auto l4= [d](double x)->double { return sin(1.0 * x) + cos(x); };

    return 0 ;
}
 
