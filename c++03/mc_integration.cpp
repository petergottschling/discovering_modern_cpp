#include <iostream>
#include <cmath>
#include <boost/random.hpp>

double function(double argument)
{
   return sin(argument);
}

int main(int argc, char** argv)
{
   // random number setup 
   //
   typedef boost::mt19937 base_generator_type;

   base_generator_type generator(42u);
   boost::uniform_real<> uniform_distribution(0,1);
   boost::variate_generator<base_generator_type&, boost::uniform_real<> > 
      random_uniform(generator, uniform_distribution);

   // integration now from 0 to 1
   // 
   long number_of_samples = 1000;

   double sum(0);

   for (long i(0); i < number_of_samples; ++i)
   {
      double value = function(random_uniform());
      sum += value;
   }

   std::cout << "the approximate result is: " << sum / number_of_samples << std::endl;

   return 0;
}
