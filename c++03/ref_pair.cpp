#include <iostream>
#include <vector>
#include <functional>
#include <iterator>


using namespace std;

int main (int argc, char* argv[]) 
{
    vector<int> v1(3);
    pair<vector<int>&, int> p(v1, 8), p2(p);

    copy(p2.first.begin(), p2.first.end(), ostream_iterator<int>(cout, ", ")); cout << endl;
    
    return 0 ;
}
