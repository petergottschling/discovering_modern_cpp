#ifndef GREATEST_BESTEST_SOLVER_INCLUDE
#define GREATEST_BESTEST_SOLVER_INCLUDE

#include "mesher.hpp"

struct system {};

system discretize(const mesh& m);

void solve(system& s);

#endif // GREATEST_BESTEST_SOLVER_INCLUDE
