#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>


template <typename Value>
class coo_matrix
{
    typedef Value value_type; // better in trait
  public:
    coo_matrix(int nr, int nc) : nr(nr), nc(nc) {}

    void insert(int r, int c, Value v)
    {
	assert(r < nr && c < nc);
	row_index.push_back(r);
	col_index.push_back(c);
	data.push_back(v);
    }

    void sort() {}

    int nnz() const { return row_index.size(); }
    int num_rows() const { return nr; }
    int num_cols() const { return nc; }

    int begin_row(int r) const
    {
	unsigned i= 0;
	while (i < row_index.size() && row_index[i] < r) ++i;
	return i;
    }

    template <typename Matrix> friend struct coo_col;
    template <typename Matrix> friend struct coo_row;
    template <typename Matrix> friend struct coo_const_value;
    template <typename Matrix> friend struct coo_value;
  private:
    int                nr, nc;
    std::vector<int>   row_index, col_index;
    std::vector<Value> data;
};


struct nz_cursor
{
    typedef int key_type;

    nz_cursor(int offset) : offset(offset) {}

    nz_cursor& operator++() { offset++; return *this; }
    nz_cursor operator++(int) { nz_cursor tmp(*this); offset++; return tmp; }

    key_type operator*() const { return offset; }

    bool operator!=(const nz_cursor& other) { return offset != other.offset; }
  protected:
    int offset;
};

template <typename Matrix> 
nz_cursor nz_begin(const Matrix& A)
{
    return nz_cursor(0);
}

template <typename Matrix> 
nz_cursor nz_end(const Matrix& A)
{
    return nz_cursor(A.nnz());
}


template <typename Matrix> 
struct coo_col
{
    typedef int key_type;

    coo_col(const Matrix& ref) : ref(ref) {}

    int operator()(key_type k) const { return ref.col_index[k]; }
  private:
    const Matrix& ref;
};

template <typename Matrix> 
struct coo_row
{
    typedef int key_type;

    coo_row(const Matrix& ref) : ref(ref) {}

    int operator()(key_type k) const { return ref.row_index[k]; }
  private:
    const Matrix& ref;
};

template <typename Matrix> 
struct coo_const_value
{
    typedef int key_type;

    typedef typename Matrix::value_type value_type;

    coo_const_value(const Matrix& ref) : ref(ref) {}

    value_type operator()(key_type k) const { return ref.data[k]; }
  private:
    const Matrix& ref;
};

template <typename Matrix> 
struct coo_value
{
    typedef int key_type;

    typedef typename Matrix::value_type value_type;

    coo_value(Matrix& ref) : ref(ref) {}

    value_type operator()(key_type k) const { return ref.data[k]; }

    void operator()(key_type k, const value_type& v) { ref.data[k]= v; }
  private:
    Matrix& ref;
};


template <typename Matrix> 
struct row_cursor
{
    row_cursor(int r, const Matrix& ref) : r(r), ref(ref) {}

    row_cursor& operator++() { r++; return *this; }
    row_cursor operator++(int) { row_cursor tmp(*this); r++; return tmp; }

    bool operator!=(const row_cursor& other) { return r != other.r; }

    nz_cursor begin() const { return nz_cursor(ref.begin_row(r)); }
    nz_cursor end() const { return nz_cursor(ref.begin_row(r+1)); }
  protected:
    int r;
    const Matrix& ref;
};



template <typename Matrix> 
row_cursor<Matrix> row_begin(const Matrix& A)
{
    return row_cursor<Matrix>(0, A);
}

template <typename Matrix> 
row_cursor<Matrix> row_end(const Matrix& A)
{
    return row_cursor<Matrix>(A.num_rows(), A);
}

template <typename Matrix> 
nz_cursor nz_begin(const row_cursor<Matrix>& c)
{
    return c.begin();
}

template <typename Matrix> 
nz_cursor nz_end(const row_cursor<Matrix>& c)
{
    return c.end();
}

int main (int argc, char* argv[]) 
{

    coo_matrix<float> A(3, 5);
    A.insert(0, 0, 2.3);
    A.insert(0, 3, 3.4);
    A.insert(1, 2, 4.5);
    A.insert(2, 1, 5.6);
    
    coo_col<coo_matrix<float> >    col(A);
    coo_row<coo_matrix<float> >    row(A);
    coo_value<coo_matrix<float> >  value(A);

#if 0
    for (nz_cursor c= nz_begin(A), end= nz_end(A); c != end; ++c)
	std::cout << "A[" << row(*c) << "][" << col(*c) << "] = " << value(*c) << "\n"; 

    // Multiply matrix by 2
    for (nz_cursor c= nz_begin(A), end= nz_end(A); c != end; ++c)
	value(*c, 2.0 * value(*c));

    std::cout << "\n\n";
    // print again
    for (nz_cursor c= nz_begin(A), end= nz_end(A); c != end; ++c)
	std::cout << "A[" << row(*c) << "][" << col(*c) << "] = " << value(*c) << "\n"; 

#endif

    // 2D traversal
    for (row_cursor< coo_matrix<float> > c= row_begin(A), end= row_end(A); c != end; ++c) {
	std::cout << "-----\n"; 
	for (nz_cursor ic= nz_begin(c), iend= nz_end(c); ic != iend; ++ic)
	    std::cout << "A[" << row(*ic) << "][" << col(*ic) << "] = " << value(*ic) << "\n"; 
    }   
    std::cout << "-----\n"; 


    return 0 ;

}
