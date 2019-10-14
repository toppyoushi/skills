#include <iostream>
using namespace std;
class Base
{
public:
    virtual void f()
    {
        cout << "Base::f()" << endl;
    }
    virtual void g()
    {
        cout << "Base::g()" << endl;
    }
    virtual void h()
    {
        cout << "Base::h()" << endl;
    }
};
class Derive : public Base
{
public:
    virtual void f1()
    {
        cout << "Derive::f1()" << endl;
    }
    virtual void g1()
    {
        cout << "Derive::g1()" << endl;
    }
    virtual void h1()
    {
        cout << "Derive::h1()" << endl;
    }
};
int main()
{
    typedef void (*Fun)();
    Base *b;
    Derive d;
    b = &d;
    Fun bf = (Fun)*((size_t *)*(size_t *)b);
    Fun bg1 = (Fun)*((size_t *)*(size_t *)b+1);
    Fun bg2 = (Fun)*((int *)*(int *)b + 2);
    Fun bh1 = (Fun)*((size_t *)*(size_t *)b + 2);
    Fun bh2 = (Fun)*((int *)*(int *)b + 4);
    bf();
    bg1();
    bg2();
    bh1();
    bh2();
    return 0;
}
