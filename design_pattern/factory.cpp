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

class Factory
{
public:
    virtual Product *createProduct() = 0;
};

class AFactory : public Factory
{
public:
    AFactory() {}
    A *createProduct()
    {
        return new A();
    }
};

class BFactory : public Factory
{
public:
    BFactory() {}
    B *createProduct()
    {
        return new B();
    }
};
int main()
{
    Factory *f = new AFactory();
    Product *p = f->createProduct();
    p->use();
    return 0;
}