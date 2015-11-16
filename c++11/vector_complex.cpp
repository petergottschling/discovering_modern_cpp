#include <iostream>
#include <cassert>
#include <initializer_list>
#include <algorithm>
#include <string>
#include "print_compiler.hpp"

//#define WITH_AGGREGATE 1

class complex
{
  public:
    complex(double rn = 0.0, double in = 0.0) : r(rn), i(in) {}
    // complex(const complex& c) : r(c.r), i(c.i) {}

    // ~complex() {  }
  
    complex& operator= (const complex& c) 
    {
	r= c.r; i= c.i;
	return *this;
    }

    complex& operator= (double rn) 
    {
	r= rn; i= 0.0;
	return *this;
    }

    // complex operator+(const complex& c2) const
    // {
    //     std::cout << " -- c+c -- "; 
    //     return complex(r + c2.r, i + c2.i);
    // }

    // complex operator-() const { return complex(-r, -i); }

    complex operator+(double d) const;
  
    friend inline double const& real(const complex& c) { return c.r; } 
    friend inline double& real(complex& c) { return c.r; } 

    friend inline double const& imag(const complex& c) { return c.i; } 
    friend inline double& imag(complex& c) { return c.i; }  

    // double const& real() const { return r; } // c
    // double& real() { return r; }      // m

    // double const& imag() const { return i; } // c
    // double& imag() { return i; }      // m

    friend complex operator-(const complex& c1, const complex& c2);

  private:
    double r, i;
};

inline complex operator+(const complex& c1, const complex& c2)
{
    std::cout << " -- c+c -- "; 
    return complex(real(c1) + real(c2), imag(c1) + imag(c2));
}

inline complex operator+(double d, const complex& c2)
{
    std::cout << " -- d+c -- "; 
    return complex(d + real(c2), imag(c2));
}

inline complex
complex::operator+(double d) const
{
    std::cout << " -- c+d -- "; 
    return complex(r + d, i);
}

inline complex operator-(const complex& c1, const complex& c2)
{
    std::cout << " -- c-c -- "; 
    return complex(c1.r - c2.r, c1.i - c2.i);
}

// inline complex operator-(double c1, const complex& c2)
// {
//     std::cout << " -- d-c -- ";     
//     return complex(c1 - c2.real(), -c2.imag());
// }
 
complex operator-(const complex& c1) 
{ std::cout << "free unary -\n"; return complex(-real(c1), -imag(c1)); }


std::ostream& operator<<(std::ostream& os, complex c)
{
    os << '(' << real(c) << ',' << imag(c) << ")";
    return os;
}

class vector_complex
{
    typedef ::complex T;
    typedef vector_complex self;
    void check_size(unsigned that_size) const { assert(my_size == that_size); }
    void check_index(unsigned i) const { assert(i < my_size); }
  public:

#ifndef WITH_AGGREGATE
    vector_complex(int n) : my_size(n), data(new T[my_size]) { std::cout << "(n)\n"; }

    vector_complex(int n, T* data) : my_size(n), data(data) {std::cout << "(n, *data)\n"; }

    vector_complex(const vector_complex& v)
      : my_size(v.my_size), data(new T[my_size]) 
    {
        for (unsigned i= 0; i < my_size; i++) 
            data[i]= v.data[i];
    	std::cout << "Copy constructor called.\n";
    }


    vector_complex(std::string s, int i) : my_size(i), data(0) {std::cout << "(string, n)\n"; }

    vector_complex(std::initializer_list<T> values)
      : my_size(values.size()), data(new T[my_size]) 
    {
    	std::copy(values.begin(), values.end(), data);
    	// std::cout << "Initializer list constructor called.\n";
    }
#endif

    ~vector_complex()  { if (data != (T*)(0x11111)) delete[] data; }

    self& operator=(const std::initializer_list<T>& values)
    {
        assert(my_size == values.size());
	std::copy(values.begin(), values.end(), data);
	std::cout << "Init assignment called.\n";
 	return *this;
    }

    vector_complex& operator=(const vector_complex& src) 
    {
	if (this == &src) 
	    return *this;
	assert(my_size == src.my_size);
	for (unsigned i= 0; i < my_size; i++)
	    data[i]= src.data[i];
	return *this;
    }



    const T& operator[]( int i ) const&
    {
	check_index(i);
	return data[i];
    }
		     
    T& operator[]( int i ) &
    {
	check_index(i);
	return data[i] ;
    }

    friend inline std::ostream& operator<<(std::ostream& os, const vector_complex& v)
    {
	// return os << "{" << std::hex << v.data << " @ " << std::dec << v.my_size << "}";

	if (v.data == (T*)(0x11111)) 
	    return os << "{Quatsch}";	

	if (v.data == 0) 
	    return os << "{}";
	os << "[";
	for (unsigned i= 0; i < v.my_size; i++)
	    os << v.data[i] << (i+1 < v.my_size? ", " : "");
	return os << "]";
    }


#ifndef WITH_AGGREGATE
  private:
#endif
    unsigned my_size;
    T   *data;
};

int main (int argc, char* argv[])
{
    print_compiler();

    vector_complex v= {{1.5, -2}, {3.4}, {2.6, 5.13}};
    std::cout << "v is " << v << std::endl;

    vector_complex v1= {2};
    vector_complex v1d= {{2}};

    vector_complex v2= {2, 3};
    vector_complex v2d= {{2, 3}};
    vector_complex v2dc= {{2, 3}, };
    vector_complex v2cd= {{2, 3, }};
    vector_complex v2w= {{2}, {3}};
    vector_complex v2c= {{2, 3, }};
    vector_complex v2dw= {{{2}, {3}}};

    vector_complex v3= {2, 3, 4};
    vector_complex v3d= {{2, 3, 4}};
    vector_complex v3dc= {{2, 3}, 4};

    std::cout << "v1 is " << v1 << std::endl;
    std::cout << "v1d is " << v1d << std::endl << std::endl;

    std::cout << "v2 is " << v2 << std::endl;
    std::cout << "v2d is " << v2d << std::endl;
    std::cout << "v2dc is " << v2dc << std::endl;
    std::cout << "v2cd is " << v2cd << std::endl;
    std::cout << "v2w is " << v2w << std::endl;
    std::cout << "v2c is " << v2c << std::endl;
    std::cout << "v2dw is " << v2dw << std::endl << std::endl;
 
    std::cout << "v3 is " << v3 << std::endl;
    std::cout << "v3d is " << v3d << std::endl;
    std::cout << "v3dc is " << v3dc << std::endl;

    

    return 0 ;
}
