#include <iostream>
#include <cmath>

#include <boost/type_traits.hpp>
#include <boost/static_assert.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/numeric/mtl/mtl.hpp>

namespace tst {


template <typename T>
struct Magnitude
{
    typedef T type;
};

template <typename T>
struct Magnitude<std::complex<T> >
{
    typedef T type;
};

template <typename T, typename P>
struct Magnitude<mtl::dense_vector<T, P> >
{
    typedef typename Magnitude<T>::type type;
};

template <typename T, typename P>
struct Magnitude<mtl::dense2D<T, P> >
{
    typedef typename Magnitude<T>::type type;
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

    template <typename T>
    struct is_vector
      : boost::mpl::false_ {};

    template <typename T>
    struct is_vector<const T>
      : is_vector<T> {};

    template <typename V, typename P>
    struct is_vector<mtl::dense_vector<V, P> >
      : boost::mpl::true_ {};

    template <bool B, typename T>
    struct enable_if_c
    {
	typedef T   type;
    };

    template <typename T>
    struct enable_if_c<false, T>
    {};

    template <typename Cond, typename T>
    struct enable_if_
      : enable_if_c<Cond::value, T>
    {};

    template <typename T>
    typename enable_if_c<is_matrix<T>::value && !is_sparse_matrix<T>::value, 
			 typename Magnitude<T>::type>::type
    inline one_norm(const T& A)
    {


    }
    
    template <typename T>
    typename enable_if_<is_sparse_matrix<T>, typename T::type>::type
    inline one_norm(const T& A)
    {


    }
    
    template <typename T>
    typename enable_if_<is_vector<T>, typename Magnitude<T>::type>::type
    inline one_norm(const T& v)
    {


    }
    

// SFINAE
}

int main (int argc, char* argv[]) 
{

    return 0 ;

}
