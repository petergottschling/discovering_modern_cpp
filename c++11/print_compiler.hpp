#ifndef PRINT_COMPILER_INCLUDE
#define PRINT_COMPILER_INCLUDE

#include <iostream>

void print_compiler()
{
# if defined(__INTEL_COMPILER)
    std::cout << "Intel compiler, version (intern) " << __INTEL_COMPILER << ", i.e. icc/icpc " 
	      << double(__INTEL_COMPILER) / 100.0 << '\n';
# elif defined(__clang__)
    std::cout << "Clang C++ compiler, version " << __clang_major__ << '.' << __clang_minor__ << '\n';
# elif defined(__GNUC__)
    std::cout << "GNU compiler, i.e. g++ " << __GNUC__ << '.' << __GNUC_MINOR__ << '.' << __GNUC_PATCHLEVEL__ << '\n';
# elif defined(__PGI)
    std::cout << "Portland group compiler (MTL4 not tested for it yet).\n";
# elif defined(__IBMCPP__)
    std::cout << "IBM compiler xlc++ (MTL4 not tested for it yet).\n"; 
    // version __xlC__ (or __xlc__) VVRM version, release, modification
# elif defined(_MSC_VER)
    std::cout << "Visual studio C++ compiler, version (intern) " << _MSC_VER << '\n';
# else
    std::cout << "Unknown compiler\n";
# endif
}

#endif
