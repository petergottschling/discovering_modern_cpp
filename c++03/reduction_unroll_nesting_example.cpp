#include <cmath>
#include <cassert>
#include <iostream>
#include <boost/timer.hpp>



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
	for (unsigned i= 0; i < my_size; i++) 
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
 
#if 0
template <unsigned BSize, typename Value>
struct multi_tmp
{
    typedef multi_tmp<BSize-1, Value> sub_type;

    multi_tmp(const Value& v) : value(v), sub(v) {}

    Value     value;
    sub_type  sub;
};

template <typename Value>
struct multi_tmp<0, Value>
{
    multi_tmp(const Value& v) {}
};
#endif

template <unsigned BSize, typename Value>
struct multi_tmp
{
    typedef multi_tmp<BSize-1, Value> sub_type;

    multi_tmp(const Value& v) : value(v), sub(v) {}

    Value sum() const { return value + sub.sum(); }

    template <typename Op>
    Value reduce(Op op, const Value& init) const { return op(value, sub.reduce(op, init)); }
    
    Value     value;
    sub_type  sub;
};

template <typename Value>
struct multi_tmp<0, Value>
{
    multi_tmp(const Value& v) {}
    Value sum() const { return 0; }

    template <typename Op>
    Value reduce(Op, const Value& init) const { return init; }
};



template <unsigned Offset, unsigned Max>
struct one_norm_ftor
{
    template <typename S, typename V>
    void operator()(S& sum, const V& v, unsigned i)
    {
	using std::abs;
	sum.value+= abs(v[i+Offset]);
	one_norm_ftor<Offset+1, Max>()(sum.sub, v, i);
    }
};

template <unsigned Max>
struct one_norm_ftor<Max, Max> 
{
    template <typename S, typename V>
    void operator()(S& sum, const V& v, unsigned i) {}
};

template <unsigned BSize, typename Vector>
typename Vector::value_type
inline one_norm(const Vector& v)
{
    using std::abs;
    typedef typename Vector::value_type value_type;
    multi_tmp<BSize, value_type> multi_sum(0);

    unsigned s= size(v), sb= s / BSize * BSize;   
    for (unsigned i= 0; i < sb; i+= BSize)
	one_norm_ftor<0, BSize>()(multi_sum, v, i);

    value_type sum= multi_sum.sum();
    for (unsigned i= sb; i < s; i++) 
	sum+= abs(v[i]);

    return sum;
}


template <unsigned BSize, typename Vector>
void inline bench_unroll(const Vector& v, const unsigned rep)
{
    typename Vector::value_type norm;
    boost::timer t1; 
    for (unsigned j= 0; j < rep; j++)
	norm= one_norm<BSize>(v);
    std::cout << "Compute time one_norm<" << BSize << ">(v) is " 
	      << 1000000.0 * t1.elapsed() / double(rep) << " mmicros.\n";
    std::cout << "one_norm<" << BSize << ">(v) is " << norm << '\n';
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
    const unsigned rep= 1000000; 

    bench_unroll<1>(v, rep);
    bench_unroll<2>(v, rep); 
    bench_unroll<4>(v, rep);
    bench_unroll<6>(v, rep);
    bench_unroll<8>(v, rep);

    return 0 ;
}

 
