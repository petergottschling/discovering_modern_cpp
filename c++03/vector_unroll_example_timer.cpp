#include <cassert>
#include <iostream>
#include <boost/timer.hpp>

template <typename T>
class vector 
{
    void check_size(int that_size) const { assert(my_size == that_size); }
    void check_index(int i) const { assert(i >= 0 && i < my_size); }
  public:
    explicit vector(int size)
      : my_size(size), data( new T[my_size] )
    {}

    vector()
      : my_size(0), data(0)
    {}

    vector( const vector& that )
      : my_size(that.my_size), data( new T[my_size] )
    {
	for (int i= 0; i < my_size; ++i)
	    data[i]= that.data[i];
    }

    ~vector() { if (data) delete [] data ; }

    vector& operator=( const vector& that ) 
    {
	check_size(that.my_size);
	for (int i= 0; i < my_size; ++i)
	    data[i]= that.data[i];
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
    int   my_size ;
    T*    data ;
};


template <typename T>
std::ostream& operator<<(std::ostream& os, const vector<T>& v)
{
  os << '[';
  for (int i= 0; i < v.size(); ++i) os << v[i] << ',';
  os << ']';
  return os ;
}
 

template <unsigned Offset, unsigned Max>
struct my_axpy_ftor
{
    template <typename U, typename V, typename W>
    void operator()(U& u, const V& v, const W& w, unsigned i)
    {
	u[i+Offset]= 3.0f * v[i+Offset] + w[i+Offset];
	my_axpy_ftor<Offset+1, Max>()(u, v, w, i);
    }
};

template <unsigned Max>
struct my_axpy_ftor<Max, Max> 
{
    template <typename U, typename V, typename W>
    void operator()(U& u, const V& v, const W& w, unsigned i) {}
};

template <unsigned BSize, typename U, typename V, typename W>
void my_axpy(U& u, const V& v, const W& w)
{
    assert(u.size() == v.size() && v.size() == w.size());
    unsigned s= u.size(), sb= s / BSize * BSize;
   
    for (unsigned i= 0; i < sb; i+= BSize)
	my_axpy_ftor<0, BSize>()(u, v, w, i);

    for (unsigned i= sb; i < s; i++) 
	u[i]= 3.0f * v[i] + w[i];
}



int main(int argc, char** argv)  
{
    /* const */ unsigned s= 1000;
    // if (argc > 1) s= atoi(argv[1]);
    vector<float> u(s), v(s), w(s);

    for (unsigned i= 0; i < s; i++) { 
	v[i]= float(i);
	w[i]= float(2*i + 15);
    }
    
    for (unsigned j= 0; j < 3; j++) 
	for (unsigned i= 0; i < s; i++) 
	    u[i]= 3.0f * v[i] + w[i]; 

    const unsigned rep= 2000000; // 1000000; 

    boost::timer native; 
    // asm ( "# start here native" );
    for (unsigned j= 0; j < rep; j++)
	for (unsigned i= 0; i < s; i++)  
	    u[i]= 3.0f * v[i] + w[i];
    // asm ( "# end here native" );
    std::cout << "Compute time native loop is " << 1000000.0 * native.elapsed() / double(rep) << " mmicros.\n";
    std::cout << "u[0] is " << u[0] << '\n';


    boost::timer unrolled;
    // asm ( "# start here unrolled" );
    for (unsigned j= 0; j < rep; j++) {
	unsigned sb= s / 4 * 4;
	for (unsigned i= 0; i < sb; i+= 4) {
	    u[i]=   3.0f * v[i]   + w[i];
	    u[i+1]= 3.0f * v[i+1] + w[i+1];
	    u[i+2]= 3.0f * v[i+2] + w[i+2];
	    u[i+3]= 3.0f * v[i+3] + w[i+3];
	} 
	for (unsigned i= sb; i < s; i++) 
	    u[i]= 3.0f * v[i] + w[i];
    }
    // asm ( "# end here unrolled" );
    std::cout << "Compute time unrolled loop is " << 1000000.0 * unrolled.elapsed() / double(rep) << " mmicros.\n";
    std::cout << "u[0] is " << u[0] << '\n'; 


    boost::timer unrolled2; 
    for (unsigned j= 0; j < rep; j++)
	my_axpy<2>(u, v, w);
    std::cout << "Compute time unrolled<2> loop is " << 1000000.0 * unrolled2.elapsed() / double(rep) << " mmicros.\n";
    std::cout << "u[0] is " << u[0] << '\n';


    boost::timer unrolled4;
    for (unsigned j= 0; j < rep; j++)
	my_axpy<4>(u, v, w);
    std::cout << "Compute time unrolled<4> loop is " << 1000000.0 * unrolled4.elapsed() / double(rep) << " mmicros.\n";
    std::cout << "u[0] is " << u[0] << '\n';


    boost::timer unrolled6;
    for (unsigned j= 0; j < rep; j++)
	my_axpy<6>(u, v, w);
    std::cout << "Compute time unrolled<6> loop is " << 1000000.0 * unrolled6.elapsed() / double(rep) << " mmicros.\n";
    std::cout << "u[0] is " << u[0] << '\n';


    boost::timer unrolled8;
    for (unsigned j= 0; j < rep; j++)
	my_axpy<8>(u, v, w);
    std::cout << "Compute time unrolled<8> loop is " << 1000000.0 * unrolled8.elapsed() / double(rep) << " mmicros.\n";
    std::cout << "u[0] is " << u[0] << '\n';
 
    return 0;
}

 
