#include <iostream>

int main () 
{
    const int csize= 3 * 5, c2= csize * 2;
    int x[csize], y[3], w[]= {3, 7, 9, 1};

    x[0]= 2; 
    x[4]= 7;
    std::cout << w[2] << '\n';

    float A[2][3]= {{4, 5, 9}, {3, 4, 7}};
    std::cout << "A[1][1] = " << A[1][1] << '\n';

    int size= 5;
    cin >> size;
    int* xd= new int[size];
    delete[] xd;

    int* p= new int;
    delete p;

    p= &y[1];

    int i= 5;
    int &r= y[1], &r2= i;

    r= y[2]; // *p= y[2]; 5 * *p;
    i + 6; r2 + 6;

    return 0 ;
}
