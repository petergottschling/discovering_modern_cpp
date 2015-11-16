#include <iostream>
#include <vector>
#include <algorithm>

void print(int i)
{
    std::cout << i << ", ";
}

int main (int argc, char* argv[]) 
{
    std::vector<int> v;
    v.push_back(7); v.push_back(9); v.push_back(2);
    std::for_each(v.begin(), v.end(), [](int& i){ i+= 2; });
    std::for_each(v.begin(), v.end(), [](int i){ std::cout << i << ", "; });
    

    return 0 ;
}
