#include <cassert>
#include <iostream>

template <typename T> class vector_sum;
template <typename T> class vector_sum3;

template <typename T>
class vector 
{
  public:
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

    vector& operator=(const vector& that) 
    {
	check_size(that.my_size);
	for (int i= 0; i < my_size; ++i)
	    data[i]= that.data[i];
	return *this;
    }

    vector& operator=(const vector_sum<T>& that) 
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

template <typename T>
class vector_sum
{
    void check_index(int i) const { assert(i >= 0 && i < size(v1)); }
  public:
    vector_sum(const vector<T>& v1, const vector<T>& v2) : v1(v1), v2(v2) 
    { 
	assert(size(v1) == size(v2));
    }

    friend int size(const vector_sum& x) { return size(x.v1); }

    T operator[](int i) const { check_index(i); return v1[i] + v2[i]; }

    template <typename U>
    friend vector_sum3<U> inline operator+(const vector_sum<U>& x, const vector<U>& y);

  private:
    const vector<T>& v1, v2;
};

template <typename T>
vector_sum<T> inline operator+(const vector<T>& x, const vector<T>& y) 
{
    return vector_sum<T>(x, y);
}

#if 1
template <typename T>
class vector_sum3
{
    void check_index(int i) const { assert(i >= 0 && i < size(v1)); }
  public:
    vector_sum3(const vector<T>& v1, const vector<T>& v2, const vector<T>& v3) : v1(v1), v2(v2), v3(v3) 
    { 
	assert(size(v1) == size(v2)); assert(size(v1) == size(v3));
    }

    friend int size(const vector_sum3& x) { return size(x.v1); }

    T operator[](int i) const { check_index(i); return v1[i] + v2[i] + v3[i]; }
  private:
    const vector<T>& v1, v2, v3;
};

template <typename T>
vector_sum3<T> inline operator+(const vector_sum<T>& x, const vector<T>& y) 
{
    return vector_sum3<T>(x.v1, x.v2, y);
}
#endif

#if 0
template <typename T>
vector<T> inline operator+(const vector<T>& x, const vector<T>& y) 
{
    x.check_size(size(y));
    vector<T> sum(size(x));
    for (int i= 0; i < size(x); ++i) 
	sum[i] = x[i] + y[i];
    return sum;
}
#endif

template <typename T>
void inline add3(const vector<T>& x, const vector<T>& y, const vector<T>& z, vector<T>& sum) 
{
    x.check_size(size(y));
    x.check_size(size(z));
    x.check_size(size(sum));
    for (int i= 0; i < size(x); ++i) 
	sum[i] = x[i] + y[i] + z[i];
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

    w= x + y;
    x + y + z;
#if 0
    w= x + y + z;
    std::cout << "w= x + y + z = " << w << std::endl;

    add3(x, y, z, w);
    std::cout << "w= x + y + z = " << w << std::endl;
#endif 
    return 0;
}
