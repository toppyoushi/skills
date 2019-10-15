#include <iostream>
#include <cstring>
using namespace std;
void Fun(int a[])
{
    cout<<sizeof(a)<<endl;          //将数组名转化为指针类型
}
int main()
{
    char a[] ={1,2,3,0,4,5};
    cout<<strlen(a)<<endl;
}
