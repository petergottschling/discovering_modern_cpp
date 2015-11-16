#include <iostream>
#include <string>

int main () 
{
    int i= 5; 
    std::cout << "i = " << 5 << "\n" << std::endl;
    std::cerr << "Alles falsch!\n";
#if 0
    int age, size;
    std::cin >> age >> size;
    
    std::cout << "age = " << age << ", size = "
	      << size << std::endl;
#endif

    std::string name;
    std::cin >> name;
    name= name + " Schmidt";
    std::cout << name << '\n';


    return 0 ;
}
