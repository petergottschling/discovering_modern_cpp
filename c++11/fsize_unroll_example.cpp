#include <cassert>
#include <iostream>
#include <cmath>
#include <boost/static_assert.hpp>

template <int N>
struct fsize_assign
{
    template <typename Target, typename Source>
    void operator()(Target& tar, const Source& src)
    {
	fsize_assign<N-1>()(tar, src);
	std::cout << "assign entry " << N << '\n';
	tar[N]= src[N];
    }
};
 
template <>
struct fsize_assign<0>
{
    template <typename Target, typename Source>
    void operator()(Target& tar, const Source& src)
    {
	std::cout << "assign entry " << 0 << '\n';
	tar[0]= src[0];
    }
};

template <typename Matrix, typename Vector>
struct mat_vec_et
{
    const static int     my_rows= Matrix::my_rows, my_cols= Matrix::my_cols;
    // check consistency with Vector!

    mat_vec_et(const Matrix& A, const Vector& v) : A(A), v(v) {}

    const Matrix& A;
    const Vector& v;
};

template <int Rows, int Cols>
struct fsize_mat_vec_mult
{
    template <typename Matrix, typename VecIn, typename VecOut>
    void operator()(const Matrix& A, const VecIn& v_in, VecOut& v_out)
    {
	fsize_mat_vec_mult<Rows, Cols-1>()(A, v_in, v_out);
	v_out[Rows]+= A[Rows][Cols] * v_in[Cols];
    }
};

template <int Rows>
struct fsize_mat_vec_mult<Rows, 0>
{
    template <typename Matrix, typename VecIn, typename VecOut>
    void operator()(const Matrix& A, const VecIn& v_in, VecOut& v_out)
    {
	fsize_mat_vec_mult<Rows-1, Matrix::my_cols-1>()(A, v_in, v_out);
	v_out[Rows]= A[Rows][0] * v_in[0];
    }
};

template <>
struct fsize_mat_vec_mult<0, 0>
{
    template <typename Matrix, typename VecIn, typename VecOut>
    void operator()(const Matrix& A, const VecIn& v_in, VecOut& v_out)
    {
	v_out[0]= A[0][0] * v_in[0];
    }
};


template <int Rows, int Cols>
struct fsize_mat_vec_mult_cm
{
    template <typename Matrix, typename VecIn, typename VecOut>
    void operator()(const Matrix& A, const VecIn& v_in, VecOut& v_out)
    {
	fsize_mat_vec_mult_cm<Rows-1, Cols>()(A, v_in, v_out);
	v_out[Rows]+= A[Rows][Cols] * v_in[Cols];
    }
};

template <int Cols>
struct fsize_mat_vec_mult_cm<0, Cols>
{
    template <typename Matrix, typename VecIn, typename VecOut>
    void operator()(const Matrix& A, const VecIn& v_in, VecOut& v_out)
    {
	fsize_mat_vec_mult_cm<Matrix::my_rows-1, Cols-1>()(A, v_in, v_out);
	v_out[0]+= A[0][Cols] * v_in[Cols];
    }
};

template <int Rows>
struct fsize_mat_vec_mult_cm<Rows, 0>
{
    template <typename Matrix, typename VecIn, typename VecOut>
    void operator()(const Matrix& A, const VecIn& v_in, VecOut& v_out)
    {
	fsize_mat_vec_mult_cm<Rows-1, 0>()(A, v_in, v_out);
	v_out[Rows]= A[Rows][0] * v_in[0];
    }
};

template <>
struct fsize_mat_vec_mult_cm<0, 0>
  : fsize_mat_vec_mult<0, 0> {};




template <int Rows, int Cols>
struct fsize_mat_vec_mult_aux
{
    template <typename Matrix, typename VecIn, typename ScalOut>
    void operator()(const Matrix& A, const VecIn& v_in, ScalOut& tmp)
    {
	fsize_mat_vec_mult_aux<Rows, Cols-1>()(A, v_in, tmp);
	tmp+= A[Rows][Cols] * v_in[Cols];
    }
};

template <int Rows>
struct fsize_mat_vec_mult_aux<Rows, 0>
{
    template <typename Matrix, typename VecIn, typename ScalOut>
    void operator()(const Matrix& A, const VecIn& v_in, ScalOut& tmp)
    {
	tmp= A[Rows][0] * v_in[0];
    }
};


template <int Rows, int Cols>
struct fsize_mat_vec_mult_reg
{
    template <typename Matrix, typename VecIn, typename VecOut>
    void operator()(const Matrix& A, const VecIn& v_in, VecOut& v_out)
    {
	fsize_mat_vec_mult_reg<Rows-1, Cols>()(A, v_in, v_out);

	typename VecOut::value_type tmp;
	fsize_mat_vec_mult_aux<Rows, Cols>()(A, v_in, tmp);
	v_out[Rows]= tmp;
    }
};

template <int Cols>
struct fsize_mat_vec_mult_reg<0, Cols>
{
    template <typename Matrix, typename VecIn, typename VecOut>
    void operator()(const Matrix& A, const VecIn& v_in, VecOut& v_out)
    {
	typename VecOut::value_type tmp;
	fsize_mat_vec_mult_aux<0, Cols>()(A, v_in, tmp);
	v_out[0]= tmp;
    }
};



template <typename T, int Size>
class fsize_vector 
{
    typedef fsize_vector self;
    void check_index(int i) const { assert(i >= 0 && i < my_size); }

  public:  
    typedef T            value_type;
    BOOST_STATIC_ASSERT((Size > 0));
    const static int     my_size= Size;

    fsize_vector() {}

    fsize_vector( const self& that )
    {
	for (int i= 0; i < my_size; ++i)
	    data[i]= that.data[i];
    }


    self& operator=( const self& that ) 
    {
	fsize_assign<my_size-1>()(*this, that);
	return *this;
    }

    template <typename Vector>
    self& operator=( const Vector& that ) 
    {
	fsize_assign<my_size-1>()(*this, that);
	return *this;
    }

    template <typename Matrix, typename Vector>
    self& operator=( const mat_vec_et<Matrix, Vector>& that ) 
    {
	typedef mat_vec_et<Matrix, Vector> et;
	fsize_mat_vec_mult_reg<et::my_rows-1, et::my_cols-1>()(that.A, that.v, *this);
	return *this;
    }

    int size() const { return my_size ; }

    const T& operator[]( int i ) const 
    {
	check_index(i);
	return data[i];
    }
		     
    T& operator[]( int i ) 
    {
	check_index(i);
	return data[i] ;
    }

    self operator+( const self& that ) const 
    {
	self sum;
	for (int i= 0; i < my_size; ++i) 
	    sum[i]= data[i] + that[i];
	return sum ;
    }
  private:
    T     data[Size] ;
};

template <typename T, int Rows, int Cols>
class fsize_matrix 
{
    typedef fsize_matrix self;
  public:  
    typedef T            value_type;
    BOOST_STATIC_ASSERT((Rows * Cols > 0));
    const static int     my_rows= Rows, my_cols= Cols;

    fsize_matrix() 
    {
	for (int i= 0; i < my_rows; ++i)
	    for (int j= 0; j < my_cols; ++j)
		data[i][j]= T(0);
    }

    fsize_matrix( const self& that )
    {
	for (int i= 0; i < my_rows; ++i)
	    for (int j= 0; j < my_cols; ++j)
		data[i][j]= that.data[i][j];
    }

    // cannot check column index
    const T* operator[](int r) const { return data[r]; }
    T* operator[](int r) { return data[r]; }

    mat_vec_et<self, fsize_vector<T, Cols> > operator*(const fsize_vector<T, Cols>& v) const 
    { 
	return mat_vec_et<self, fsize_vector<T, Cols> > (*this, v); 
    }

  private:
    T     data[Rows][Cols];
};




template <typename T, int Size>
std::ostream& operator<<(std::ostream& os, const fsize_vector<T, Size>& v)
{
  os << '[';
  for (int i= 0; i < v.size(); ++i) os << v[i] << ',';
  os << ']';
  return os ;
}


template <typename Vector>
typename Vector::value_type
inline one_norm(const Vector& v)
{
  using std::abs;
  typename Vector::value_type s= 0;
  for (int i= 0; i < v.size(); ++i)
    s+= abs(v[i]);
  return s;
}



int main() 
{
    
    fsize_vector<float, 4> v, w;
    v[0]= v[1]= 1.0; v[2]= 2.0; v[3]= -3.0;
    w= v;

    fsize_matrix<float, 4, 4> A;
    A[0][1]= 2.3; A[1][2]= 3.4; A[2][3]= 4.1; A[3][0]= 5.; 

    w= A * v;
    std::cout << "A * v = " << w << '\n';

    return 0 ;
}
