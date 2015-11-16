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
    float global= 0.0f;
    MPI_Status st;
    // Receive from predecessor
    if (myrank > 0)
	MPI_Recv(&global, 1, MPI_FLOAT, myrank-1, 387, MPI_COMM_WORLD, &st);
    // Increment
    global+= local;
    // Send to successor
    if (myrank+1 < nprocs)
	MPI_Send(&global, 1, MPI_FLOAT, myrank+1, 387, MPI_COMM_WORLD);
    else
	std::cout << "Hello, I am the last process and I know that |v|_1 is " << global << ".\n";

    MPI_Finalize();      

    return 0 ;
}
