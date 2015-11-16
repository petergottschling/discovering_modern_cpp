#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

template <typename C>
void reverse_sort(C& c)
{
    sort(begin(c), end(c), [](auto x, auto y){ return x > y; });
}

int main(int argc, char** argv) 
{
    vector<int> v= {3, 7, 2, 9};

    sort(begin(v), end(v));    
    copy(cbegin(v), cend(v), ostream_iterator<int>(cout, ", "));
    cout << endl;

    // sort(begin(v), end(v), [](auto x, auto y){ return x > y; });
    reverse_sort(v); 
    copy(begin(v), end(v), ostream_iterator<int>(cout, ", "));
    cout << endl;

    return 0; 
} 
 
