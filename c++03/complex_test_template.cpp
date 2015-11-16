#include <iostream>

template <class T>
class complex
{
public:
  explicit complex(T rn = 0.0, T in = 0.0) : r(rn), i(in) {}
  // complex(const complex& c) : r(c.r), i(c.i) {}

  // ~complex() {  }
  
  complex& operator= (const complex& c) 
  {
    r= c.r; i= c.i;
    return *this;
  }

  complex& operator= (T rn) 
  {
    r= rn; i= 0.0;
    return *this;
  }

  inline complex operator+(const complex& c2) const
  {
    return complex(r + c2.r, i + c2.i);
  }

  complex operator+(T d) const;
  
  T const& real() const { return r; } // c
  T& real() { return r; }      // m

  T const& imag() const { return i; } // c
  T& imag() { return i; }      // m


  template <class TT>
  friend complex<TT> operator-(const complex<TT>& c1, const complex<TT>& c2);

private:
  T r, i;
};

template <class T>
inline complex<T>
complex<T>::operator+(T d) const
{
  return complex<T>(r + d, i);
}

template <class T>
inline complex<T> operator-(const complex<T>& c1, const complex<T>& c2)
{
  return complex<T>(c1.r - c2.r, c1.i - c2.i);
}

template <class T>
inline complex<T> operator-(T c1, const complex<T>& c2)
{
  return complex<T>(c1 - c2.real(), -c2.imag());
}


template <class T>
std::ostream& operator<<(std::ostream& os, complex<T> c)
{
  os << '(' << c.real() << ',' << c.imag() << ")";
  return os;
}

template <typename T>
T inline abs(const complex<T>& c)
{
  return c.real()*c.real() + c.imag()*c.imag();
}

int main()
{
  complex<double> c(7.0, 8.0), c2, c3(9.0), c4(c);
  const complex<double> cc(c3);

  c4 = c2 = c;
  c.real() = 7.0; // m

  std::cout << "cc + c4 is " << cc + c4 << std::endl; // c
  std::cout << "cc - c4 is " << cc - c4 << std::endl; // c

  return 0;
}
