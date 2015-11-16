#include <iostream>

using namespace std;


template <typename T>
struct list_entry
{
    list_entry(const T& value) : value(value), next(0) {}

    T              value;
    list_entry<T>* next;
};

template <typename T>
struct list_iterator;

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
struct list_iterator
{
    typedef T value_type;
    list_iterator(list_entry<T>* entry) : entry(entry) {}

    T& operator*() { return entry->value; }
    const T& operator*() const { return entry->value; }
    list_iterator<T> operator++() { entry= entry->next; return *this; }
    bool operator!=(const list_iterator<T>& other) const { return entry != other.entry; }
    
    list_entry<T>* entry;
};

#if 1
template <typename T>
T sum(list_entry<T>* entry)
{
    T sum(0);
    for (; entry != NULL; entry= entry->next)
	sum+= entry->value;
    return sum;
}
#else
template <typename Iter, typename T>
T sum(Iter first, Iter last, T s) 
{
    for ( ; first != last; ++first)
	s = s + *first;
    return s;
}
#endif

int main() 
{
    ::list<int> l;
    l.append(5); l.append(3); l.append(7);
#if 1
    std::cout << "Sum is " << sum(l.first) << '\n';
#else
    std::cout << "Sum is " << sum(l.begin(), l.end(), 0) << '\n';
#endif
    return 0;
}
