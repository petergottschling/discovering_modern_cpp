#include <iostream>
#include "solver.hpp"
#include "mesher.hpp"

int main()
{
    mesh my_mesh;
    mesh_it(my_mesh);

    system my_system= discretize(my_mesh);
    solve(my_system);

    return 0;
}
