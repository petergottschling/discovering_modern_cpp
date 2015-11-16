#include <iostream>

template <typename T>
inline T max(T x, T y)
{
    return x < y ? y : x;
}

// template <typename T>
// inline T max(T x, T y)
// {
//     return x < y ? y.value : x.value;
// }

// Example that doesn't work with double
// template <typename T>
// inline T max(T x, T y)
// {
//     return x < y ? y : (x & x);
// }

// instantiation
template short max<short>(short, short);

// Specialization: declaration only
// template <> long max<long>(long, long);
template <> long max<long>(long x, long y) 
{ 
    std::cout << "Specialized: "; 
    return x < y ? y : x; 
}

// Overloads
long max(int x, long y) 
{ 
    std::cout << "Overloaded: "; 
    return x < y ? y : x; 
}

long max(long x, long y) 
{ 
    std::cout << "Overloaded: "; 
    return x < y ? y : x; 
}

// struct dings
// {
//     dings(int i) : value(i) {}

//     int value;    
// };

// bool operator<(const dings& x, const dings& y)
// {
//     return x.value < y.value;
// }


int main (int argc, char* argv[]) 
{
    std::cout << max(8, 9) << '\n';
    std::cout << max(8.1, 9.3) << '\n';
    std::cout << max<float>(8.1, 9.3) << '\n';
    std::cout << max(8l, 9l) << '\n';

    // dings a(2), b(3);
    // max(a, b);

    return 0 ;
}
