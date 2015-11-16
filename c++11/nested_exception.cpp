#include <iostream>
#include <exception>
#include <stdexcept>
#include <typeinfo>
#include "print_compiler.hpp"

using namespace std;

void foo() {
    throw std::runtime_error("Exception thrown by foo");
}

void bar() {
    try {
        foo();

    } catch(...) {
        std::throw_with_nested(std::logic_error("Exception detected inside bar"));
    }
}

void print_backtrace(std::exception_ptr exception, std::string prefix = "") 
{
    try {
	std::rethrow_exception(exception);

    } catch(const std::exception& e) {
	std::cerr << prefix + "[exception] Exception of type \"" << typeid(e).name() << "\"";
	std::cerr << prefix + "[exception] Message: " + std::string(e.what());

    } catch(const std::nested_exception&) {
	// handled below
    } catch(...) {
	std::cerr << prefix + "[exception] Exception of unknown type";
    }

    try {
	std::rethrow_exception(exception);

    } catch(const std::nested_exception& e) {
	print_backtrace(e.nested_ptr(), prefix + "    ");
    } catch (...) {
    }
    std::cerr << std::endl;
}

int main() 
{
    print_compiler();
    try {
        bar();
        
    } catch(...) {
        print_backtrace(std::current_exception());
    }

    return 0;
}


