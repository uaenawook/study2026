## 类与对象(上)

面向过程 - 体现在实现的过程
面向对象 - 体现在 用户 与用户的关系
C语言面向过程 
C++面向过程和面向对象 因为兼容C
java面向过程

## 类：
```c
class Person //类定义的对象
{
public://访问限定符
//成员函数
void PrintPersonInfo();
private:
//成员变量
char _name[20];
char _gender[3];
int _age;
};
```
**在C中有 struct 定义的结构体**
```c
    在C++ 中兼容C 但是已经升级为类
    并且默认访问 是public(公有) 
    而且在结构体中可以定义成员函数 并且调用
    
    struct Stucent
    {
    	//成员变量
    	char _name[10];
    	int _age;
    	int _id;
    	//成员函数
    	void Init(const char* name, int age, int id)
    	{
    		strcpy(_name, name);
    		_age = age;
    		_id = id;
    	}
    	void Print()
    	{
    		cout << _name << endl;
    		cout << _age << endl;
    		cout << _id << endl;
    	}
    };
    int main()
    {
    	//struct Stucent s1; //兼容C
    	Stucent s2;			//升级到类，Stucent类名，也是类型
    	strcpy(s2._name, "李四");
    	s2._id = 1;
    	s2._age = 18;
    	s2.Init("张三",18, 1);
    	s2.Print();
    	return 0;
    }
```
**在C++中用class 定义类**
```c
class Stucent
{
public:

	//成员变量
	char _name[10];
	int _age;
	int _id;
	//成员函数
	void Init(const char* name, int age, int id)
	{
		strcpy(_name, name);
		_age = age;
		_id = id;
	}
private:  //以下是私有
	void Print()
	{
		cout << _name << endl;
		cout << _age << endl;
		cout << _id << endl;
	}
};
int main()
{
	Stucent s2;			//升级到类，Stucent类名，也是类型
	strcpy(s2._name, "李四");
	s2._id = 1;
	s2._age = 18;
	s2.Init("张三",18, 1);
	s2.Print();
}
```

**面向对象的三大特性：封装、继承、多态。**
```c
    默认访问限定符是private(私有)
    访问限定符：
        public 公有
        protected 保护
        private 私有
```
**作用域**

    访问限定符的作用域 遇到下一个限定符结束  或者类的底部结束
    
**类的实例化**

    用类名定义的 变量 - 称之为 类实例化的对象


**C++类中的成员对象 也就是C结构体中的变量**
**类对象的大小**

    类中有两种对象  - 成员变量 、成员函数
    存储方式 是 实例化对象字存储成员变量、成员函数放在公共代码区
        因为 成员函数 是相同的 没必要多处拷贝

```c
// 类中既有成员变量，又有成员函数
class A1 {
public:
void f1(){}
private:
int _a;
};
// 类中仅有成员函数
class A2 {
public:
void f2() {}
};
// 类中什么都没有---空类
class A3
{};

sizeof(A1) : __4___ sizeof(A2) : __1___ sizeof(A3) : ___1__
```
**类的大小也需要空间对齐，规则与结构体相同**
**类无变量时 用一个字符标识这个类，存了一个地址**


# 类与对象（中）
&emsp;&emsp;六个默认成员函数：构造函数、析构函数、拷贝构造函数、赋值运算符重载
## 构造函数
&emsp;&emsp;在实例化对象时初始化用的函数，我们自己写了，编译器会调用我们写的，我们不写，编译器会自动生成。对于内置类型成员变量不处理，对于自定义类型成员变量调用它的默认构造函数。
```c
class Date
{
    构造函数 要与定义的类名一致
    1.Date() {}; 不能传参
    2.Date(int a,int b){};必须传参
    3.Date(int a = 0,int b = 0){}; 不传参用缺省值，传参用形参
    
    4.Date(capacaty)//对于栈的初始化
    {
        Stack* ret = (Stack*)malloc(sizeof(Stack)*capacaty)
        _capacaty = capacaty;
    }
};
```
## 析构函数
&emsp;&emsp;用于清理对象中的资源，如果独享需要资源，才需要自己实现析构函数，析构函数在函数生命周期到了，自动调用。内置类型不处理，自定义类型调用它的析构函数。
```c
1.对于malloc的对象需要自己定义析构函数
class Stack
{
    int*a;
    int _val;
};
2.对于日期类对象不需要自己定义析构函数
class Date
{
    int _year;
    int _month;
};
```
## 拷贝构造函数
&emsp;&emsp;使用同类型的对象去初始化对象，我们不写，编译器自动生成。
&emsp;&emsp;自动生成
&emsp;&emsp;&emsp;&emsp;1.内置类型完成按字节序的拷贝 - 浅拷贝  对于指针的拷贝会把指针的地址拷贝过去，造成新初始化的对象与原对象指向同一块空间。
&emsp;&emsp;&emsp;&emsp;2.自定义类型的成员变量，调用它的拷贝构造。
```c
1.对于日期类，可以不写，浅拷贝够用
Date(const Date& d) 需要注意这里传引用，不然会死循环调用拷贝构造
{
    _year = d._year;
    _month = d._month;
    _day = d._day;
}

2.对于栈类，需要拷贝构造，因为有指针

3.对于以下，不需要，因为会调用它的拷贝构造
class MyQueue
{
    Stack _pushST;
    Stack _popST;
}
```
## 运算符重载
&emsp;&emsp;关键字：返回值类型`operator`操作符(参数列表)
&emsp;&emsp;自定义类型不支持运算符使用，所以需要自己写
&emsp;&emsp;不能被重载的运算符（5个）：`.*`、`::`、`sizeof`、`?:`、`.`
```c
大于操作符，用引用是为了防止原始数据被改，并可以减少拷贝构造的调用
class Date
{
public:
    bool Date::operator>(const Date& d)
    {
        if(_year>d._year)
            return true;
        else if(_year==d._year && _month>d._month)
            return true;
        else if(_year==d._year && _month==d._month && _day>d._day)
            return true;
        else
            return false;
    }
private:
    int _year;
    int _month;
    int _day;
}

调用：
int mian()
{
    d1 > d2; //d1.operator>(d2)
}
说明：、
如果operator 与main在一个.cpp中 则可以 operator>(d1,d2);这样调用
如果：1.operator>在类中，则字默认增加隐藏参数 this  
    2.所以要减少一个参数，this 就是d1 
    
运算符重载 调用顺序，先去成员函数找，再去全局找
```
## 赋值重载
&emsp;&emsp; 两个已经存在的对象之间 赋值
```c
    Date d1(2022,4,17);
    Date d3(2022,5,23);
    对刚创建的值进行初始化 - 拷贝构造
    Date d4(d1);
    Date d5 = d1;
    
    两个已经存在的对象之间 赋值 - 赋值拷贝
    d1 = d3;
```
&emsp;&emsp;**赋值运算符的返回值应该是d1**
```c
int i,j,k;
j = i = k = 10;
//k = 10的返回值是k
```
```c
赋值运算符的实现
Date& operator=(const Date& d)
{
优化：自己个自己赋值 判断一下
    if(this != &d)
    {
        _year = d.year;
        _month = d.month;
        _day = d.day;
    }
    return *this;
}
因为 函数调用结束，d1还存在，所以用引用返回，可以减少拷贝构造


```
##### 梳理
赋值重载、拷贝构造、构造函数、析构函数分别是干嘛用的？
1.赋值重载：给两个已经存在的对象进行复制，在这期间会产生临时拷贝，所以会调用拷贝构造，为了减少拷贝构造，参数用了引用参数，因为赋值运算要有返回值作为右值，所以需要返回this参数，，为了减少拷贝构造，返回参数用了引用返回。
2.拷贝构造：用来对刚创建的对象进行赋值，也用于函数传参，临时拷贝用
3.构造函数：用于初始化新建的类，一般会用缺省参数，便于创建对象时的赋值。
4.析构函数：对对象的清理

赋值重载和拷贝构造 代码基本一致
构造函数和析构函数 代码基本一致
**以上函数都是 编译器自动调用，不写时自动产生。**
- **+= 与运算符重载**
&emsp;&emsp;直接将天数加到 day上 当day小于这个月应该有的天数则结束 返回，如果大于当月天数，则day-当月天数 ，然后进位月份，月份++，当月份>12时 重置为1，年++;
&emsp;&emsp;+=是给自身加  比如i=5;i+=10; 则i = 15;
```c
Date& Date::operator+=(int day)
{
	_day += day;
	while (_day > GetMonthDay(_year, _month))
	{
		_day -= GetMonthDay(_year, _month);
		_month++;
		if (_month == 13)
		{
			_month = 1;
			_year++;
		}
	}
	return *this;
}
```
- **日期+天数**
&emsp;&emsp;天数相加 ，+运算符不会改变自身，例如：i= 5; ret = i+10; 最后i还是5  ret是15;，所以这里为了不改变this 先用ret代替*this，在改变ret  返回ret ，又因为ret出函数销毁，所以不能用引用返回，用临时变量（调用拷贝构造，拷贝临时变量）返回
```c
Date Date::operator+(int day)
{
	Date ret = *this;
	ret += day;
	return ret;
}
```
- **前置++**
&emsp;&emsp;前置++ 直接加就可以了 返回原来的值，因为原来的值出作用域补销毁，所以用引用返回。
&emsp;&emsp;前置++ 不会进行拷贝 ，建议用前置++
Date& Date::operator++()
{
	*this += 1;
	return *this;
}
- **后置++**
&emsp;&emsp;后置++ 为了与前置++区分 多给一个参数int  传什么值不重要
Date Date::operator++(int)
{
	Date ret = (*this);
	*this + 1;
	return ret;
}

**析构 在同一个生命周期里 先创建的后析构**

推荐图书《深度探索C++对象模型》