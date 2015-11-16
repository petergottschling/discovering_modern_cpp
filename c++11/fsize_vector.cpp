#include <cassert>
#include <iostream>
#include <cmath>
#include <algorithm>

template <typename T, int Size>
class fsize_vector 
{
    using self= fsize_vector;
    void check_index(int i) const { assert(i >= 0 && i < my_size); }
  public:  
    using value_type= T;
    const static int     my_size= Size;

    fsize_vector(int s= Size) { assert(s == Size); }

    fsize_vector(const self& that)
    {
	std::copy(that.data, that.data + Size, data);
    }

    self& operator=(const self& that) 
    {
	std::copy(that.data, that.data + Size, data);
	return *this;
    }

    int size() const { return my_size; }

    const T& operator[](int i) const 
    {
	check_index(i);
	return data[i];
    }
		     
    T& operator[](int i) 
    {
	check_index(i);
	return data[i];
    }

    self operator+(const self& that) const 
    {
	self sum;
	for (int i= 0; i < my_size; ++i) 
	    sum[i]= data[i] + that[i];
	return sum;
    }
  private:
    T     data[my_size];
};


template <typename T, int Size>
std::ostream& operator<<(std::ostream& os, const fsize_vector<T, Size>& v)
{
  os << '[';
  for (int i= 0; i < v.size(); ++i) os << v[i] << ',';
  os << ']';
  return os;
}


template <typename Vector>
typename Vector::value_type
inline one_norm(const Vector& v)
{
    using std::abs;
    typename Vector::value_type s= 0;
    for (int i= 0; i < v.size(); ++i)
	s+= abs(v[i]);
    return s;
}

template <typename Vector>
typename Vector::value_type
inline sum(const Vector& v)
{
    typename Vector::value_type s= 0;
    for (int i= 0; i < v.size(); ++i)
	s+= v[i];
    return s;
}

#if 0
template <typename Vector>
typename Vector::value_type
inline product(const Vector& v)
{
    typename Vector::value_type s= 1;
    for (int i= 0; i < v.size(); ++i)
	s*= v[i];
    return s;
}
#endif

template <typename Vector, typename F>
typename Vector::value_type
inline accumulate(const Vector& v, const F& f)
{
    typename Vector::value_type s;
    f.initialize(s);
    for (int i= 0; i < v.size(); ++i)
	f(s, v[i]);
    return s;
}

template <typename T>
struct times_functor
{
    void initialize(T& x) const  { x= 1; }
    void operator()(T& x, const T& y) const { x*= y; }
};

template <typename Vector>
typename Vector::value_type
inline product(const Vector& v)
{
    times_functor<typename Vector::value_type> t;
    return accumulate(v, t);
}

class dummy
{
  public:
    void operator=(int) {}

    int a;
};

int main() 
{
    dummy d1, d2;
    d1.a= 7;
    d2= d1;
    std::cout << "d2.a is " << d2.a << std::endl;


    fsize_vector<float, 4> v;
    v[0] = v[1] = 1.0; v[2] = 2.0; v[3] = -3.0;

    float on= one_norm(v);
    std::cout << "onenorm is " << on << std::endl;

#if 1
    std::cout << v << std::endl;

    fsize_vector<float, 4> w;
    w = v;

    fsize_vector<float, 4> sum(w + v);

    fsize_vector<float, 4> z(v);

    std::cout << one_norm(v) << '\n';
    std::cout << "Product(v) is " << product(v) << '\n';
#endif

    return 0;
}
