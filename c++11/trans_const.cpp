#include <iostream>
#include <cmath>
#include <typeinfo>
#include <type_traits>
#include <boost/numeric/mtl/mtl.hpp>


// namespace to avoid ambiguities with mtl
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

    template <bool Condition, typename ThenType, typename ElseType>
    struct conditional
    {
	using type= ThenType;
    };

    template <typename ThenType, typename ElseType>
    struct conditional<false, ThenType, ElseType>
    {
	using type= ElseType;
    };

    template <bool Condition, typename ThenType, typename ElseType>
    using conditional_t= typename conditional<Condition, ThenType, ElseType>::type;

    template <typename T>
    struct is_matrix
      : std::false_type
    {};
    
    template <typename Value, typename Para>
    struct is_matrix<mtl::dense2D<Value, Para> >
      : std::true_type
    {};

#if 1
    template <typename T>
    struct is_matrix<const T>
      : is_matrix<T> {};
#endif


#if 0
    template <typename Matrix>
    class transposed_view
    {
      public:
	using value_type= typename Matrix::value_type;
	using size_type=  typename Matrix::size_type;
	
	// typedef typename mtl::Collection<Matrix>::value_type  value_type;
	// typedef typename mtl::Collection<Matrix>::size_type   size_type;

	explicit transposed_view(Matrix& A) : ref(A) {}
	
	value_type& operator()(size_type r, size_type c) { return ref(c, r); }
	const value_type& operator()(size_type r, size_type c) const { return ref(c, r); }
	
      private:
	Matrix& ref;
    };

    template <typename Matrix>
    class const_transposed_view
    {
      public:
	using value_type= typename Matrix::value_type;
	using size_type=  typename Matrix::size_type;

	explicit const_transposed_view(const Matrix& A) : ref(A) {}
	
	const value_type& operator()(size_type r, size_type c) const { return ref(c, r); }
	
      private:
	const Matrix& ref;
    };

    template <typename Matrix>
    inline const_transposed_view<Matrix> trans(const Matrix& A)
    {
	return const_transposed_view<Matrix>(A);
    }

#else
    template <typename Matrix>
    class transposed_view
    {
	static_assert(is_matrix<Matrix>::value, "template argument is not a Matrix");
      public:
	using value_type= typename Matrix::value_type;
	using size_type=  typename Matrix::size_type;

      private:
	using vref_type= conditional_t<is_const<Matrix>::value,
				       const value_type&,
				       value_type&>;
      public:
	explicit transposed_view(Matrix& A) : ref(A) {}
	
	vref_type operator()(size_type r, size_type c) { return ref(c, r); }
	const value_type& operator()(size_type r, size_type c) const { return ref(c, r); }
	
      private:
	Matrix& ref;
    };
#endif

    template <typename Matrix>
    transposed_view<Matrix> inline trans(Matrix& A)
    {
	return transposed_view<Matrix>(A);
    }

    template <typename Matrix>
    struct is_matrix<transposed_view<Matrix> >
      : is_matrix<Matrix>
    {};
    
}

template <int M>
void f()
{
    typedef typename tst::conditional<M < 100, double, float>::type & value_type;
    typedef const typename tst::conditional<M < 100, const double, const float>::type const_value_type;
    std::cout << "typeid = " << typeid(value_type).name() << '\n';
}

int main (int argc, char* argv[]) 
{
    // const double eps= 0.00000001;
    const int n = 10;
    typedef tst::conditional<n < 100, double, float>::type& value_type;
    typedef const tst::conditional<n < 100, double, float>::type const_value_type;
    std::cout << "typeid = " << typeid(value_type).name() << '\n';
    f<17>();

    mtl::dense2D<float> A= {{2, 3, 4},
			    {5, 6, 7},
			    {8, 9, 10}};    
    std::cout << "trans(A) is\n" << trans(A);

    trans(A)[2][0]= 4.5;
    std::cout << "trans(A) is\n" << trans(A);

    const mtl::dense2D<float> B(A);
    std::cout << "trans(B) is\n" << trans(B);

    tst::transposed_view<mtl::dense2D<float> >  At(A);
    At(2, 0)= 4.5;

    std::cout << "tst::trans(A)(2, 0) = " << tst::trans(A)(2, 0) << '\n';
    tst::trans(A)(2, 0)= 4.6;
    std::cout << "trans(A) after modification is\n" << trans(A);

    std::cout << "typeid of trans(A) = " << typeid(tst::trans(A)).name() << '\n';
    std::cout << "typeid of trans(B) = " << typeid(tst::trans(B)).name() << '\n';
    // int ta= trans(A);
    // int tb= trans(B);
    // int tar= trans(A).ref; 
    // int tbr= trans(B).ref;

    std::cout << "tst::trans(B)(2, 0) = " << tst::trans(B)(2, 0) << '\n';
    // tst::trans(B)(2, 0)= 4.6;
    
    const tst::transposed_view<const mtl::dense2D<float> >  Bt(B);
    std::cout << "Bt(2, 0) = " << Bt(2, 0) << '\n';

    return 0 ;
}
