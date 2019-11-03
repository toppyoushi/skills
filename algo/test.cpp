#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;
class A{
    private:
    static int a;
};
int A::a=0;
int main()
{
    A a1;
    cout<<A::a<<endl;
}
