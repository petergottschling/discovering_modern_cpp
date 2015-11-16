#include <iostream>
#include <cmath>
#include <typeinfo>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits.hpp>
#include <boost/static_assert.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/numeric/mtl/mtl.hpp>

namespace tst {

    template <typename T>
    struct is_const
    {
	static const bool value= false;
    };

    template <typename T>
    struct is_const<const T>
    {
	static const bool value= true;
    };

    template <typename T>
    struct is_matrix
      : boost::mpl::false_ {};

    template <typename T>
    struct is_matrix<const T>
      : is_matrix<T> {};

    template <typename V, typename P>
    struct is_matrix<mtl::dense2D<V, P> >
      : boost::mpl::true_ {};


    template <bool C, typename ThenType, typename ElseType>
    struct if_c
    {
	typedef ThenType type;
    };

    template <typename ThenType, typename ElseType>
    struct if_c<false, ThenType, ElseType>
    {
	typedef ElseType type;
    };

    template <typename Cond, typename ThenType, typename ElseType>
    struct if_
      : if_c<Cond::value, ThenType, ElseType>
    {};

    template <typename Matrix>
    class transposed_view
    {
	//BOOST_STATIC_ASSERT((is_matrix<Matrix>::value)); // argument Matrix must be a known matrix
	// static_assert(is_matrix<Matrix>::value, "argument Matrix must be a known matrix");
      public:
	typedef typename mtl::Collection<Matrix>::value_type  value_type;
	typedef typename mtl::Collection<Matrix>::size_type   size_type;
	typedef typename if_<is_const<Matrix>,
			     const value_type&,
			     value_type&>::type               ref_type;

	transposed_view(Matrix& A) : ref(A) {}
#if 1
	template <typename U>
	transposed_view(typename boost::enable_if<boost::is_scalar<U>, U>::type x) { }
#endif

	ref_type operator()(size_type r, size_type c) { return ref(c, r); }
	const value_type& operator()(size_type r, size_type c) const { return ref(c, r); }
	
      private:
	Matrix& ref;
    };

    template <typename Matrix>
    struct is_matrix<transposed_view<Matrix> >
      : is_matrix<Matrix> {};


    template <typename Matrix>
    transposed_view<Matrix> inline trans(Matrix& A)
    {
	return transposed_view<Matrix>(A);
    }

}

template <int N>
void f()
{
    typename tst::if_c<N < 100, float, double>::type x;
    std::cout << "typeid of x = " << typeid(x).name() << '\n';
}


int main (int argc, char* argv[]) 
{
    typedef int T;



    mtl::dense2D<float> A(3, 3);
    A=  2, 3, 4,
	5, 6, 7,
	8, 9, 10;
    std::cout << "trans(A)(2, 0) = " << tst::trans(A)(2, 0) << '\n';
    tst::trans(A)(2, 0)= 4.5;

    std::cout << "A is\n" << A;

    const mtl::dense2D<float> B(A);
    std::cout << "trans(B)(2, 0) = " << tst::trans(B)(2, 0) << '\n';

    double d= 3.4;
    tst::transposed_view<double> td(d);

    return 0 ;

}
