#include <iostream>



int main (int argc, char* argv[]) 
{
    int i= 3;
    const int* const ip= &i;

    double d= 3.0;
    double const* const dp= &d;

    typedef const double* double_pointer;
    // dp= double_pointer(ip);
    // dp= static_cast<double_pointer>(ip);
    // dp= double_pointer{ip};

    std::cout << "i = " << i << std::endl;


    double d2;
    // d= double{i};
    d2= static_cast<double>(i);

    long l;
    l= long(dp);
    l= (long) dp;
    l= static_cast<long>(dp);
    // l= long{dp};
    

    return 0 ;
}
