#ifndef ODE_SOLVER_RUNGE_KUTTA4_HPP
#define ODE_SOLVER_RUNGE_KUTTA4_HPP


#include "resize.hpp"
#include "algebra.hpp"
#include "operations.hpp"


namespace ode_solver {

template<class state_type, class value_type = double,
         class time_type = value_type,
         class algebra = container_algebra,
         class operations = default_operations>
class runge_kutta4 {
public:
    template<typename System>
    void do_step(System &system, state_type &x,
                     time_type t, time_type dt)
    {
        adjust_size( x );
        const value_type one = 1;
        const time_type dt2 = dt/2, dt3 = dt/3, dt6 = dt/6;

        typedef typename operations::template scale_sum2<
                    value_type, time_type> scale_sum2;

        typedef typename operations::template scale_sum5<
                    value_type, time_type, time_type,
                    time_type, time_type> scale_sum5;

        system(x, k1, t);
        m_algebra.for_each3(x_tmp, x, k1, scale_sum2(one, dt2));

        system(x_tmp, k2, t + dt2);
        m_algebra.for_each3(x_tmp, x, k2, scale_sum2(one, dt2));

        system(x_tmp, k3, t + dt2);
        m_algebra.for_each3(x_tmp, x, k3, scale_sum2(one, dt));

        system(x_tmp, k4, t + dt);
        m_algebra.for_each6(x, x, k1, k2, k3, k4,
                            scale_sum5(one, dt6, dt3,
                                       dt3, dt6));
    }
private:
    state_type x_tmp, k1, k2, k3, k4;
    algebra m_algebra;

    void adjust_size(const state_type &x) {
        resize(x, x_tmp);
        resize(x, k1); resize(x, k2);
        resize(x, k3); resize(x, k4);
    }
};

}

#endif
