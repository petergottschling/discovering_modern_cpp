// Filename: matrix_crtp_example.cpp
#include <cassert>
#include <iostream>

using std::size_t;

#define WITH_DOUBLE_INDEX

#if 0
class some_matrix; // Forward declaration

class simple_bracket_proxy
{
  public:
    simple_bracket_proxy(matrix& A, size_t r) : A(A), r(r) {}
    
    double& operator[](size_t c){ return A(r, c); }
  private:
    matrix& A;
    size_t     r;
};
#endif


template <typename Matrix, typename Result>
class bracket_proxy
{
  public:
    bracket_proxy(Matrix& A, size_t r) : A(A), r(r) {}
    
    Result& operator[](size_t c){ return A(r, c); }
  private:
    Matrix& A;
    size_t     r;
};

template <typename Matrix, typename Result>
class crtp_matrix
{
    using const_proxy= bracket_proxy<const Matrix, const Result>;
  public:
    bracket_proxy<Matrix, Result> operator[](size_t r) 
    { 
	return {static_cast<Matrix&>(*this), r}; 
    }

    const_proxy operator[](size_t r) const
    { 
	return {static_cast<const Matrix&>(*this), r}; 
    }

    bool operator!=(const Matrix& B) const 
    {
	return !(static_cast<const Matrix&>(*this) == B);
    }

    Matrix operator+(const Matrix& B) const
    {
	Matrix tmp(static_cast<const Matrix&>(*this));
	tmp+= B;
	return tmp;
    }

    Matrix clone() const { return static_cast<const Matrix&>(*this); }
};

class some_matrix 
  : public crtp_matrix<some_matrix, double>
{
  public:
    some_matrix() : nrows(0), ncols(0), data(0) {}

    some_matrix(size_t nrows, size_t ncols) 
      : nrows(nrows), ncols(ncols), data( new double[nrows * ncols] ) {}

    some_matrix(const some_matrix& that) 
      : nrows(that.nrows), ncols(that.ncols), data(new double[nrows * ncols])
    {
	for (size_t i= 0, size= nrows*ncols; i < size; ++i)
	    data[i]= that.data[i];
    }

    ~some_matrix() { if(data) delete [] data; }

    void operator=(const some_matrix& that) 
    {
	assert(nrows == that.nrows && ncols == that.ncols);
	for (size_t i= 0, size= nrows*ncols; i < size; ++i)
	    data[i]= that.data[i]; 
    }

    size_t num_rows() const { return nrows; }
    size_t num_cols() const { return ncols; }

  private:
    void check(size_t r, size_t c) const { assert(r < nrows && c <= ncols); }
  public:
    double& operator()(size_t r, size_t c) 
    { 
	check(r, c); 
	return data[r*ncols + c]; 
    }
    const double& operator()(size_t r, size_t c) const 
    { 
	check(r, c); 
	return data[r*ncols + c]; 
    }

    bool operator==(const some_matrix& ) const { return false; }

#if 0
    simple_bracket_proxy operator[](size_t r) 
    {
	return simple_bracket_proxy(*this, r);
    }
#endif

#if 0
    bracket_proxy<some_matrix, double> operator[](size_t r) 
    { 
	return bracket_proxy<some_matrix, double>(*this, r); 
    }
#endif

  private:
    size_t     nrows, ncols;
    double* data;
};

std::ostream& operator<<(std::ostream& os, const some_matrix& A)
{
    for (size_t r= 0; r < A.num_rows(); r++) {
	os << '[';
	for (size_t i= 0; i < A.num_cols(); ++i) 
	    os << A(r, i) << (i+1 < A.num_cols() ? "  " : "");
	os << "]\n";
    }
    return os;
}



int main() 
{
    some_matrix A(2, 2);
    A(0, 0)= 4.0; A(1, 1)= 2.0; A(0, 1)= 3.0; A(1, 0)= -1.0;

    std::cout << "A is \n" << A << '\n';

    std::cout << "A[0][1] is " << A[0][1] << '\n';

#if 1
    const some_matrix B(A);
    std::cout << "B[0][1] is " << B[0][1] << '\n';
#endif
    return 0;
}
