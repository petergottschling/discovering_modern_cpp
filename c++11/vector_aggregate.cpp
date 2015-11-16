#include <iostream>
#include <cassert>
#include <initializer_list>
#include <algorithm>
#include <string>

//#define WITH_AGGREGATE 1

class vector
{
    typedef double T;
    typedef vector self;
    void check_size(unsigned that_size) const { assert(my_size == that_size); }
    void check_index(unsigned i) const { assert(i < my_size); }
  public:

    vector() : my_size{}, data{nullptr} {std::cout << "()\n"; }

#ifndef WITH_AGGREGATE
    vector(unsigned n) : my_size{n}, data{new double[my_size]} { std::cout << "(n)\n"; }

    vector(unsigned n, double* data) : my_size(n), data(data) {std::cout << "(n, *data)\n"; }

    vector(const vector& v)
      : my_size(v.my_size), data(new double[my_size]) 
    {
        for (unsigned i= 0; i < my_size; i++) 
            data[i]= v.data[i];
    	std::cout << "Copy constructor called.\n";
    }


    vector(std::string s, int i) : my_size(i), data(0) {std::cout << "(string, n)\n"; }

    vector(std::initializer_list<double> values)
      : my_size(values.size()), data(new double[my_size]) 
    {
    	std::copy(values.begin(), values.end(), data);
    	std::cout << "Initializer list constructor called.\n";
    }
#endif

    ~vector()  { if (data != (double*)(0x11111)) delete[] data; }

    self& operator=(const std::initializer_list<double>& values)
    {
        assert(my_size == values.size());
	std::copy(values.begin(), values.end(), data);
	std::cout << "Init assignment called.\n";
 	return *this;
    }

    vector& operator=(const vector& src) 
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

    friend inline std::ostream& operator<<(std::ostream& os, const vector& v)
    {
	// return os << "{" << std::hex << v.data << " @ " << std::dec << v.my_size << "}";

	if (v.data == (double*)(0x11111)) 
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
    double   *data;
};

double dot(const vector& v1, const vector& v2) { return 7; }

int main (int argc, char* argv[])
{
    vector e{};
    vector e2{{}};

    vector u{7, reinterpret_cast<double*>(0x11111)};
    std::cout << "u is " << u << std::endl;

    vector u2= {6, reinterpret_cast<double*>(0x11111)};
    std::cout << "u2 is " << u2 << std::endl;
    
    double* dp= (double*)(0x11111);
    vector u3= {5, dp};
    std::cout << "u3 is " << u3 << std::endl;

    // double array[4]= {2, 3, 4, 5}; 
    // vector u4= {4, array};
    // std::cout << "u4 is " << u4 << std::endl;
    
 
#ifndef WITH_AGGREGATE
    vector v1= {3};
    std::cout << "v1 is " << v1 << std::endl;
    vector v2{3};
    std::cout << "v2 is " << v2 << std::endl;
    
    vector v3= {{2, 3, 4}};
    vector v4{{2, 3, 4}};

    vector v5= {2, 3, 4};
    vector v6{2, 3, 4};

    vector s1= {"Nur so", 7};
    //     std::cout << "s1 is " << s1 << std::endl;

    vector s2{"Nur so", 7};
    //     std::cout << "s2 is " << s2 << std::endl;

#endif

    double d= dot({3, 4, 5}, {7, 8, 9});

    return 0 ;
}
