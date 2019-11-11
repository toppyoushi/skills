#include <iostream>
#include <string>
#include <stdlib.h>
#include <exception>
using namespace std;
class AbstractProductA
{
public:
    virtual void use() = 0;
};
class AbstractProductB
{
public:
    virtual void eat() = 0;
};
class ProductA : public AbstractProductA
{
public:
    void use()
    {
        cout << "use product A" << endl;
    }
};
class ProductB : public AbstractProductB
{
public:
    void eat()
    {
        cout << "use product B" << endl;
    }
};
class AbstractFactory
{
public:
    virtual AbstractProductA *createProductA() = 0;
    virtual AbstractProductB *createProductB() = 0;
};
class FactoryA : public AbstractFactory
{
public:
    AbstractProductA *createProductA()
    {
        AbstractProductA *p = nullptr;
        try
        {
            p = new ProductA();
        }
        catch (exception e)
        {
            cerr << e.what() << endl;
        }
        return p;
    }
    AbstractProductB *createProductB()
    {
        AbstractProductB *p = nullptr;
        try
        {
            p = new ProductB();
        }
        catch (exception e)
        {
            cerr << e.what() << endl;
        }
        return p;
    }
};
class FactoryB : public AbstractFactory
{
public:
    AbstractProductA *createProductA()
    {
        AbstractProductA *p = nullptr;
        try
        {
            p = new ProductA();
        }
        catch (exception e)
        {
            cerr << e.what() << endl;
        }
        return p;
    }
    AbstractProductB *createProductB()
    {
        AbstractProductB *p = nullptr;
        try
        {
            p = new ProductB();
        }
        catch (exception e)
        {
            cerr << e.what() << endl;
        }
        return p;
    }
};

int main()
{
    AbstractFactory *af = new FactoryA();
}