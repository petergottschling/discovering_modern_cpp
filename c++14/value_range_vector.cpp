#include <iostream>
#include <typeinfo> // to enable c++filt in script

#include <boost/numeric/mtl/mtl.hpp>

#include "print_compiler.hpp"
#include "../my_info.hpp"

using namespace std;

struct too_small {};
struct too_large {};

template <typename Vector>
class value_range_vector
{
    using value_type= typename Vector::value_type;
    using size_type=  typename Vector::size_type;
  public:
    value_range_vector(Vector& vref, value_type minv, value_type maxv)
      : vref(vref), minv(minv), maxv(maxv)
    {}

    decltype(auto) operator[](size_type i)
    {
	decltype(auto) value= vref[i];
	if (value < minv) throw too_small{};
	if (value > maxv) throw too_large{};
	return value;
    }
  private:
    Vector&    vref;
    value_type minv, maxv;
};


int main () 
{
    print_compiler();

    using Vec= mtl::vector<double>;
    Vec v= {2.3, 8.1, 9.2};

    value_range_vector<Vec> w(v, 1.0, 10.0);
    decltype(auto) val= w[1];
    cout << "The type of val is " << my_info<decltype(val)>() << endl;
}

