#include <iostream>
#include <cassert>
#include <initializer_list>
#include <algorithm>

class vector
{
    typedef vector self;
  public:
    vector(int n) : my_size(n), data(new double[my_size]) {}

    vector(const vector& v)
      : my_size(v.my_size), data(new double[my_size]) 
    {
        for (unsigned i= 0; i < my_size; i++) 
            data[i]= v.data[i];
	std::cout << "Copy constructor called.\n";
    }


    ~vector()  { delete[] data; }

    vector& operator=(const vector& src) 
    {
	if (this == &src) 
	    return *this;
	assert(my_size == src.my_size);
	for (unsigned i= 0; i < my_size; i++)
	    data[i]= src.data[i];
	return *this;
    }

    vector(std::initializer_list<double> values)
      : my_size(values.size()), data(new double[my_size]) 
    {
	std::copy(values.begin(), values.end(), data);
	std::cout << "Init constructor called.\n";
    }

    self& operator=(const std::initializer_list<double>& values)
    {
        assert(my_size == values.size());
	std::copy(values.begin(), values.end(), data);
	std::cout << "Init assignment called.\n";
 	return *this;
    }

    vector(vector&& v) 
      : my_size(v.my_size), data(v.data) 
    {
	v.data= 0;
	v.my_size= 0;
	std::cout << "Move constructor called.\n";
    }

#if 0
    vector& operator=(vector&& src) 
    {
	assert(my_size == src.my_size);
	std::swap(data, src.data);
	std::cout << "Move assignment called.\n";
	return *this;
    }
#else
    vector& operator=(vector&& src) 
    {
	assert(my_size == src.my_size);
	delete[] data;
	data= src.data;
	src.data= 0;
	src.my_size= 0;
	std::cout << "Move assignment called.\n";
	return *this;
    }
#endif

    friend inline std::ostream& operator<<(std::ostream& os, const vector& v)
    {
	os << "[";
	for (unsigned i= 0; i < v.my_size; i++)
	    os << v.data[i] << (i+1 < v.my_size? ", " : "");
	return os << "]";
    }

    friend inline void swap(vector& x, vector& y) { std::swap(x.my_size, y.my_size); std::swap(x.data, y.data); }

  private:
    unsigned my_size;
    double   *data;
};

template <typename T>
inline void swap(T& x, T& y)
{
    T tmp(x); x= y; y= tmp;
}

vector set()
{
    return vector{4, 3, 2};
}

void f(vector&& v)
{
    std::cout << "In function f.\n";
}

template <typename T>
void g(T&& v)
{
    std::cout << "In function g&&.\n";
}

template <typename T>
void g(const T& v)
{
    std::cout << "In function g&.\n";
}


int main (int argc, char* argv[])
{
    vector v(3), w={2, 3, 4}, u= set();
    std::cout << "u is " << u << std::endl;
    v= {7, 8, 9};
    std::cout << "v is " << v << std::endl;
    // v= set();

    vector x(std::move(w)), y(x);
    std::cout << "x is " << x << std::endl;
    std::cout << "w is " << w << std::endl;

    v= std::move(u);
    std::cout << "v is " << v << std::endl;
    std::cout << "u is " << u << std::endl;

    f(set()); 
    // f(v); doesn't compile
    g(set());
    g(v);
 
    swap(u, v);

    return 0 ;
}
