// Prime number computation by Erwin Unruh

template <int i> struct D { D(void*); operator int(); };

template <int p, int i> struct is_prime {
 enum { prim = (p==2) || (p%i) && is_prime<(i>2?p:0), i-1> :: prim };
};

template <int i> struct Prime_print {
 Prime_print<i-1> a;
 enum { prim = is_prime<i, i-1>::prim };
 void f() { D<i> d = prim ? 1 : 0; a.f();}
};

template<> struct is_prime<0,0> { enum {prim=1}; };
template<> struct is_prime<0,1> { enum {prim=1}; };

template<> struct Prime_print<1> {
 enum {prim=0};
 void f() { D<1> d = prim ? 1 : 0; };
};

int main() {
 Prime_print<18> a;
 a.f();
}
