#include <cassert>
#include <iostream>
#include <memory>
#include <algorithm>

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

    vector(const vector& that)
      : my_size(that.my_size), data(new T[my_size])
    {
	std::copy(&that.data[0], &that.data[that.my_size], &data[0]);
    }

    vector& operator=(const vector& that) 
    {
	check_size(that.my_size);
	std::copy(&that.data[0], &that.data[that.my_size], &data[0]);
	return *this;
    }

    int size() const { return my_size; }

    const T& operator[](int i) const 
    {
	check_index(i);
	return data[i];
    }
		     
    T& operator[](int i) 
    {
	check_index(i);
	return data[i];
    }

    vector operator+(const vector& that) const 
    {
	check_size(that.my_size);
	vector sum(my_size);
	for (int i= 0; i < my_size; ++i) 
	    sum[i] = data[i] + that[i];
	return sum;
    }
  private:
    int                   my_size;
    std::unique_ptr<T[]>  data;
};


template <typename T>
std::ostream& operator<<(std::ostream& os, const vector<T>& v)
{
  os << '[';
  for (int i= 0; i < v.size(); ++i) os << v[i] << ',';
  os << ']';
  return os;
}

class vector_bool_proxy
{
  public:
    vector_bool_proxy(unsigned char& byte, int p) : byte(byte), mask(1 << p) {}

    operator bool() const { return byte & mask; }

    vector_bool_proxy& operator=(bool b) 
    { 
	if (b)
	    byte|= mask;
	else
	    byte&= ~mask;
	return *this; 
    }

  private:
    unsigned char& byte;
    unsigned char  mask;
};

template <>
class vector<bool> 
{
  public:
    explicit vector(int size)
      : my_size(size), data(new unsigned char[(my_size+7) / 8])
    {}

    vector() : my_size(0) {}
  
    bool operator[](int i) const { return (data[i/8] >> i%8) & 1; }

    vector_bool_proxy operator[](int i) 
    { return {data[i/8], i%8};   }

  private:
    int                              my_size;
    std::unique_ptr<unsigned char[]> data;
};





int main() 
{
#if 1
    vector<float> v( 4 );
    v[0]= v[1]= 1.0; v[2]= 2.0; v[3] = -3.0;

    std::cout << v << std::endl;

    vector<float> w(v.size());
    w = v;

    vector<float> sum( w + v );
    vector<float> z( v );
#endif

    vector<bool>  b(13);
    for (int i= 0; i < 13; i++)
	b[i]= i & 1;
    for (int i= 0; i < 13; i++)
	std::cout << b[i];
    std::cout << '\n';

    return 0;
}
