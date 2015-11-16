#include <iostream>
#include <fstream>
#include <cstdlib>
#include "print_compiler.hpp"

using namespace std;

struct cannot_open_file {};

int read_matrix_file(const char* fname)
{
    fstream f(fname);
    if (!f.is_open())
	// return 1;
	throw cannot_open_file();

    return 0;
}



int main (int argc, char* argv[]) 
{
    print_compiler();

    // read_matrix_file("does_not_exist.dat");

    try {
	read_matrix_file("does_not_exist.dat");
    } catch (cannot_open_file& e) {
	cerr << "O my gosh, the file is not there! Please caller help me.\n";
	throw;
    }

    
    // try {
    // 	read_matrix_file("does_not_exist.dat");
    // } catch (float& i) {
    // 	cerr << "Catch 1\n";
    // } catch (int& i) {
    // 	cerr << "Catch 2\n";
    // } catch (cannot_open_file& e) {
    // 	cerr << "Hey guys, your file does not exist! I'm out.\n";
    // 	exit(EXIT_FAILURE);
    // } catch (...) {}

    bool keep_trying= true;
    do {
	char fname[80]; // std::string is better
	cout << "Please enter file name: ";
	cin >> fname;
	try {
	    read_matrix_file(fname);
	    keep_trying= false;
	} catch (cannot_open_file& e) {
	    cout << "Could not open the file. Try another one!\n";
	} catch (...)
	    cout << "Something is fishy here. Try another file!\n";
	}
    } while (keep_trying);




    return 0;
}

