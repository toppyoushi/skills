#include <iostream>
#include <cstdlib>
using namespace std;
void fun(int *p)
{
    (*p) = 2;
    p+=1;
    cout<<p<<endl;
}
int main()
{
    int a = 1;
    int *p = &a;
    cout<<p<<endl;
    fun(p);
    cout<<p<<endl;
    cout<<a<<endl;
}