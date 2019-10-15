#include <iostream>
#include <cstring>
#include <iomanip>
using namespace std;
class A{
public:
    A(int a):_a(a)
    {
        cout<<"A construtor"<<endl;
    }
    int getA()
    {
        return this->_a;
    }
    ~A()
    {
        cout<<"A deconstructor"<<endl;
    }
protected:
    int _a;
};
class B:public A{
public:
    B(int a,int b):A(a),_b(b){
        cout<<"B constructor"<<endl;
        cout<<_a<<_b<<endl;
    }
private:
    int _b;
};
void fun(A a)
{
    cout<<a.getA()<<endl;
}
int main()
{
    // A *a;
    // a = new A(5);
    fun(5);
}
