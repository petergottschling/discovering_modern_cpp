#include <iostream>
#include "print_compiler.hpp"

using namespace std;

class tray
{
  public:
    tray() = default;
    tray(const tray&) = default; // considered user-defined
    // tray& operator=(const tray&) = default; // unwillingly
    // ...
    ~tray() = default;
};


int main (int argc, char* argv[]) 
{
    print_compiler();
    tray t1, t2(t1);
    t1= t2;

    return 0;
}

