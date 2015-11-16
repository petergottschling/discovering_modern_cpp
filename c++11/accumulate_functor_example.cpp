#include <iostream>
#include <limits>
#include <cassert>

using namespace std;

template <typename T>
struct list_entry
{
    list_entry(const T& value) : value(value), next(0) {}

    T              value;
    list_entry<T>* next;
};

template <typename T>
struct list_iterator
{
    list_iterator(list_entry<T>* p) : p(p) {}
    bool operator!=(const list_iterator<T>& that) const { return p != that.p; }
    list_iterator<T> operator++() { p= p->next; return *this; }
    list_iterator<T> operator++(int) 
    {
	list_iterator<T> tmp(*this);
	p= p->next;
	return tmp;
    }
    T& operator*() { return p->value; }
    T operator*() const { return p->value; }

  private:
    list_entry<T>* p;
};

template <typename T>
struct list
{
    list() : first(0), last(0) {}
    ~list() { while (first) { list_entry<T> *tmp= first->next; delete first; first= tmp; } }
    void append(const T& x) { last= (first ? last->next : first)= new list_entry<T>(x); }
    list_iterator<T> begin() { return list_iterator<T>(first); }
    list_iterator<T> end() { return list_iterator<T>(0); }

    list_entry<T> *first, *last;
};


class vector
{
    typedef double T;
    typedef vector self;
    void check_size(unsigned that_size) const { assert(my_size == that_size); }
    void check_index(unsigned i) const { assert(i < my_size); }
  public:
    vector(int n) : my_size(n), data(new double[my_size]) {}

    vector(const vector& v)
      : my_size(v.my_size), data(new double[my_size]) 
    {
        for (unsigned i= 0; i < my_size; i++) 
            data[i]= v.data[i];
	std::cout << "Copy constructor called.\n";
    }


    ~vector()  { delete[] data; }

    vector& operator=(const vector& src) 
    {
	if (this == &src) 
	    return *this;
	assert(my_size == src.my_size);
	for (unsigned i= 0; i < my_size; i++)
	    data[i]= src.data[i];
	return *this;
    }

    vector(std::initializer_list<double> values)
      : my_size(values.size()), data(new double[my_size]) 
    {
	std::copy(values.begin(), values.end(), data);
	std::cout << "Init constructor called.\n";
    }

    self& operator=(const std::initializer_list<double>& values)
    {
        assert(my_size == values.size());
	std::copy(values.begin(), values.end(), data);
	std::cout << "Init assignment called.\n";
 	return *this;
    }

    vector(vector&& v) 
      : my_size(v.my_size), data(v.data) 
    {
	v.data= 0;
	v.my_size= 0;
	std::cout << "Move constructor called.\n";
    }

    // quick hacks!!!
    double* begin() { return data; }
    double* end()   { return data+my_size; }

  private:
    unsigned my_size;
    double   *data;
};



template <typename Iter, typename T>
T sum(Iter it, Iter end, T init)
{
    for (; it != end; ++it)
	init+= *it;
    return init;
}

template <typename Iter, typename T, typename BinaryFunction>
T accumulate(Iter it, Iter end, T init, BinaryFunction op)
{
    for (; it != end; ++it)
	init= op(init, *it);
    return init;
}

template <typename T>
struct add
{
    T operator()(const T& x, const T& y) const { return x + y; }
};

struct times
{
    template <typename T>
    T operator()(const T& x, const T& y) const { return x * y; }    
};

struct maximum
{
    template <typename T>
    T operator()(const T& x, const T& y) const { return std::max(x, y); }    
};


int main (int argc, char* argv[]) 
{
    int    ai[]= {2, 4, 7};
    double ad[]= {2., 4.5, 7.};

    cout << "sum ai is " << sum(ai, &ai[3], 0) << '\n';
    cout << "sum ad is " << sum(ad, ad+3, 0.0) << '\n';

    add<int> my_add;
    
    cout << "sum ai is " << accumulate(ai, &ai[3], 0, my_add) << '\n';
    cout << "sum ad is " << accumulate(ad, ad+3, 0.0, add<double>()) << '\n';
    cout << "product ad is " << accumulate(ad, ad+3, 1.0, times()) << '\n';
    cout << "max ad is " << accumulate(ad, ad+3, -numeric_limits<double>::max(), maximum()) << '\n';


    list<float>  l;
    cout << "sum l [empty] is " << sum(l.begin(), l.end(), 0.0f) << '\n';
    cout << "sum l [empty] is " << accumulate(l.begin(), l.end(), 0.0f, add<float>()) << '\n';
    cout << "product l is " << accumulate(l.begin(), l.end(), 1.0f, times()) << '\n';
    cout << "max l is " << accumulate(l.begin(), l.end(), -numeric_limits<float>::max(), maximum()) << '\n';

    l.append(2.0f); l.append(4.0f); l.append(7.0f); 

    cout << "sum l is " << sum(l.begin(), l.end(), 0.0f) << '\n';
    cout << "sum l is " << accumulate(l.begin(), l.end(), 0.0, add<double>()) << '\n';
    cout << "product l is " << accumulate(l.begin(), l.end(), 1.0f, times()) << '\n';
    cout << "max l is " << accumulate(l.begin(), l.end(), -numeric_limits<float>::max(), maximum()) << '\n';
    
#if 0
    cout << "min float == " << numeric_limits<float>::min()  << '\n';
    cout << "max float == " << numeric_limits<float>::max()  << '\n';

    cout << "min double == " << numeric_limits<double>::min()  << '\n';
    cout << "max double == " << numeric_limits<double>::max()  << '\n';

    cout << "min int == " << numeric_limits<int>::min()  << '\n';
    cout << "max int == " << numeric_limits<int>::max()  << '\n';
#endif

    vector v= {7.0, 8.0, 11.0};
    double s= accumulate(v.begin(), v.end(), 0.0, add<double>{});
    double p= accumulate(v.begin(), v.end(), 1.0, times{});
    cout << "maximum of v is " << accumulate(v.begin(), v.end(), -numeric_limits<double>::max(), maximum{});


    return 0 ;
}
