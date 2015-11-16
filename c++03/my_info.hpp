#include <typeinfo>
#include <string>

template <typename T>
struct wrap {};

// wrap the type since typeid forgets all the qualifiers
template <typename T>
std::string my_info()
{
    return typeid(wrap<T>).name();
}
