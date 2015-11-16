#include <iostream>

int main () 
{
  const int concave = 1, monotone = 2, continuous = 4;

  int f_is = concave | continuous;
  std::cout << "f is " << f_is << std::endl;

  std::cout << "Is f concave? (0 means no, 1 means yes) " 
	    << (f_is & concave) << std::endl;

  f_is = f_is | monotone;
  f_is = f_is ^ concave;

  std::cout << "f is now " << f_is << std::endl;
  return 0 ;
}
