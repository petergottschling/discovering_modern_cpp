#include <iostream>

class dings
{
  public:
    dings(int i) : i(i) {}
    dings(dings& that) : i(that.i) {}

    int i;
};

int main (int argc, char* argv[]) 
{
    dings a(3), b(a);
    const dings c(4);
    // dings d(c); // error only mutable copy constructor

    return 0 ;
}
