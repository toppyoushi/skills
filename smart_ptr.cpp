#include <iostream>
#include <cassert>
using namespace std;
template <class T>
class SmartPtr
{
private:
    T *_ptr;
    size_t *_count;

public:
    SmartPtr() {}
    SmartPtr(T* ptr = nullptr) : _ptr(ptr)
    {
        if (_ptr)
        {
            _count = new size_t(1);
        }
        else
        {
            _count = new size_t(0);
        }
    }
    SmartPtr(const SmartPtr &p)
    {
        if (this != &p)
        {
            this->_ptr = p._ptr;
            this->_count = p._count;
            (*this->_count)++;
        }
    }
    SmartPtr &operator=(const SmartPtr &p)
    {
        if (this != &p)
        {
            return *this;
        }
        if (this->_ptr)
        {
            this->count--;
            if (this->_count == 0)
            {
                delete this->_ptr;
                delete this->_count;
            }
        }
        this->_count = p._count;
        this->_ptr = p._ptr;
        return *this;
    }
    ~SmartPtr()
    {
        this->_count--;
        if (this->_count == 0)
        {
            delete _ptr;
            delete _count;
        }
    }
    T &operator*()
    {
        assert(this->_ptr != nullptr);

        return this->_ptr;
    }
    T *operator->()
    {
        assert(this->_ptr != nullptr);
        
        return this->_ptr;
    }
    T *get()
    {
        return this->_ptr;
    }
    size_t use_count()
    {
        return *this->_count;
    }
};

class MyClass
{
private:
    int _n;

public:
    MyClass(int n) : _n(n) {}
    MyClass(const MyClass &myclass)
    {
        if (this != &myclass)
        {
            this->_n = myclass._n;
        }
    }
    MyClass &operator=(const MyClass& myclass)
    {
        if (this != &myclass)
        {
            this->_n = myclass._n;
            return *this;
        }
        return *this;
    }
    int getN()
    {
        return this->_n;
    }
};
int main()
{
    int a = 2;
    SmartPtr<int> p(&a);
    cout << p.use_count() << endl;
    cout << *(p.get()) << endl;
    MyClass *m = new MyClass(1);
    SmartPtr<MyClass> mp(m);
    cout << mp->getN() <<endl;
    return 0;
}