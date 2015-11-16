#include <iostream>
#include <typeinfo>
#include <string>
#include <type_traits>

#include "print_compiler.hpp"
#include "../my_info.hpp"

using namespace std;

template <typename T>
string l_or_r(const T&) { return "const lvalue"; }

template <typename T>
string l_or_r(T&) { return "lvalue"; }

template <typename T>
string l_or_r(T&&) { return "rvalue"; }

// Evil hack for testing
#define info(VV) \
    cout << #VV << ": type is " << my_info<decltype(VV)>() << endl;

    // cout << #VV << ": lref = " << boolalpha << is_lvalue_reference<decltype(VV)>::value 
    // 	 << ", rref = " << is_rvalue_reference<decltype(VV)>::value << ", " << l_or_r(VV) << endl


int main (int argc, char* argv[]) 
{
    print_compiler();

    int        i= 3;              
    int&       ri= i;             
    const int& cri= i;            

    auto a1= i;                   
    decltype(auto) d1= i;         
    auto a2= ri;                  
    decltype(auto) d2= ri;        
    auto a3= cri;                 
    decltype(auto) d3= cri;       
    auto& a4= i;                  
    decltype(i)& d4= i;
    auto& a5= ri;                    // int&
    auto& a6= cri;                   // const int&

    auto&& a7= i;
    auto&& a8= ri;
    auto&& a9= cri;
    auto&& a10= 33;
    auto&& a11= move(i);
    
#if 0
    cout << "i = " << i << "\n";
    a2= 4;
    cout << "i = " << i << "\n";
    d2= 5;
    cout << "i = " << i << "\n";
    a3= 6;
    cout << "i = " << i << "\n";
    // d3= 7;
    // cout << "i = " << i << "\n";

    a4= 8;
    cout << "i = " << i << "\n";
    d4= 9;
    cout << "i = " << i << "\n";

    a5= 10;
    cout << "i = " << i << "\n";
    // a6= 12;
    // cout << "i = " << i << "\n";

    a7= 13;
    cout << "i = " << i << "\n";
    a8= 14;
    cout << "i = " << i << "\n";
    // a9= 15;
    // cout << "i = " << i << "\n";
    a10= 16;
    a11= 17;
    cout << "i = " << i << "\n";
#endif

    info(a1);
    info(a2);
    info(a3);
    info(a4);
    info(a5);
    info(a6);
    info(a7);
    info(a8);
    info(a9);
    info(a10);
    info(a11);
    info(d1);
    info(d2);
    info(d3);
    info(d4);

    // cout << "lref = " << boolalpha << is_lvalue_reference<decltype(a11)>::value
    // 	 << ", rref = " << is_rvalue_reference<decltype(a11)>::value << ", " << l_or_r(a11) << endl;

    return 0;
}
