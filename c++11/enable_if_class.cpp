#include <iostream>
#include <type_traits>
#include "print_compiler.hpp"

template <bool Cond, typename T= void>
using enable_if_t= typename std::enable_if<Cond, T>::type;



template <typename T>
struct vector
{
    explicit vector(int s) : s{s}, data{new T[s]} {}

    // static const bool is_int= std::is_integral<T>::value;
    // template <typename U>
    // struct is_int : std::is_integral<T> {};

    template <typename U>
    struct is_int : std::integral_constant<bool, std::is_integral<T>::value && std::is_same<U,T>::value> {};


    // template <typename U, typename = typename std::enable_if<is_int<U>::value && std::is_same<U,T>::value>::type >
    template <typename U, typename= enable_if_t<is_int<U>::value> >
    vector<T>& operator&=(const U& value)
    {
    	for (int i= 0; i < s; ++i)
    	    data[i]&= value;
    	std::cout << "&=\n";
    	return *this;
    }

#if 0
    template <typename= enable_if_t<std::is_integral<T>::value> >
    vector<T>& operator&=(const T& value) // error
    {
    	for (int i= 0; i < s; ++i)
    	    data[i]&= value;
    	std::cout << "&=\n";
    	return *this;
    }
#endif

    //vector<T>& operator|=(int mask);

    int s;
    T* data;
};


template <typename T, typename= enable_if_t<std::is_integral<T>::value> >
vector<T>& operator|=(vector<T>& v, const T& mask)
{
    for (int i= 0; i < v.s; ++i)
	v.data[i]|= mask;
    std::cout << "|=\n";
    return v;
}

// template <typename T>
// vector<T>& operator=(vector<T>& v, int value)
// {
//     for (int i= 0; i < v.s; ++i)
// 	v.data[i]= value;
//     std::cout << "Assignment\n";
//     return v;
// }

template <typename T, typename= enable_if_t<std::is_integral<T>::value> >
vector<T>& operator++(vector<T>& v)
{
    for (int i= 0; i < v.s; ++i)
	++v.data[i];
    std::cout << "++\n";
    return v;
}


int main (int argc, char* argv[]) 
{
    print_compiler();

    vector<int> v1(3);
    vector<double> v2(3);

    v1&= 7;
    // v2&= 7.0; // not enabled
 
    v1|= 7;
    // v2|= 7.0; // not enabled
 
    ++v1;
    // ++v2;

    return 0;
}

