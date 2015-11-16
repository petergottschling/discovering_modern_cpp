#include <iostream>

extern "C" {
#include "dings.h"
}

// extern "C"
// int dings(int i);

int main (int argc, char* argv[]) 
{
    dings(3);
    static int bums;

    std::cout << "Hallo\n"; 
    return 0;
}

