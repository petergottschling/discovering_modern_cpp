#include <iostream>

static double pi= 17.4;
// static double pi= 3.14159265358979323846264338327950288419716939;
// extern double pi;

static double square(double x) { return x*x; }

struct ss { ss(int i) : i(i) {} int i; };

const ss ss3(3);

void fix_pi();

void print_address();

template <typename T> void tprint(const T& x) { std::cout << x << '\n'; }
