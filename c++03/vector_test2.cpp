#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main (int argc, char* argv[]) 
{
    vector<int> v;
    v.push_back(3); v.push_back(4); v.push_back(7); v.push_back(9); 
    vector<int>::iterator it= find(v.begin(), v.end(), 4);
    cout << "After " << *it << " comes " << *(it+1) << '\n';
    v.insert(it+1, 5); // insert value 5 at position 2
    v.erase(v.begin()); // delete entry at position 1
    cout << "Size = " << v.size() << ", capacity = " << v.capacity() << '\n';
    {
	vector<int> tmp(v);
	swap(v, tmp);
    }	
    v.push_back(7);
    for (vector<int>::iterator it= v.begin(); it < v.end(); ++it)
	cout << *it << ",";
    cout << '\n';

    return 0;
}

