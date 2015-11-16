#include <iostream>
#include <cmath>

int main(int argc, char** argv)
{
   const size_t domain_length(150) ;
   double delta_x(0.1) ;

   double boundary_0(-1) ;
   double boundary_1(1) ;

   double potential[domain_length] = {0} ;
   double system_matrix[domain_length][domain_length] =  {{0}} ;
   double rhs[domain_length] = {0} ;


   // set boundary conditions
   // 
   system_matrix[0][0] = 1. ;
   system_matrix[domain_length-1][domain_length-1] = 1. ;
   
   rhs[0] = boundary_0 ;
   rhs[domain_length - 1] = boundary_1 ;

   // fill the matrix with values 
   // these is for an equidistant grid
   //
   for (size_t i(1); i < domain_length - 1; ++i)
   {
      system_matrix[i][i] = 2 ;
      system_matrix[i][i+1] = -1 ;
      system_matrix[i][i-1] = -1 ;
      rhs[i] += sin(delta_x * i * M_PI );
      std::cerr << i << "\t" << rhs[i] << std::endl;
   }

   // solve the linear equation system
   //  system_matrix * potential = rhs
   // using a tridiagonal solver algorithm
   //
   system_matrix[0][1] = system_matrix[0][1] / system_matrix[0][0];
   rhs[0] = rhs[0] / system_matrix[0][0];

   for (size_t i(1); i < domain_length - 1; i++)
   {
      double temp(system_matrix[i][i] - system_matrix[i][i-1] * system_matrix[i-1][i]);
      system_matrix[i][i+1] = system_matrix[i][i+1] / temp ;
      rhs[i] = ( rhs[i] - system_matrix[i][i-1] * rhs[i-1] ) / temp ;
   }
   
   potential[domain_length-1] = rhs[domain_length-1]; 
   for (int i = domain_length - 2; i >= 0; i--)
   {
      potential[i] = rhs[i] - system_matrix[i][i+1] * potential[i+1] ;
   }

   // show the solution
   //
   for (size_t i(0); i < domain_length; ++i)
   {
      std::cout << i << "\t" << potential[i] << std::endl ;
   }

   return 0;
}
