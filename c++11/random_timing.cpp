#include <iostream>
#include <chrono>
#include <random>
#include "print_compiler.hpp"

using namespace std;
using namespace std::chrono;

template <typename T>
void measure(T& rng)
{
    const int rep= 1000000;

    int vrng{};
    auto t1= system_clock::now();
    for (int i= 0; i < rep; i++)
	vrng+= rng();
    auto t2= system_clock::now();
    std::cout << "milliseconds: " << duration_cast<milliseconds>(t2-t1).count()
	      << " " << vrng << endl;
}


int main () 
{
    print_compiler();

    default_random_engine re;
    random_device         rd;

    measure(re);
    measure(rd);

    // cout << duration_cast<nanoseconds>(system_clock::duration()).count() << endl;

    return 0;
}

