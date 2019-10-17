#include <iostream>
#include <vector>
using namespace std;
int jumpFloor(int number) {
        if(number < 1)
            return 0;
        if(number == 1)
        {
            return 1;
        }
        if(number == 2)
        {
            return 2;
        }
        return jumpFloor(number - 1) + jumpFloor(number - 2);
    }
int main(int argc,char *argv[])
{
    int n;
    cin>>n;
    cout<<jumpFloor(n)<<endl;;

    return 0;
}
