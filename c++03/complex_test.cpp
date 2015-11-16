#include <iostream>

class complex_algebra {};

class complex
{
  public:
    complex() : r(), i() {}
    // complex() : r(0.0), i(0.0) {}
    complex(double rn) : r(rn), i(0.0) {}
    complex(double rn, double in) : r(rn), i(in) {}
    // complex(double rn= 0.0, double in= 0.0) : r(rn), i(in) {}
    // complex(const complex& c) : r(c.r), i(c.i) {}

    // ~complex() {  }
  
    complex& operator= (const complex& c) 
    {
	r= c.r; i= c.i;
	return *this;
    }

    complex& operator= (double rn) 
    {
	r= rn; i= 0.0;
	return *this;
    }

    // complex operator+(const complex& c2) const
    // {
    //     std::cout << " -- c+c -- "; 
    //     return complex(r + c2.r, i + c2.i);
    // }

    // complex operator-() const { return complex(-r, -i); }

    complex operator+(double d) const;
  
    friend inline double const& real(const complex& c) { return c.r; } 
    friend inline double& real(complex& c) { return c.r; } 

    friend inline double const& imag(const complex& c) { return c.i; } 
    friend inline double& imag(complex& c) { return c.i; }  

    // double const& real() const { return r; } // c
    // double& real() { return r; }      // m

    // double const& imag() const { return i; } // c
    // double& imag() { return i; }      // m

    friend complex operator-(const complex& c1, const complex& c2);

    friend std::ostream& operator<<(std::ostream&, const complex&);
    friend class complex_algebra;

  private:
    double r, i;
};

inline complex operator+(const complex& c1, const complex& c2)
{
    std::cout << " -- c+c -- "; 
    return complex(real(c1) + real(c2), imag(c1) + imag(c2));
}

inline complex operator+(double d, const complex& c2)
{
    std::cout << " -- d+c -- "; 
    return complex(d + real(c2), imag(c2));
}

inline complex
complex::operator+(double d) const
{
    std::cout << " -- c+d -- "; 
    return complex(r + d, i);
}

inline complex operator-(const complex& c1, const complex& c2)
{
    std::cout << " -- c-c -- "; 
    return complex(c1.r - c2.r, c1.i - c2.i);
}

// inline complex operator-(double c1, const complex& c2)
// {
//     std::cout << " -- d-c -- ";     
//     return complex(c1 - c2.real(), -c2.imag());
// }
 
complex operator-(const complex& c1) 
{ std::cout << "free unary -\n"; return complex(-real(c1), -imag(c1)); }


std::ostream& operator<<(std::ostream& os, const complex& c)
{
    return os << '(' << real(c) << ',' << imag(c) << ")";
}


struct whatever
{
    operator complex() { return complex(3, 4); }
};

struct something_else
{
    operator whatever() { return whatever(); }
};

int main()
{
    complex c(7.0, 8.0), c2, c3(9.0), c4(c);
    std::cout << "c2 = " << c2 << '\n';
    const complex cc(c3);
    whatever dd;
    -dd;

    std::cout << "whatever is " << dd// .operator complex()
	      << std::endl;     
    something_else se;
    std::cout << "something_else is " << whatever(se)
	      << std::endl;     
    

    c4 = c2 = c;
    real(c) = 7.0; 

    std::cout << "cc + c4 is " << cc + c4 << std::endl; 
    std::cout << "cc + 4.2 is " << cc + 4.2 << std::endl; 
    std::cout << "4.2 + c4 is " << 4.2 + c4 << std::endl; 
    std::cout << "whatever + c4 is " << dd + c4 << std::endl;     
    std::cout << "whatever + 4.2 is " << dd + 4.2 << std::endl;     
    std::cout << "4.2 + whatever is " << 4.2 + dd << std::endl;     
    // std::cout << "cc - c4 is " << cc - c4 << std::endl; 
    // std::cout << "3.5 - c4 is " << 3.5 - c4 << std::endl; 
    // std::cout << "3 - c4 is " << 3 - c4 << std::endl; 

    return 0;
}
