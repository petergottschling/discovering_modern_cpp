#include <iostream>
#include <limits>

using namespace std;

#if 0
int sum(int* array, int length)
{
    int sum= 0;
    for (int i= 0; i < length; i++)
	sum+= array[i];
    return sum;
}

double sum(double* array, int length)
{
    double sum= 0;
    for (int i= 0; i < length; i++)
	sum+= array[i];
    return sum;
}
#endif

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
    list_iterator(list_entry<T>* entry) : entry(entry) {}
    bool operator!=(const list_iterator<T>& that) const 
    { return entry != that.entry; }

    list_iterator<T> operator++() 
    { entry= entry->next; return *this; }

    list_iterator<T> operator++(int) 
    {
	list_iterator<T> tmp(*this);
	entry= entry->next;
	return tmp;
    }
    T& operator*() { return entry->value; }
    T operator*() const { return entry->value; }

  private:
    list_entry<T>* entry;
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

template <typename T>
T sum(const T* array, int n)
{
    T sum(0);
    for (int i= 0; i < n; i++)
	sum+= array[i];
    return sum;
}

template <typename T, unsigned N>
T sum(const T (&array)[N])
{
    T sum(0);
    for (unsigned i= 0; i < N; i++)
	sum+= array[i];
    return sum;
}


template <typename T>
T sum(const list<T>& l)
{
    T sum= 0;
    for (list_entry<T>* entry= l.first; entry != 0; entry= entry->next)
	sum+= entry->value; // (*entry).value;
    return sum;
}

template <typename T>
inline T accumulate_array(T* a, T* a_end)
{
    T sum(0);
    for (; a != a_end; ++a)
	sum+= *a;
    return sum;
}

template <typename Iter, typename T>
inline T accumulate(Iter it, Iter end, T init)
{
    for (; it != end; ++it)
	init+= *it;
    return init;
}



int main (int argc, char* argv[]) 
{
    int    ai[]= {2, 4, 7};
    double ad[]= {2., 4.5, 7.};

    cout << "sum ai is " << sum(ai, 3) << '\n';
    cout << "sum ad is " << sum(ad, 3) << '\n';

    cout << "sum ai is " << sum(ai) << '\n';
    cout << "sum ad is " << sum(ad) << '\n';

    cout << "sum ai is " << accumulate_array(ai, &ai[3]) << '\n';
    cout << "sum ad is " << accumulate_array(ad, ad+3) << '\n';

    cout << "sum ai is " << accumulate(ai, &ai[3], 0) << '\n';
    cout << "sum ad is " << accumulate(ad, ad+3, 0.0) << '\n';


    list<float>  l;
    cout << "sum l [empty] is " << sum(l) << '\n';
    cout << "sum l [empty] is " << accumulate(l.begin(), l.end(), 0.0f) << '\n';

    l.append(2.0f); l.append(4.0f); l.append(7.0f); 

    cout << "sum l is " << sum(l) << '\n';
    cout << "sum l is " << accumulate(l.begin(), l.end(), 0.0) << '\n';
    

    return 0 ;
}
