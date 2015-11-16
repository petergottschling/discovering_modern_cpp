#include <cassert>
#include <iostream>
#include <boost/timer.hpp>


template <unsigned Offset, unsigned Max>
struct assign
{
    template <typename U, typename V>
    void operator()(U& u, const V& v, unsigned i)
    {
	u[i+Offset]= v[i+Offset];
	assign<Offset+1, Max>()(u, v, i);
    }
};

template <unsigned Max>
struct assign<Max, Max> 
{
    template <typename U, typename V>
    void operator()(U& u, const V& v, unsigned i) {}
};



template <typename T>
class vector 
{
    void check_size(int that_size) const { assert(my_size == that_size); }
    void check_index(int i) const { assert(i >= 0 && i < my_size); }
  public:
    typedef T   value_type;

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

    template <typename Src>
    vector& operator=(const Src& that) 
    {
	check_size(size(that));
	unsigned s= my_size, sb= s / 4 * 4;

	for (unsigned i= 0; i < sb; i+= 4)
	    assign<0, 4>()(*this, that, i);

	for (unsigned i= sb; i < s; i++) 
	    data[i]= that[i];

	return *this;
    }

    template <unsigned BSize, typename Src>
    vector& operator=(const Src& that) 
    {
	check_size(size(that));
	unsigned s= my_size, sb= s / BSize * BSize;

	for (unsigned i= 0; i < sb; i+= BSize)
	    assign<0, BSize>()(*this, that, i);

	for (unsigned i= sb; i < s; i++) 
	    data[i]= that[i];
	return *this;
    }

    friend int size(const vector& x) { return x.my_size; }

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
  for (int i= 0; i < size(v); ++i) os << v[i] << ',';
  os << ']';
  return os ;
}
 

template <typename V1, typename V2>
class vector_sum
{
    typedef vector_sum   self;
    void check_index(int i) const { assert(i >= 0 && i < size(v1)); }
  public:
    typedef typename V1::value_type value_type;

    vector_sum(const V1& v1, const V2& v2) : v1(v1), v2(v2) 
    { 
	assert(size(v1) == size(v2));
    }

    friend int size(const self& x) { return size(x.v1); }

    value_type operator[](int i) const { check_index(i); return v1[i] + v2[i]; }

  private:
    const V1& v1;
    const V2& v2;
};

template <typename V1, typename V2>
vector_sum<V1, V2> inline operator+(const V1& x, const V2& y) 
{
    return vector_sum<V1, V2>(x, y);
}

template <unsigned BSize, typename V>
class unroll_vector
{
  public:
    unroll_vector(V& ref) : ref(ref) {}

    template <typename Src>
    V& operator=(const Src& that) 
    {
	assert(size(ref) == size(that));
	unsigned s= size(ref), sb= s / BSize * BSize;

	for (unsigned i= 0; i < sb; i+= BSize)
	    assign<0, BSize>()(ref, that, i);

	for (unsigned i= sb; i < s; i++) 
	    ref[i]= that[i];
	return ref;
    }
  private:
    V&    ref;
};

template <unsigned BSize, typename Vector>
unroll_vector<BSize, Vector> inline unroll(Vector& v)
{
    return unroll_vector<BSize, Vector>(v);
}

template <unsigned BSize, typename Vector>
void bench_unroll(Vector& u, const Vector& v, const Vector& w, const unsigned rep)
{
    boost::timer t1; 
    for (unsigned j= 0; j < rep; j++)
	unroll<BSize>(u)= v + v + w;
    std::cout << "Compute time unroll<" << BSize << ">(u)= v + v + w is " 
	      << 1000000.0 * t1.elapsed() / double(rep) << " mmicros.\n";
    std::cout << "u[0] is " << u[0] << '\n';
}

int main(int argc, char** argv)  
{
    const unsigned s= 1000; 
    // if (argc > 1) s= atoi(argv[1]);
    vector<float> u(s), v(s), w(s);

    for (unsigned i= 0; i < s; i++) { 
	v[i]= float(i);  
	w[i]= float(2*i + 15);
    }
    const unsigned rep= 1000000; 

#if 1    
    boost::timer t; 
    for (unsigned j= 0; j < rep; j++)
	u= v + v + w;
    std::cout << "Compute time is " << 1000000.0 * t.elapsed() / double(rep) << " mmicros.\n";
    std::cout << "u[0] is " << u[0] << '\n';

    u.operator=<4>(v + v + w);
#endif 

#if 1    
    bench_unroll<1>(u, v, w, rep);
    bench_unroll<2>(u, v, w, rep);
    bench_unroll<4>(u, v, w, rep);
    bench_unroll<6>(u, v, w, rep);
    bench_unroll<8>(u, v, w, rep);
#endif 

    return 0 ;
}

 
