#include <iostream>
#include <vector>

#include "runge_kutta4.hpp"

using ode_solver::runge_kutta4;

typedef std::vector<double> state_type;
typedef runge_kutta4< state_type > rk4_type;

struct lorenz {
    const double sigma, R, b;
    lorenz(const double sigma, const double R, const double b)
        : sigma(sigma), R(R), b(b) { }

    void operator()(const state_type &x,state_type &dxdt,
                    double t)
    {
        dxdt[0] = sigma * ( x[1] - x[0] );
        dxdt[1] = R * x[0] - x[1] - x[0] * x[2];
        dxdt[2] = -b * x[2] + x[0] * x[1];
    }
};


int main() {
    const int steps = 5000;
    const double dt = 0.01;

    rk4_type stepper;
    lorenz system(10.0, 28.0, 8.0/3.0);
    state_type x(3, 1.0);
    x[0] = 10.0;  // some initial condition
    for( size_t n=0 ; n<steps ; ++n ) {
        stepper.do_step(system, x, n*dt, dt);
        std::cout << n*dt << ' '; 
        std::cout << x[0] << ' ' << x[1] << ' ' << x[2]
                  << std::endl;
    }
}
