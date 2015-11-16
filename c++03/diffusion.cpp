#include <iostream>
#include <cmath>

int main(int argc, char** argv)
{
   const size_t domain_length(100);
   const size_t time_steps(100);
   double delta_t(0.001);
   double delta_x(0.1);

   double concentration_0[domain_length] = {0};
   double concentration_1[domain_length] = {0};

   double *current_concentration(concentration_0);
   double *next_concentration(concentration_1);

   current_concentration[domain_length / 2] = 100;
   for (size_t i(1); i < domain_length-1; ++i)
   {
      std::cout << 0 << "\t" << i << "\t" << current_concentration[i] << std::endl;
   }
   std::cout << std::endl;

   for (size_t t(0); t < time_steps; ++t)
   {
      for (size_t i(1); i < domain_length-1; ++i)
      {
         next_concentration[i] =
            current_concentration[i] + 
            delta_t / delta_x / delta_x *
            (
               current_concentration[i+1] + 
               current_concentration[i-1] + 
               - 2 * current_concentration[i] 
            );
         std::cout << t << "\t" << i << "\t" << next_concentration[i] << std::endl;
      }
      double* temp(next_concentration);
      current_concentration = next_concentration;
      next_concentration = temp;
      std::cout << std::endl;
   }
   return 0;
}
