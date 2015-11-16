// Example 3: The Dimov/Abrahams Example 
// 

#include <iostream>

template<class T> // (a) same old base template as before 
void f( T )
{
    std::cout << "Primary template called\n";
}

template<>        // (c) explicit specialization, this time of (a)
void f<>(int*)
{
    std::cout << "Template specialization for int* called\n";
}

template<class T> // (b) a second base template, overloads (a) 
void f( T* )
{
    std::cout << "Overload for T* called\n";
}

int main()
{
    int *p; 
    f( p );           // calls (b)! overload resolution ignores 
                      // specializations and operates on the base 
                      // function templates only
}
