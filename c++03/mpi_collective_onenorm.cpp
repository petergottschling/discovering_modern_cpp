#include <iostream>
#include <cmath>
#include <mpi.h>

int main (int argc, char* argv[]) 
{
    MPI_Init(&argc, &argv);            

    int myrank, nprocs;
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

    float vec[2];
    vec[0]= 2*myrank; vec[1]= vec[0]+1;

    // Local accumulation
    float local= std::abs(vec[0]) + std::abs(vec[1]);

    // Global accumulation
    float global;
    MPI_Allreduce (&local, &global, 1, MPI_FLOAT, MPI_SUM, MPI_COMM_WORLD);
    std::cout << "Hello, I am process " << myrank << " and I know too that |v|_1 is " << global << ".\n";

    MPI_Finalize();      
    return 0 ;
}
