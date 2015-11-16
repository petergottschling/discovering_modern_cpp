#include <iostream>
#include <functional>
#include <cmath>
#include <boost/mpi.hpp>

namespace mpi = boost::mpi;

int main (int argc, char* argv[]) 
{
    mpi::environment env(argc, argv);
    mpi::communicator world;
    int myrank= world.rank();

    float vec[2];
    vec[0]= 2*myrank; vec[1]= vec[0]+1;

    // Local accumulation
    float local= std::abs(vec[0]) + std::abs(vec[1]);

    // Global accumulation
    float global= mpi::all_reduce(world, local, std::plus<float>());
    std::cout << "Hello, I am process " << world.rank() << " and I know too that |v|_1 is " << global << ".\n";

    return 0 ;
}
