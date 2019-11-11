#include <iostream>
#include <string>
using namespace std;

class Product
{
public:
    virtual void use() = 0;
};

class A : public Product
{

public:
    A() {}
    void use()
    {
        cout << "use product A " << endl;
    }
};

class B : public Product
{
public:
    B() {}
    void use()
    {
        cout << "use product B " << endl;
    }
};

class SimpleFactory
{
public:
    SimpleFactory() {}
    static Product *createProduct(string &p_type)
    {
        Product *p = nullptr;
        if (p_type == "A")
        {
            p = new A();
        }
        if (p_type == "B")
        {
            p = new B();
        }
        return p;
    }
};
int main()
{
    string s;
    cin>>s;
    Product *p = SimpleFactory::createProduct(s);
    p->use();
}