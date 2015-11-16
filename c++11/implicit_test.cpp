#include <iostream>
#include <utility>
#include <vector>
#include <set>
#include <memory>
#include "print_compiler.hpp"

using namespace std;

struct copy_only // only C++11
{
    copy_only() = default;
    copy_only(const copy_only&) = default;
    copy_only(copy_only&&) = delete;
    copy_only& operator=(const copy_only&) = default;
    copy_only& operator=(copy_only&&) = delete;
    ~copy_only() = default;
};

struct move_only
{
    move_only() = default;
    move_only(const move_only&) = delete;
    move_only(move_only&&) = default;
    move_only& operator=(const move_only&) = delete;
    move_only& operator=(move_only&&) = default;
    ~move_only() = default;
    // ...
};



struct mutable_copy
{
    mutable_copy() = default;
    mutable_copy(mutable_copy& ) {}
    mutable_copy(mutable_copy&& ) = default;
    mutable_copy& operator=(const mutable_copy& ) = default;
    mutable_copy& operator=(mutable_copy&& ) = default;
    ~mutable_copy() = default;
};

class tray
{
  public:
    tray(unsigned s= 0) 
      : v(s)
      // , r(v[0]) 
      // , ci(3)
    {}
    // tray(const tray&) = default;
    // tray(tray&& that) : tray(that) {}
    // tray& operator=(const tray&) = default;
    // tray& operator=(tray&& that) { return *this= that; }
    // ~tray() = default;
    std::vector<float>  v;
    std::set<int>       s;
    // float&              r;
    // const int           ci;
    // move_only           mo;
    //mutable_copy     m;
    // copy_only        co;
    // std::unique_ptr<int> up;
};

void print(const tray& d, char name)
{
    if (d.v.size() == 0)
	cout << name << "'s vector is empty\n";
    else
	cout << name << "'s vector starts at " << std::hex << &d.v[0] << '\n';
}

struct no_default1
{
    no_default1(int) {}
};

struct no_default2
{
    no_default2(const no_default2&) = default;
};

struct default3
{
    ~default3() = default;
};

int main (int argc, char* argv[]) 
{
    print_compiler();

    tray a(5), b;
    print(a, 'a');

    tray c(a);
    print(a, 'a');
    print(c, 'c');

    tray d(std::move(a));
    print(a, 'a');
    // print(c, 'c');
    print(d, 'd');

    print(b, 'b');
    b= c;
    print(b, 'b');
    print(c, 'c');

    b= std::move(c);
    print(b, 'b');
    print(c, 'c');

    mutable_copy mc;

    //no_default1 nd1;
    //no_default2 nd2;
    default3 nd3;

    return 0;
}

