#include <iostream>
#include <map>
#include <string>
#include <memory>
#include <deque>
#include <vector>
#include <functional>

#include <boost/numeric/mtl/mtl.hpp>

#include "print_compiler.hpp"

using namespace std;
using namespace mtl;

using Mat= matrix<double>;
using Vec= mtl::vector<double>;
using Linear= function<Vec(const Vec&)>;

struct named_linear
{
    void insert(const string& name, const Linear& op) {
	ops[name]= op; }
    void insert(const string& name, Linear&& op) {
	ops[name]= move(op); }
    Vec apply(const string& name, const Vec& x) {
	return ops[name](x); }

    map<string, Linear> ops;
};

deque<Linear> d;

void insert_hilbert(named_linear& nl)
{
    auto F= make_unique<Mat>(Mat{{1., 0.5},{0.5,1./3.}});
    // nl.insert("hilbert", [&F](const Vec& x){ return Vec(*F * x); });
    // nl.insert("hilbert", [F](const Vec& x){ return Vec(*F * x); });
    // nl.insert("hilbert", [F= move(F)](const Vec& x){ return Vec(*F * x); });
    // nl.ops["hilbert"]= move([F= move(F)](const Vec& x){ return Vec(*F * x); });
    // nl.ops.emplace("hilbert", [F= move(F)](const Vec& x){ return Vec(*F * x); });
    // d.emplace_back([F{ move(F) }](const Vec& x) { return Vec(*F * x); });
    auto func= [F= move(F)](const Vec& x){ return Vec(*F * x); };
    // nl.ops.emplace("hilbert", move(func));
    //nl.insert("hilbert", move(func));
}

struct dings
{
    dings() = default;
    dings(const dings&) = delete;
    dings(dings&&) = default;
    dings& operator=(const dings&) = delete;
    dings& operator=(dings&&) = default;

    // unique_ptr<int> p;
};

struct evil
{
    evil() = default;
    evil(int) {}
    evil(const evil&) = delete;
    evil(evil&&) = delete;
    evil& operator=(const evil&) = delete;
    evil& operator=(evil&&) = delete;
};

// struct foo { unique_ptr<int> p; };

int main (int argc, char* argv[]) 
{
    print_compiler();

    Mat A= {{2, 3}, {4, 5}};
    Mat I= {{1, 0}, {0, 1}};

    named_linear nl;
    nl.insert("scale", [&A](const Vec& x){ return Vec(A * x); });
    nl.insert("trans" , [&A](const Vec& x){ return Vec(trans(A) * x); });
    nl.insert("identity" , [&I](const Vec& x){ return Vec(I * x); });

    Vec x= {3, 4};
    // cout << "identity(x) = " << nl.apply("identity", x) << "\n";
    // cout << "trans(x) = " << nl.apply("trans", x) << "\n";
    // cout << "hilbert(x) = " << nl.apply("hilbert", x) << "\n";

    dings bums;
    deque<dings> dd;
    dd.push_back(move(bums));
    dd.push_back(dings());
    dd.emplace_back(dings());

    map<string, dings> dm;
    dm.emplace("hallo", dings());
    dm["huhu"]= dings();
 
    nl.insert("test1", [&bums](const Vec& x){ return x; });
    // nl.insert("test2", [b= move(bums)](const Vec& x){ return x; });

    auto up= make_unique<int>(3);
    std::vector<function<int(int)>> v;
    v.push_back([&up](int i){return i;});
    // v.push_back([up= move(up)](int i){return i;});

    deque<function<int(int)>> di;
    // di.emplace_back([up= move(up)](int i){return i;});

    deque<evil> de;
    de.emplace_back();
    de.emplace_back(7);

    struct foo { unique_ptr<int> p; };
    std::vector<foo> v2;
    v2.push_back(foo{});
    
    { // to avoid redeclaration of x
    int x= 4;
    auto y= 
        [&r= x, x= x + 1]()
        {
            r+= 2;          // increment r, a reference to outer x
            return x + 2;   // return x + 2 where x is the outer x + 1
        }();  // Updates ::x to 6, and initializes y to 7.
    cout << "x = " << x << ", y = " << y << endl;
    }

    return 0;
}
