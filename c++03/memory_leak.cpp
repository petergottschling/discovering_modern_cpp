int main () 
{
    int* xd= new int[10];
    xd= new int[15];
    delete[] xd;

    return 0 ;
}
