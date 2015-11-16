#ifndef ODE_SOLVER_ALGEBRA_HPP
#define ODE_SOLVER_ALGEBRA_HPP


#include <iterator>

namespace ode_solver {

struct container_algebra 
{
    template<class S1, class S2,
             class S3, class Op>
    void for_each3(S1 &s1, S2 &s2,
                   S3 &s3, Op op) const
    {
        using std::begin;
        using std::end;

        auto first1 = begin(s1);
        auto last1 = end(s1);
        auto first2 = begin(s2);
        auto first3 = begin(s3);
        for( ; first1 != last1 ; )
            op(*first1++, *first2++,
               *first3++);
    }



    template<class S1, class S2,
             class S3, class S4,
             class S5, class S6,
             class Op>
    void for_each6(S1 &s1, S2 &s2,
                   S3 &s3, S4 &s4,
                   S5 &s5, S6 &s6, Op op) const
    {
        using std::begin;
        using std::end;

        auto first1 = begin(s1);
        auto last1 = end(s1);
        auto first2 = begin(s2);
        auto first3 = begin(s3);
        auto first4 = begin(s4);
        auto first5 = begin(s5);
        auto first6 = begin(s6);
        for( ; first1 != last1 ; )
            op(*first1++, *first2++,
               *first3++, *first4++,
               *first5++, *first6++);
    }
};

}

#endif
