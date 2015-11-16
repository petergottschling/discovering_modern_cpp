#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include "print_compiler.hpp"

using namespace std;

struct mat {};

struct parameters {};
struct solver
{
    solver(const mat& ref, const parameters& para) : ref(ref), para(para) {}
    solver(const solver&) = delete;
    solver(solver&&) = delete;

    const mat&        ref;
    const parameters& para; 
};

void solve_x(const solver& s)
{
    // s(x) ...
}

int main (int argc, char* argv[]) 
{
    print_compiler();

    mat A, B, C;
    parameters p1, p2;
    deque<solver> solvers;
    // solvers.push_back(solver(B, p1)); // would not compile
    solvers.emplace_back(B, p1);
    solvers.emplace_back(C, p2);
    solvers.emplace_front(A, p1);
    // solvers.insert(solvers.begin(), solver(A, p2));
    // solvers.erase(solvers.begin()); 

    for (auto& s : solvers)
	solve_x(s);


    return 0;
}

