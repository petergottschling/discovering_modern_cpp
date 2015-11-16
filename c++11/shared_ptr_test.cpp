#include <iostream>
#include <memory>
#include "print_compiler.hpp"

using namespace std;

struct X
{
    static int c;
    // X() { cout << "X [" << ++c << "]  constructed at address " << this << endl; }
    // ~X() { cout << "X [" << c-- << "] destructed at address " << this << endl; }
    int i= 3;
};

int X::c= 0;


shared_ptr<double> f()
{
    // shared_ptr<double> p1{new double}; // make_shared<double>();
    auto p1= make_shared<double>();
    shared_ptr<double> p2{new double}, p3= p1;
    cout << "p3.use_count() = " << p3.use_count() << endl;
    return p3;
}

// shared_ptr<X> f()
// {
//     shared_ptr<X> p1= make_shared<X>();
//     shared_ptr<X> p2= make_shared<X>(), p3= p1;
//     cout << "p3.use_count() = " << p3.use_count() << endl;
//     cout << "End of f" << endl;
//     return p3;
// }

int main () 
{
    print_compiler();
    
    X x;
    shared_ptr<double> p1= f();
    cout << "p1.use_count() = " << p1.use_count() << endl;
    
    shared_ptr<X> p2(new X);
    
    cout << "@p2 = " << p2 << endl;

    // shared_ptr<X> p3(new X), p4(new X);
    // p3= p4;
    // p4= p3;

    // X* px= new X;
    // shared_ptr<X> p5{px}, p6{px};

    



    // cout << "@px = " << px << endl;
    // cout << "@p5 = " << p5 << ", uc = " << p5.use_count() << endl;
    // cout << "@p6 = " << p6 << ", uc = " << p6.use_count() << endl;
    
    // p5->i= 7;
    // cout << "p5->i = " << p5->i << endl;
    // cout << "p6->i = " << p6->i << endl;
    // cout << "@p5 = " << p5 << ", uc = " << p5.use_count() << endl;
    // cout << "@p6 = " << p6 << ", uc = " << p6.use_count() << endl;

    // p5.reset();
    // cout << "@p5 = " << p5 << ", uc = " << p5.use_count() << endl;
    // cout << "@p6 = " << p6 << ", uc = " << p6.use_count() << endl;
    // // cout << "p5->i = " << p5->i << endl;
    // cout << "p6->i = " << p6->i << endl;

    return 0;
}

