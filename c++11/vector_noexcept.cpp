#include <cassert>
#include <iostream>
#include <type_traits>
#include <initializer_list>
#include <algorithm>


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

    vector(std::initializer_list<value_type> values)
      : my_size(values.size()), data(new value_type[my_size]) 
    {
	std::copy(values.begin(), values.end(), data);
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

    template <typename Src>
    vector& operator=(Src&& that) 
    {
	check_size(size(that));
	std::swap(data, that.data);
	return *this;
    }

    friend int size(const vector& x) { return x.my_size; }

    const T& operator[](int i) const noexcept { check_index(i); return data[i]; }
    T& operator[](int i) noexcept { check_index(i); return data[i];  }

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

template <typename Vector>
inline Vector operator+(const Vector& x, const Vector& y) noexcept(noexcept(x[0]))
{
    assert(size(x) == size(y));
    Vector sum(size(x));
    for (int i= 0; i < size(x); ++i)
	sum[i]= x[i] + y[i];
    // throw 4; // terminates program
    return sum;
}

template <typename T>
inline T clone(const T& x) 
    noexcept(std::is_nothrow_copy_constructible<T>::value)
{
    // throw 7; // terminates program
    return x; 
}

int main() 
{
    try {
	double d= clone(4.2);
    } catch (int i) { std::cout << "#1: Caught " << i << "\n"; }

    vector<double> x= {3., 4., 5.}, y(3);
    
    try {
	y= x + x;
	std::cout << "y = " << y << '\n';
    } catch (int i) { std::cout << "#2: Caught " << i << "\n"; }

    return 0;
}
