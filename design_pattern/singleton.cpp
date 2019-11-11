#include<iostream>
#include<string>
using namespace std;
class Singleton;
class Singleton
{
private:
    static Singleton *s;
    Singleton(){}
public:
    static Singleton *getSingleton();
    void printInfo()
    {
        cout<<"print Singleton"<<endl;
    }
    ~Singleton()
    {
        delete s;
    }
};
Singleton *Singleton::s = nullptr;
Singleton *Singleton::getSingleton()
{
    if(Singleton::s == nullptr)
    {
        Singleton::s = new Singleton();
    }
    return Singleton::s;
}
int main()
{
    Singleton *s = Singleton::getSingleton();
    s->printInfo();
}