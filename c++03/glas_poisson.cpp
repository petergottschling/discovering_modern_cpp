//#include <glas/toolbox/la/la.hpp>
#include <glas/toolbox/kronecker/kronecker.hpp>
#include <glas/toolbox/iterative/iterative.hpp>
#include <glas/glas.hpp>

typedef glas::dense_matrix<double> m_type;
typedef glas::dense_vector<double> v_type;

template <typename LS, typename EV>
double inverse_iteration( LS const& solver, EV& x, int m)
{
  glas::dense_vector<double> y(size(x));
  double lambda;
  x /= norm2(x);
  for (int i= 0; i < m; i++) {
    solver(x, y);
    lambda = sum(x) / sum(y);
    x = y / norm_2(y);
  }
  return lambda;
}

// BinaryFunction poisson_cg
struct poisson_cg {
  template <typename RHS, typename Sol>
  void operator() (const RHS& rhs, Sol& sol) const
  {
    glas::options opt; opt.tolerance_ = 1.e-4; opt.max_mat_vec_ = 100;
    glas::no_report rep;
    poisson_matvec_with_vectors matvec;
    glas::iterative::cg( matvec, sol, rhs, rep, opt);
  }

};


struct poisson_matvec
{  
  void operator() (const m_type& u, m_type& f)
  {
    for (int r= 0; r < num_rows(u); r++)
      for (int c= 0; c < num_columns(u); c++) {
	f(r, c)= 4 * u(r, c);
	if (r > 0) f(r, c)-= u(r-1, c);
	if (r < num_rows(u)-1) f(r, c)-= u(r+1, c);
	if (c > 0) f(r, c)-= u(r, c-1);
	if (c < num_columns(u)-1) f(r, c)-= u(r, c+1);
      }
  }
};

struct poisson_matvec_with_vectors
{
  template <typename X, typename Y>
  void operator() (const X& x, Y& y)
  {
    m_type x
  }
};

int main()
{
  m_type u(10, 10), f(10, 10);

  u= 0.0;
  u(1, 1) = 1.0 ;
  
  v_type eigenvector(n);
  glas::random(eigenvector, seed);

  poisson_matvec()(u, f);
  return 0;
}
