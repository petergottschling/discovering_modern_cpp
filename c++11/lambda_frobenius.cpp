// Filename: lambda_frobenius.cpp 
#include <cassert>
#include <iostream>
#include <cmath>

class matrix 
{
  public:
    typedef double value_type;

    matrix() : nrows(0), ncols(0), data(0) {}
    matrix(int nrows, int ncols) 
      : nrows(nrows), ncols(ncols), data( new double[nrows * ncols] ) {}

    matrix(const matrix& that) 
      : nrows(that.nrows), ncols(that.ncols), data(new double[nrows * ncols])
    {
	for (int i= 0, size= nrows*ncols; i < size; ++i)
	    data[i]= that.data[i];
    }

    ~matrix() { if(data) delete [] data; }

    void operator=(const matrix& that) 
    {
	assert(nrows == that.nrows && ncols == that.ncols);
	for (int i= 0, size= nrows*ncols; i < size; ++i)
	    data[i]= that.data[i]; 
    }

    int num_rows() const { return nrows; }
    int num_cols() const { return ncols; }

  private:
    void check(int r, int c) const { assert(0 <= r && r < nrows && 0 <= c && c <= ncols); }
  public:
    double& operator()(int r, int c) 
    { 
	check(r, c); 
	return data[r*ncols + c]; 
    }
    const double& operator()(int r, int c) const 
    { 
	check(r, c); 
	return data[r*ncols + c]; 
    }

  private:
    int     nrows, ncols;
    double* data;
};

std::ostream& operator<<(std::ostream& os, const matrix& A)
{
    for (int r= 0; r < A.num_rows(); r++) {
	os << '[';
	for (int i= 0; i < A.num_cols(); ++i) 
	    os << A(r, i) << (i+1 < A.num_cols() ? "  " : "");
	os << "]\n";
    }
    return os;
}

template <typename Functor>
void on_each_nonzero(const matrix& A, Functor f)
{
    for (int r= 0; r < A.num_rows(); r++) 
	for (int c= 0; c < A.num_cols(); ++c) 
	    f(A(r, c));
}

// template <typename Matrix>
// inline auto frobenius_norm(const Matrix& A) 
//     -> decltype(std::abs(A(0,0)))  wrong when abs not std::abs
// {
//     using std::abs;
//     typedef typename Matrix::value_type value_type;
//     value_type ss(0);
//     on_each_nonzero(A, [&ss](value_type x) { ss+= abs(x) * abs(x); });
//     return std::sqrt(ss);
// }

template <typename Matrix>
typename Matrix::value_type
inline frobenius_norm(const Matrix& A) 
{
    using std::abs;
    typedef typename Matrix::value_type value_type;
    value_type ss(0);
    on_each_nonzero(A, [&ss](value_type x) { ss+= abs(x) * abs(x); });
    return std::sqrt(ss);
}

int main() 
{
    matrix A(2, 2);
    A(0, 0)= 4.0; A(1, 1)= 2.0; A(0, 1)= 3.0; A(1, 0)= -1.0;

    std::cout << "A is \n" << A << '\n';
    std::cout << "Frobenius norm of A is " << frobenius_norm(A) << '\n';

    return 0;
}
