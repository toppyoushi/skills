
# 今天在尝试下方虚函数表地址访问代码时遇到的问题

``` //cpp
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

```

1. typedef void （*Fun)()函数指针语法不会，查阅博客得知这是定义返回类型为void，形式参数为空的函数指针Fun
2. 对指针b的类型转换，```Fun b1fun = (Fun)(*(size_t *)*(size_t *)b);```该语句从右向左，首先将指针b转化为size_t型得到虚函数表中第一个虚函数的地址，再进行一次相同的转换得到该虚函数的函数指针，指针的加减操作是和其所指类型相关的，+1操作得到的是下一个函数指针的地址，网上的博客使用的是int而不是size_t，主要是32位系统与64位系统间的差别，在我自己电脑上如果使用int需要+2，说明64位系统中指针大小为8字节而32位系统为4字节
注意：虚函数表位于c++内存模型的只读数据段，虚函数位于代码段，验证方法见这个博客:https://blog.csdn.net/qq_28114615/article/details/98041319
3. 父类的指针即使指向子类实例是无法访问任何非重载父类成员函数的自有成员函数的，会被编译器报错，但是通过对虚函数表的访问，可以做到

引用：数据类型 & 引用名 = 被引用变量
为变量建立引用相当于给它取别名，且必须初始化，与某一变量绑定，引用不是独立数据类型，也不会为其创建内存空间，而是与被绑定的变量存入同一内存？
在程序中声明了b是a的引用，实际上在内存中开辟了一个指针型的储存单元，在其中放变量a的地址，输出引用b时，就输出b所指向的变量a的值，相当于*b.引用其实就是一个指针变量，它的指针不能改变，只能指向一个指定的变量。所以引用的本质还是指针。
这两句话来自同一篇博客，WTF   明白了，引用不会为其指向的变量分配空间，但不代表引用本身不占空间，引用本身占一个指针的内存空间
不能声明引用数组，可以声明数组引用
引用作为函数返回值：当函数的返回值不是一个变量的引用时，一定会创建一个临时变量，返回变量的引用，避免在内存中产生返回值的副本
引用做返回值应遵守的规则：

- 不能返回局部变量的引用，因为函数体结束变量就被销毁了
- 不能返回函数内部new分配的内存的引用。虽然不存在局部变量的被动销毁问题，可对于这种情况（返回函数内部new分配内存的引用），又面临其它尴尬局面。例如，被函数返回的引用只是作为一 个临时变量出现，而没有被赋予一个实际的变量，那么这个引用所指向的空间（由new分配）就无法释放，造成memory leak。
- 可以返回类成员的引用，但最好是const

常引用：左侧加const，常引用只能get不能set
引用与指针的异同：

1. 相同点：底层的实现都是指针
2. 不同点：
    - 引用必须初始化，指针可以只声明
    - 引用一旦与某一变量绑定，就不能再与另一变量建立引用
    - 引用不能为NULL，指针可以为NULL
    - 对引用sizeof，得到的是其所引用的变量类型的字节大小，而对指针sizeof得到的是固定值32位为4字节，64位为8字节
    - 引用自加后是对被引用值自加，而指针自加是指向某个该指针类型的空间
    - 没有多级引用，有多级指针
    - 指针手动寻址，引用编译器寻址

# C++ 重载

1. 函数重载

## 定义

函数重载指在同一作用域，一组含有不同形参列表的同名函数，没有返回值不同这一条件，主要是为了在解析时不依赖于上下文

``` //cpp
float sqrt(float);
double sqrt(double);

void f(double da, float fla)
{
      float fl=sqrt(da);//调用sqrt(double)
      double d=sqrt(da);//调用sqrt(double)

      fl=sqrt(fla);//调用sqrt(float)
   d=sqrt(fla);//调用sqrt(float)
}
```

同一作用域主要体现在类的函数重载

## 为什么要用函数重载

- 许多功能相似而仅仅是参数不同的函数，需要不断取不同名字会非常不友好
- 类的构造函数与类名完全相同，如果不进行构造函数的重载，不能做到多种方法实例化对象
- 运算符重载实际上就是一种函数重载

## 编译器的解析

编译器将重载函数解析为命名空间+返回值+函数名+形参

## 重载函数调用时如何正确地匹配

判断规则:

- 精准匹配：不对参数类型转换或只做很细微的转换，如数组名转指针，函数名转函数指针，非const转const
- 提升匹配：整数提升，bool到int，char到int，short到int，float到double
- 使用标准转换匹配： 如int到double，double到int，Derived\*到Base\*，T \*到void \*,int到unsigned int
- 省略号匹配

# c++中数组名与指针的区别与联系

数组名与指针是不同的，其中一个体现就是对数组名和指针使用sizeof()运算符得到的结果不同，数组名不能进行自加和自减操作，而指针可以。
可以将数组名理解成一种指针常量（并不代表是），数组名可以转化为指针

``` //cpp
#include <iostream>
using namespace std;
void Fun(int a[])
{
    cout<<sizeof(a)<<endl;          //自动将将数组名转化为指针类型
}
int main()
{
    int a[5] = {1, 2, 3, 4, 5};
    int *ptr = (int *)(&a+1);       //可以讲数组名a看做int[]类型，对其取地址，就是取一个int[]型结构的地址（指针），
    ptr--;                          //对地址自加得到下一个int[]的地址，再转换成int型指针，自减后得到数组最后一个元素
    cout<<*(ptr)<<endl;
    Fun(a);
    return 0;
}
```

# C++强制类型转换

强制类型转换发生在赋值、数学表达式等情况下，当运算符的操作数类型不同时，C++会将操作数转换为同一数据类型

---

## 数据类型排名

能够容纳更大数值的类型排名较高，具体如下（从左至右为从高到低）:  
long double > double >float > unsigned long long int > long long int > long int > unsigned int > int

`当long int 与 int大小相同时，即32位系统时，unsigned int > long int，因为它能表示的数据更大`

规则

- char, short, unsigned short自动升级为int，意味着任何时候获取这些数据类型的值，都会自动转换为int
- 当操作数不一样时，自动将排名较低的数据转换为排名较高的数据
- 为变量赋值时，数据值会被转化为该变量数据类型，如果此时是降级转换，会造成部分数据的丢失从而得到不准确的结果

C++类型转换表达式：

``` \\cpp
    static_cast<datatype>(value) /相关类型转换
    reinterpret_cast<datatype>(value) //无关类型转换
    const_cast<datatype>(value) //删除const属性的转换
    dynamic_cast<datatype>(value) //用于将一类父类对象的指针转换为子类对象的指针或引用
```

C++ 重载、覆盖与重定义区别  

| 重载 | 同一作用域内 | 函数名相同、形参的类型、个数不同 |
| :----: | :----: | :----: |
| 覆盖 | 分别位于基类与派生类 | 函数名相同、形参类型、个数相同，返回值相同 |
| 重定义 | 分别位于基类与派生类 | 函数名相同就构成重定义 |

## dynamic_cast 动态类型转换

dynamic_cast 用于将父类对象的指针转换为子类对象的指针或引用（动态转换）  
将子类对象指针转换为父类指针可直接用切片完成，但父类对象转换为子类对象则不安全，  
dynamic_cast会先检查能否转换成功，能转换则转换，不能转换则返回0，*dynamic_cast只能用于含有虚函数的类*

```dynamic_cast<type*>(e)```能够转换成功的三种情况：  

1. e的类型是type类型的共有派生类：派生类转基类一定能成功
2. e的类型是type类型的基类，但是指向的是派生类的对象，或者基类引用引用派生类对象，如果e指向的是基类对象，则转换不能成功
3. e的类型就是个type类型，一定能够转换成功

``` \\cpp
#include<iostream>
using namespace std;

class Person{
protected:
    string _name;
	virtual void Print()
	{
		cout << "I am the father" << endl;
	}
};

class Student :public Person
{
public:
	int _num;
	virtual void Print()
	{
		cout << "I am the son" << endl;
	}
};
void Func(Person* p)
{
	//父类对象指针->子类指针/引用
	Student* sp = dynamic_cast<Student*>(p);//只允许子类对象指针转换
	sp->Print();
}
int main()
{
	Person p;
	Student s;
	//Func(&p);//使用dynamic_cast，不能将父类指针转换成子类指针，防止了越界行为
	Func(&s);
	return 0;
}
```

# C++各种类型与0的比较

1. bool值

```\\cpp
    bool flag = true
    if(flag)
    if(!flag)
```

2. int,long,short等整型

```\\cpp
    int i = 1;
    if(i == 0)
    if(i != 0)
```

3. float,double等浮点型

```\\cpp
    #define EPSILON 0.000000000001
    float flag = 1.0;
    if ( flag < EPSILON && flag > -EPSILON)
```

4. 判断两浮点数是否相等
```
    #define EPSILON 0.000000000001
    float a = 2.1, b = 1.0;
    if((a-b)<EPSILON && (a-b)>-EPSILON)
```

5. 指针
```
    int *ptr = new int(5);
    if(ptr == NULL)
    if(ptr != NULL)
```

# C++深拷贝与浅拷贝


# C++重载

