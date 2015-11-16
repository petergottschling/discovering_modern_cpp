#include <iostream>

template <typename T>
class complex
{
public:
  explicit complex(const T& rn = 0.0, const T& in = 0.0) : r(rn), i(in) {}
  // complex(const complex& c) : r(c.r), i(c.i) {}

  // ~complex() {  }
  
  complex& operator= (const complex& c) 
  {
    r= c.r; i= c.i;
    return *this;
  }

  complex& operator= (const T& rn) 
  {
    r= rn; i= 0.0;
    return *this;
  }

  inline complex operator+(const complex& c2) const
  {
    return complex(r + c2.r, i + c2.i);
  }

  complex operator+(const T& d) const;
  
  T const& real() const { return r; } // c
  T& real() { return r; }      // m

  T const& imag() const { return i; } // c
  T& imag() { return i; }      // m

  template <typename U>
  friend complex<U> operator-(const complex<U>& c1, const complex<U>& c2);

private:
  T r, i;
};

template <typename T>
inline complex<T>
complex<T>::operator+(const T& d) const
{
  return complex<T>(r + d, i);
}

template <typename T>
inline complex<T> operator-(const complex<T>& c1, const complex<T>& c2)
{
  return complex<T>(c1.r - c2.r, c1.i - c2.i);
}

template <typename T>
inline complex<T> operator-(T c1, const complex<T>& c2)
{
  return complex<T>(c1 - c2.real(), -c2.imag());
}

template <typename T>
std::ostream& operator<<(std::ostream& os, complex<T> c)
{
  os << '(' << c.real() << ',' << c.imag() << ")";
  return os;
}



int main()
{
  complex<long double> c(7.0, 8.0), c2, c3(9.0), c4(c);
  const complex<long double> cc(c3);

  c4 = c2 = c;
  c.real() = 7.0; // m

  std::cout << "cc + c4 is " << cc + c4 << std::endl; // c
  std::cout << "cc - c4 is " << cc - c4 << std::endl; // c

  return 0;
}
