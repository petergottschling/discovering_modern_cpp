#include <cassert>
#include <iostream>
#include <boost/static_assert.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_same.hpp>

template <typename V1, typename V2> class vector_sum;

template <typename T>
class vector 
{
    void check_size(int that_size) const { assert(my_size == that_size); }
    void check_index(int i) const { assert(i >= 0 && i < my_size); }
  public:
    typedef T    value_type;

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

    template <typename Src>
    vector& operator=( const Src& that ) 
    {
	check_size(that.size());
	for (int i= 0; i < my_size; ++i)
	    data[i]= that[i];
	return *this;
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

template <typename V1, typename V2>
class vector_sum
{
  public:
    typedef typename V1::value_type value_type;
    BOOST_STATIC_ASSERT((boost::is_same<typename V2::value_type, value_type>::value));

    vector_sum(const V1& v1, const V2& v2) : v1(v1), v2(v2) 
    {
	assert(v1.size() == v2.size());
    }

    int size() const { return v1.size(); }

    value_type operator[](int i) const { return v1[i] + v2[i]; }

  private:
    const V1 &v1;
    const V2 &v2;
};

template <typename  V1, typename V2>
// typename boost::enable_if_c<is_vector<V1>::value && is_vector<V2>::value, vector_sum<V1, V2> >::type
vector_sum<V1, V2> 
inline operator+( const V1& x, const V2& y ) 
{
    return vector_sum<V1, V2>(x, y) ;
}





int main() 
{

    vector<float> v( 4 ), w(4), x(4), y(4)  ;
    v[0]= v[1]= 1.0; v[2]= 2.0 ; v[3] = -3.0 ;
    w[0]= w[1]= 1.3; w[2]= 2.5 ; w[3] = -13.0 ;
    x[0]= x[1]= 1.0; x[2]= 2.0 ; x[3] = 3.0 ;

    std::cout << "v = " << v << std::endl ;

    y= v + w + x;
    std::cout << "y = " << y << std::endl ;

    return 0 ;
}
