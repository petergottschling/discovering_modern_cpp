#ifndef ODE_SOLVER_RESIZE_HPP
#define ODE_SOLVER_RESIZE_HPP

#include <vector>
#include <array>

namespace ode_solver {

template<class state_type>
void resize(const state_type &in, state_type &out) {
  // standard implementation works for containers
  out.resize(in.size());
}

// specialization for std::array
template<class T, std::size_t N>
void resize(const std::array<T, N> &, std::array<T,N>& ) {
  /* arrays don't need resizing */
}

}

#endif
