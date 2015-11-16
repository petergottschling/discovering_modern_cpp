#include <iostream>
#include <string>

class a
{
  public:
     int f() { return 3;}
};

class b
  : public a
{
  public:
     float f() { return 4; }
    // virtual std::string f() { return "xxx3xxx"; }
};


int main (int argc, char* argv[]) 
{
    a aa;
    b bb;

    std::cout << "aa.f() = " << aa.f() << '\n';
    std::cout << "bb.f() = " << bb.f() << '\n';

    a& ar= bb;
    std::cout << "ar.f() = " << ar.f() << '\n';
    

    return 0 ;
}
