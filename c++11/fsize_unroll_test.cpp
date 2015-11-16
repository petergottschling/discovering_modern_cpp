#include <cassert>
#include <iostream>
#include <cmath>


template <typename Target, typename Source, int N>
struct fsize_assign
{
    void operator()(Target& tar, const Source& src)
    {
	fsize_assign<Target, Source, N-1>()(tar, src);
	std::cout << "tar[" << N << "]= src[" << N << "]\n";
	tar[N]= src[N];
    }

};

template <typename Target, typename Source>
struct fsize_assign<Target, Source, 0>
{
    void operator()(Target& tar, const Source& src)
    {
	std::cout << "tar[0]= src[0]\n";
	tar[0]= src[0];
    }

};

template <typename Matrix, typename Vector>
struct mat_vec_et
{
    const static int my_rows= Matrix::my_rows, my_cols= Matrix::my_cols;

    mat_vec_et(const Matrix& A, const Vector& v) : A(A), v(v) {}

    const Matrix& A;
    const Vector& v;
};

template <int Row, int Col>
struct fsize_mat_vec_mult
{
    template <typename Matrix, typename VecIn, typename VecOut>
    void operator()(const Matrix& A, const VecIn& v, VecOut& w)
    {
	fsize_mat_vec_mult<Row, Col-1>()(A, v, w);
	w[Row]+= A[Row][Col] * v[Col];
    }
};

template <int Row>
struct fsize_mat_vec_mult<Row, 0>
{
    template <typename Matrix, typename VecIn, typename VecOut>
    void operator()(const Matrix& A, const VecIn& v, VecOut& w)
    {
	fsize_mat_vec_mult<Row-1, Matrix::my_cols-1>()(A, v, w);
	w[Row]= A[Row][0] * v[0];
    }
};

template <>
struct fsize_mat_vec_mult<0, 0>
{
    template <typename Matrix, typename VecIn, typename VecOut>
    void operator()(const Matrix& A, const VecIn& v, VecOut& w)
    {
	w[0]= A[0][0] * v[0];
    }
};

template <int Row, int Col>
struct fsize_mat_vec_mult_cm
{
    template <typename Matrix, typename VecIn, typename VecOut>
    void operator()(const Matrix& A, const VecIn& v, VecOut& w)
    {
	fsize_mat_vec_mult_cm<Row-1, Col>()(A, v, w);
	w[Row]+= A[Row][Col] * v[Col];
    }
};

template <int Col>
struct fsize_mat_vec_mult_cm<0, Col>
{
    template <typename Matrix, typename VecIn, typename VecOut>
    void operator()(const Matrix& A, const VecIn& v, VecOut& w)
    {
	fsize_mat_vec_mult_cm<Matrix::my_rows-1, Col-1>()(A, v, w);
	w[0]+= A[0][Col] * v[Col];
    }
};

template <int Row>
struct fsize_mat_vec_mult_cm<Row, 0>
{
    template <typename Matrix, typename VecIn, typename VecOut>
    void operator()(const Matrix& A, const VecIn& v, VecOut& w)
    {
	fsize_mat_vec_mult_cm<Row-1, 0>()(A, v, w);
	w[Row]= A[Row][0] * v[0];
    }
};

template <>
struct fsize_mat_vec_mult_cm<0, 0>
{
    template <typename Matrix, typename VecIn, typename VecOut>
    void operator()(const Matrix& A, const VecIn& v, VecOut& w)
    {
	w[0]= A[0][0] * v[0];
    }
};


template <int Row, int Col>
struct fsize_mat_vec_mult_aux
{
    template <typename Matrix, typename VecIn, typename Tmp>
    void operator()(const Matrix& A, const VecIn& v, Tmp& w)
    {
	fsize_mat_vec_mult_aux<Row, Col-1>()(A, v, w);
	w+= A[Row][Col] * v[Col];
    }
};

template <int Row>
struct fsize_mat_vec_mult_aux<Row, 0>
{
    template <typename Matrix, typename VecIn, typename Tmp>
    void operator()(const Matrix& A, const VecIn& v, Tmp& w)
    {
	w= A[Row][0] * v[0];
    }
};


template <int Row, int Col>
struct fsize_mat_vec_mult_reg
{
    template <typename Matrix, typename VecIn, typename VecOut>
    void operator()(const Matrix& A, const VecIn& v, VecOut& w)
    {
	fsize_mat_vec_mult_reg<Row-1, Col>()(A, v, w);

	typename VecOut::value_type tmp;
	fsize_mat_vec_mult_aux<Row, Col>()(A, v, tmp);
	w[Row]= tmp;
    }
};

template <int Col>
struct fsize_mat_vec_mult_reg<0, Col>
{
    template <typename Matrix, typename VecIn, typename VecOut>
    void operator()(const Matrix& A, const VecIn& v, VecOut& w)
    {
	std::cout << "fsize_mat_vec_mult_reg<0, Col>\n";
	typename VecOut::value_type tmp;
	fsize_mat_vec_mult_aux<0, Col>()(A, v, tmp);
	w[0]= tmp;
    }
};



template <typename T, int Size>
class fsize_vector 
{
    using self= fsize_vector;
    void check_index(int i) const { assert(i >= 0 && i < my_size); }

  public:  
    using value_type= T           ;
    const static int     my_size= Size;

    fsize_vector() {}

    fsize_vector( const self& that )
    {
	for (int i= 0; i < my_size; ++i)
	    data[i]= that.data[i];
    }

    self& operator=( const self& that ) 
    {
	fsize_assign<self, self, my_size-1>{}(*this, that);
	return *this;
    }

    template <typename Vector>
    self& operator=( const Vector& that ) 
    {
	fsize_assign<self, Vector, my_size-1>{}(*this, that);
	return *this;
    }


    template <typename Matrix, typename Vector>
    self& operator=(const mat_vec_et<Matrix, Vector>& that)
    {
	using et= mat_vec_et<Matrix, Vector>;
	using mv= fsize_mat_vec_mult_reg<et::my_rows-1, et::my_cols-1>;
	mv{}(that.A, that.v, *this);
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

  private:
    T     data[Size] ;
};


template <typename T, int Size>
std::ostream& operator<<(std::ostream& os, const fsize_vector<T, Size>& v)
{
  os << '[';
  for (int i= 0; i < v.size(); ++i) os << v[i] << ',';
  os << ']';
  return os ;
}

template <typename T, int Rows, int Cols>
class fsize_matrix 
{
    static_assert(Rows > 0, "Rows must be larger than 0."); 
    static_assert(Cols > 0, "Cols must be larger than 0.");

    using self= fsize_matrix;
  public:  
    using value_type= T;
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

    mat_vec_et<self, fsize_vector<T, Cols> > 
    operator*(const fsize_vector<T, Cols>& v) const 
    { 
	return {*this, v}; 
    }

  private:
    T     data[Rows][Cols];
};


int main() 
{
    fsize_vector<float, 4> v, w ;
    v[0] = v[1] = 1.0 ; v[2] = 2.0 ; v[3] = -3.0 ;
    w= v;

    fsize_matrix<float, 4, 4> A;
    A[0][1]= 2.3; A[1][2]= 3.4; A[2][3]= 4.1; A[3][0]= 5.; 

    w= A * v;
    std::cout << "A * v = " << w << '\n';

    return 0 ;
}
