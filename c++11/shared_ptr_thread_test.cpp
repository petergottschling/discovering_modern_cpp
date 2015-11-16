#include <iostream>
#include <memory>
#include "print_compiler.hpp"

struct X
{
    static int c;
    X() { std::cout << "X [" << ++c << "]  constructed at address " << this << std::endl; }
    ~X() { std::cout << "X [" << c-- << "] destructed at address " << this << std::endl; }
};

int X::c= 0;


std::shared_ptr<X> f()
{
    std::shared_ptr<X> p1= std::make_shared<X>();
    std::shared_ptr<X> p2= std::make_shared<X>(), p3= p1;
    std::cout << "End of f" << std::endl;
    return p3;
}

int main (int argc, char* argv[]) 
{
    print_compiler();
    
    X x;
    std::shared_ptr<X> p1= f();
    std::cout << "After f" << std::endl;
    std::shared_ptr<X> p2{new X};
    //p2+= 3;

    std::unique_ptr<X> p3{new X},
	               p4(new X);


    // std::shared_ptr<X> p3(new X), p4(new X);
    // p3= p4;
    // p4= p3;

    return 0;
}

