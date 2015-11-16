#include <cassert>
#include <iostream>


template <typename T>
class vector 
{
  public:
    typedef T   value_type;

    void check_size(int that_size) const { assert(my_size == that_size); }
    void check_index(int i) const { assert(i >= 0 && i < my_size); }

    explicit vector(int size) : my_size(size), data(new T[my_size])    {}
    vector() : my_size(0), data(0)  {}

    vector(const vector& that)
      : my_size(that.my_size), data(new T[my_size])
    {
	for (int i= 0; i < my_size; ++i)
	    data[i]= that.data[i];
    }

    ~vector() { if (data) delete [] data; }

    template <typename Src>
    vector& operator=(const Src& that) 
    {
	check_size(size(that));
	for (int i= 0; i < my_size; ++i)
	    data[i]= that[i];
	return *this;
    }

    friend int size(const vector& x) { return x.my_size; }

    const T& operator[](int i) const { check_index(i); return data[i]; }
    T& operator[](int i) { check_index(i); return data[i];  }

  private:
    int   my_size;
    T*    data;
};



template <typename T>
inline std::ostream& operator<<(std::ostream& os, const vector<T>& v)
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


int main() 
{
    vector<float> x(4), y(4), z(4), w(4);
    x[0]= x[1]= 1.0; x[2]= 2.0; x[3] = -3.0;
    y[0]= y[1]= 1.7; y[2]= 4.0; y[3] = -6.0;
    z[0]= z[1]= 4.1; z[2]= 2.6; z[3] = 11.0;

    std::cout << "x = " << x << std::endl;
    std::cout << "y = " << y << std::endl;
    std::cout << "z = " << z << std::endl;

    w= x + y + z;
    std::cout << "w= x + y + z = " << w << std::endl;

    return 0;
}
