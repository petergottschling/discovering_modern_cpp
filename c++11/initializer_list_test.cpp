#include <initializer_list>
#include <iostream>
#include <string>
#include <array>
#include "print_compiler.hpp"

struct S {
    int x;
    struct Foo {
        int i;
        int j;
        int a[3];
    } b;
};

struct dings
{
    int i;
    double d;
};

class MyClass{
  public:
    int x;
    double y;
};

class MyClass2{
  public:
    MyClass2(int fir, float sec) : x{fir}, y{static_cast<float>(sec)} {std::cout << "#1\n";};
    MyClass2(std::initializer_list<double> values) : x(*values.begin()), y(*(values.begin()+1)) {std::cout << "#2\n";}
    // MyClass2(int fir, float sec) : x(fir), y(sec) {};
    // MyClass2(int fir, float sec):fir{a},sec{b} {};
  private:
    int x;
    float y;
};

class MyClass3{
  public:
    MyClass3(double fir, double sec) : x{int(fir)}, y{int(sec)} {std::cout << "3#1\n";};
    MyClass3(std::initializer_list<int> values) : x(*values.begin()), y(*(values.begin()+1)) {std::cout << "3#2\n";}
    // MyClass3(std::initializer_list<int*> values) : x(**values.begin()), y(**(values.begin()+1)) {std::cout << "3#2\n";}
  private:
    int x;
    int y;
};

struct BCD {
    BCD(int val);
};
void f(char) { std::cout << "f(char)\n"; }  // (1) (assume 8-bit char)
void f(BCD)  { std::cout << "f(BCD)\n"; }// (2)

struct X {
    explicit X(int) { std::cout << "X(int)\n"; } // (1)
    X(double) { std::cout << "X(double)\n"; } // (2)
};

struct sloppy_complex
{
    double r, i;
};

int main (int argc, char* argv[]) 
{
    print_compiler();

    // int i1n= {3.14}; // narrowing error, fractional part not representable
    int i1= 3.14;    // compiles despite narrowing, runs at our risk
    int i2= {3};
    // long l= {1234567890123};
    long l2= 1234567890123;
    int il2= 0x1234567890;
    std::cout << "l2 is " << std::hex << il2 << '\n';
    // unsigned u1= {3.14}; // narrowing error, fractional part not representable
    // unsigned u2= {-3};   // narrowing error, negative values not representable
    unsigned u2b= -3;    // compiles despite narrowing, runs at our risk
    unsigned u3= {3}; 
    // unsigned u4= {i2};   // narrowing error, negative values not representable
    // int i3= {u3};        // narrowing error, large values not representable

    // std::cout << "i1b = " << i1b << '\n';

    dings dd{2, 7.3};
    std::cout << "dd is " << dd.i << "," << dd.d << std::endl;

    MyClass class0{2011,3.14}; // {} - Initializer List
    MyClass class1= {2011,3.14}; // {} - Initializer List

    MyClass2 class2{2011,float(3.14)}; // {} - Initializer List
    MyClass2 class3= {2011,3.14f}; // {} - Initializer List

    // MyClass3 class4{2011.4, 3.14}; // {} - Initializer List
    // MyClass3 class5= {2011.0, 3.14f}; // {} - Initializer List

    S s1 = { 1, { 2, 3, {4, 5, 6} } };
    // S s2 = { 1, 2, 3, 4, 5, 6}; // same, but with brace elision; warning in clang++
    S s3{1, {2, 3, {4, 5, 6} } }; // same, using direct-list-initialization syntax
    // S s4{ 1, 2, 3, 4, 5, 6}; // same, but with brace elision; warning in clang++

    // int ai[] = { 1, 2.0 }; // narrowing conversion from double to int:
    //                        // error in C++11, okay in C++03


    std::array<int, 3> std_ar2{ {1,2,3} };    // std::array is an aggregate
    std::array<int, 3> std_ar1= {1, 2, 3}; // brace-elision okay

    int ar2d1[2][2] = {{1, 2}, {3, 4}}; // fully-braced 2D array: {1, 2}
                                        //                        {3, 4}
    int ar2d2[2][2] = {1, 2, 3, 4}; // brace elision: {1, 2}
                                    //                {3, 4}; warning in clang++
    int ar2d3[2][2] = {{1}, {2}};   // only first column: {1, 0}
                                    //                    {2, 0}

    std::string a{"hello world"}; // OK
    std::string b{a};  // NOT OK

    // f({1000}); // Would call (2)

    X x1(10); // Calls (1).
    X x2 = 10; // Calls (2).
 
    X x1i{10}; // Calls (1).
    //X x2i = {10}; // Tries (1) and fails

    sloppy_complex z1{3.66, 2.33},
	           z2= {0, 1};
    


    return 0 ;
}
