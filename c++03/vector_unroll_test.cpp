#include <cassert>
#include <iostream>
#include <boost/timer.hpp>

const unsigned rep= 500000; 

template <typename T>
class vector 
{
    void check_size(int that_size) const { assert(my_size == that_size); }
    void check_index(int i) const { assert(i >= 0 && i < my_size); }
  public:
    explicit vector(int size)
      : my_size(size), data( new T[my_size] )
    {}

    vector()
      : my_size(0), data(0)
    {}

    vector( const vector& that )
      : my_size(that.my_size), data( new T[my_size] )
    {
	for (int i= 0; i < my_size; ++i)
	    data[i]= that.data[i];
    }

    ~vector() { if (data) delete [] data ; }

    vector& operator=( const vector& that ) 
    {
	check_size(that.my_size);
	for (int i= 0; i < my_size; ++i)
	    data[i]= that.data[i];
    }

    int size() const { return my_size ; }

    const T& operator[]( int i ) const 
    {
	check_index(i);
	return data[i];
    }
		     
    T& operator[]( int i ) 
    {
	check_index(i);
	return data[i] ;
    }

  private:
    int   my_size ;
    T*    data ;
};


template <typename T>
std::ostream& operator<<(std::ostream& os, const vector<T>& v)
{
  os << '[';
  for (int i= 0; i < v.size(); ++i) os << v[i] << ',';
  os << ']';
  return os ;
}

template <unsigned Offset, unsigned Max>
struct my_axpy_ftor
{
    template <typename Vector>
    void operator()(Vector& u, const Vector& v, const Vector& w, unsigned i)
    {
	u[i+Offset]= 3.0f * v[i+Offset] + w[i+Offset]; 
	my_axpy_ftor<Offset+1, Max>()(u, v, w, i);
    }
};
 
template <unsigned Max>
struct my_axpy_ftor<Max, Max>
{
    template <typename Vector>
    void operator()(Vector& u, const Vector& v, const Vector& w, unsigned i) {}
};
 

template <unsigned BSize, typename Vector>
void inline my_axpy(Vector& u, const Vector& v, const Vector& w)
{
    unsigned s= u.size(), sb= s / BSize * BSize;

    for (unsigned i= 0; i < sb; i+= BSize) 
	my_axpy_ftor<0, BSize>()(u, v, w, i);

    for (unsigned i= sb; i < s; i++) 
	u[i]= 3.0f * v[i] + w[i]; 
}

template <unsigned BSize, typename Vector>
void test(Vector& u, const Vector& v, const Vector& w)
{
    boost::timer unrolled;
    for (unsigned j= 0; j < rep; j++)
	my_axpy<BSize>(u, v, w);
    std::cout << "Unrolled<" << BSize << "> loop takes " 
	      << unrolled.elapsed() / double(rep) * 1000000 << "µs\n";
    std::cout << u << '\n';
}

int main(int argc, char** argv)  
{
    unsigned s= 1000;
    if (argc > 1) s= atoi(argv[1]);
    vector<float> u(s), v(s), w(s);

    for (unsigned i= 0; i < s; i++) { 
	v[i]= float(i);
	w[i]= float(2*i + 15);
    }
    
    for (unsigned j= 0; j < 3; j++) 
	for (unsigned i= 0; i < s; i++) 
	    u[i]= 3.0f * v[i] + w[i]; 

    boost::timer unrolled;
    for (unsigned j= 0; j < rep; j++) {
	unsigned sb= s / 4 * 4;
	for (unsigned i= 0; i < sb; i+= 4) {
	    u[i]= 3.0f * v[i] + w[i]; 
	    u[i+1]= 3.0f * v[i+1] + w[i+1]; 
	    u[i+2]= 3.0f * v[i+2] + w[i+2]; 
	    u[i+3]= 3.0f * v[i+3] + w[i+3];
	} 
	for (unsigned i= sb; i < s; i++)
	    u[i]= 3.0f * v[i] + w[i]; 
    }
    std::cout << "Unrolled loop takes " << unrolled.elapsed() / double(rep) * 1000000 << "µs\n";
    std::cout << u << '\n';

    boost::timer native;
    for (unsigned j= 0; j < rep; j++) 
	for (unsigned i= 0; i < s; i++) 
	    u[i]= 3.0f * v[i] + w[i]; 
    std::cout << "Native loop takes " << native.elapsed() / double(rep) * 1000000 << "µs\n";
    std::cout << u << '\n';

    test<1>(u, v, w);
    test<2>(u, v, w);
    test<4>(u, v, w);
    test<6>(u, v, w);
    test<8>(u, v, w);
    test<10>(u, v, w);
    test<12>(u, v, w);
    test<16>(u, v, w);
    test<32>(u, v, w);
    test<64>(u, v, w);

    return 0 ; 
} 

 
