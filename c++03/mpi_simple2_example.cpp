#include <iostream>
#include <mpi.h>

int main (int argc, char* argv[]) 
{
    MPI_Init(&argc, &argv);            

    int myrank, nprocs;
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

    std::cout << "Hello world, I am process number " << myrank << " out of " << nprocs << ".\n";
    MPI_Finalize();      

    return 0 ;
}
