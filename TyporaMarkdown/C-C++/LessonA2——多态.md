# 多态

## 概念

**多种形态**

本质：不同的人做同一件事 会产生不同的效果、结果不同。

举栗子：比如**买票这个行为**，当**普通人**买票时，是全价买票；**学生**买票时，是半价买票；**军人**买票时是优
先买票。  



## 构成条件

1.必须通过基类的指针或引用调用虚函数

2.内调用的函数必须是虚函数，且派生类必须对基类的虚函数进行重写。

**指针或引用 + 三同(函数名、参数、返回值)虚函数**

> **//构成多态，穿的哪个类型的对象，调用的就是这个类型的虚函数。——跟传来的对象有关**
> **//不构成非多态，跟P的类型有关。——跟P的类型有关，跟传过来的对象无关**

```c++
//多态：多种形态
//静态的多态：函数重载 ，同一个函数有不同的行为。静态：编译时
//动态的多态：一个父类对象的引用或指针调用同一个函数，传递不同的对象。会调用不同的函数。动态：
//本质：不同的人做同一件事 会产生不同的效果、结果不同。
// 
class Person {
public:
	virtual void BuyTicket() { cout << "买票-全价" << endl; }
};
class Student : public Person {
public:
	//子类中满足三同(函数名、参数、返回值)的虚函数，叫做重写(覆盖)
	virtual void BuyTicket() { cout << "买票-半价" << endl; }
};
//构成多态，穿的哪个类型的对象，调用的就是这个类型的虚函数。——跟传来的对象有关
//不构成非多态，跟P的类型有关。——跟P的类型有关，跟传过来的对象无关
void Func(Person& p) //不是指针或引用则不是多态，则调用Person
{
	p.BuyTicket(); //多态
}

int main()
{
	Person ps;
	Student st;
	Func(ps);
	Func(st); //切片传递
	return 0;
}
```

### 虚函数

虚函数的关键字：virtual

类的非静态函数，才能定义成虚函数，其他函数不能成为虚函数。

```C++
class Person {
public:
	virtual void BuyTicket() { cout << "买票-全价" << endl; }
};
```

### 重写

子类中满足三同(**函数名、参数、返回值**)的**虚函数**，叫做重写(覆盖)

#### 特例

**==重写要求返回值必须相同，协变例外==**

##### 1.协变(基类与派生类虚函数返回值类型不同)  

 要求返回值是父子关系的指针或引用

```c++
class A {};
class B : public A {};

class Person {
public:
	//virtual A* BuyTicket() { cout << "买票-全价" << endl;  return nullptr; } // 多态
	virtual Person* BuyTicket() { cout << "买票-全价" << endl;  return nullptr; } // 多态
};
class Student : public Person {
public:
	//子类中满足三同(函数名、参数、返回值)的虚函数，叫做重写(覆盖)
	//virtual B* BuyTicket() { cout << "买票-半价" << endl; return nullptr; }  // 多态
	virtual Student* BuyTicket() { cout << "买票-半价" << endl; return nullptr; }  // 多态
};

/*注意：在重写基类虚函数时，派生类的虚函数在不加virtual关键字时，虽然也可以构成重写(因为继承后
基类的虚函数被继承下来了在派生类依旧保持虚函数属性),但是该种写法不是很规范，不建议这样使用*/
/*void BuyTicket() { cout << "买票-半价" << endl; }*/


//构成多态，跟传的类型有关
//不构成非多态，跟P的类型有关。
void Func(Person& p)
{
	p.BuyTicket(); //多态
}

int main()
{
	Person ps;
	Student st;
	Func(ps);
	Func(st); //切片传递
	return 0;
}
```

#### 析构函数的重写  

析构函数是虚函数，是否构成重写？ 构成

析构函数名被特殊处理了，处理成了destructor

```c++
class Person {
public:
    //有virtual 则能正常调用，没有则不能
	virtual ~Person() { cout << "~Person()" << endl; }
};
class Student : public Person {
public:
	virtual ~Student() { cout << "~Student()" << endl; }
};

void Func(Person& p)
{
	//p.BuyTicket(); //多态
}

int main()
{
	//普通对象 析构函数是否虚函数，是否完成重写，都正确调用了
	//Person ps;
	//Student st;
			//~Student()
			//~Person()
			//~Person()
	Person* p1 = new Person; // operator new + 构造函数
	Person* p2 = new Student; //多态
    Student* p2 = new Student; // 不是多态 有没有virtual都能正确调用析构
	//析构函数 + operator delete
	//				p1->destructor();
	delete p1;	
	delete p2;
	//				p1->destructor();
    
    		//有virtual
    			//~Person()
				//~Student()
				//~Person()
    		//无virtual
    			//~Person()
				//~Person()
    
    
    
	return 0;
}
```

### 继承virtual

**父子的virtual不建议不写 ==建议全写==**

父亲写了virtual，子类没写，也够成虚函数。

```c++
class Person {
public:
	virtual Person* BuyTicket() { cout << "买票-全价" << endl;  return nullptr; } // 多态

};
class Student : public Person {
    Student* BuyTicket() { cout << "买票-半价" << endl; return nullptr; }//私有的也算虚继承，只重写了内容
public:

	//子类没写virtual，但是他是先继承了父类的虚函数的属性，在完成重写，那么也算虚函数
	Student* BuyTicket() { cout << "买票-半价" << endl; return nullptr; }  // 多态
};
```

本质上，子类重写的虚构函数，可以不加virtual是因为析构函数，是因为，父亲析构函数加上virtual，而子类忘记加，那么就不构成多态，没调用子类的析构函数，造成该内存泄漏。

### 为什么？

为什么多态的条件必须是基类的指针和引用：既可以传父类，也可以传子类

### C++11关键字

#### final

想让一个类不能被继承

```c++
class A final
{};
```

修饰虚函数，在父类添加，实现子类中禁止重写

```
class B
{
public:
	viraual void f() final
	{cout << "C::f()" << endl;}
};
class C :public B
{
public:
	viraual void f()
	{cout << "C::f()" << endl;}
};
```

### override

放在子类重写的虚函数的后面，检查是否完成重写

没重写就会报错

```c++
class Car{
public:
	virtual void Drive()
	{}
};
class Benz :public Car {
public:
	virtual void Drive() override
    {cout << "Benz-舒适" << endl;}
};
```

### 重载、覆盖、隐藏的对比

|            | 重载                            | 重写(覆盖)                                       | 重定义(隐藏)                                       |
| ---------- | ------------------------------- | ------------------------------------------------ | -------------------------------------------------- |
| **作用域** | 两个函数在不同作用域            | 两个函数分别在基类金额派生类的作用域             | 两个函数分别在基类和派生类的作用域                 |
| **函数**   | ==函数、参数不同== 返回值没要求 | 函数名、返回值、参数都必须相同(协变类外)==三同== | 函数名相同                                         |
| **补充**   | —                               | 两个函数必须是==虚函数==                         | 像个基类和派生类的同名函数==不构成重写就是重定义== |

## 抽象类

**包含纯虚函数的类**叫做抽象类(接口类) 抽象类不能实例化出对象。派生类继承后也不能实力出对象。只有重写纯虚函数，派生类才能实例化对象

==在虚函数的后面写上 =0==  

```c++
class Car
{
public:
	virtual void Drive() = 0;
};
```

虚函数可以实现代码，但没价值，生成解决方案 可以调用的到，但是运行会报错

### 理解

抽象——现实世界没有对应的实物

一个类型，如果一般在限时世界中，没有具体的对应实物就定义成抽象类比较好。

### 作用

纯虚函数的类，本质上强制的子类去完成虚函数得重写

override知识在语法上检查是否完成重写

## 多态的原理

### 虚函数表

```c++
// 这里常考一道笔试题：sizeof(Base)是多少？
class Base
{
public:
    virtual void Func1()
    {
        cout << "Func1()" << endl;
    }
private:
	int _b = 1;
    int
};
int main()
{
    cout << sizeof(Base) << endl; //12
    return 0;
}
```

多出来的4字节是 虚函数表的指针

![image-20220809233343218](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/imageimage-20220809233343218.png)

### 虚函数表指针

简称：虚表指针

是什么：虚表指针 是指针数组的指针

表本质是一个==数组==



### 为什么多态必须要基类的指针或引用呢？

因为：

#### 虚表指针如何运行？

```c++
class Person {
public:
	virtual Person* BuyTicket() { cout << "买票-全价" << endl;  return nullptr; } // 多态
private:
	int _a = 0;
};
class Student : public Person {
public:
	virtual Student* BuyTicket() { cout << "买票-半价" << endl; return nullptr; }  // 多态
private:
	int _a = 0;
};
void Func(Person& p)
{
	p.BuyTicket(); //多态
}

int main()
{
	Person a;
	Student b;
	Func(a);
	Func(b); //切片传递
}
```

因为有了多态，所以 a和b会找到自己对应的虚表

![image-20220810000225742](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/imageimage-20220810000225742.png)

![image-20220810000526830](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/imageimage-20220810000526830.png)

#### 原因：

普通对象不能传递虚表指针，传递过程中虚表指针会因为拷贝而被修改，而指针和引用是切片传递，不会进行拷贝。

```c++
int main()
{
	Person a;
	Student b;
	Func(a);
	Func(b); //切片传递

	Person& c = b;
	Person d = b;
}
```

![image-20220810002015893](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/imageimage-20220810002015893.png)

**可以看到 C、D都赋值成了B ，而普通对象D的虚表指针 没继承B的。**

此时也就说明 ，在函数传递形成多态时，如果传对象的过程中，父子对象的虚表 会被生成新的虚表，那么多态就找不到 父子的对应的虚函数，也就不能完成多态。
如果是指针或引用则不会出现此情况，因为指针指向了对象，指针传递不会改变，引用是对象的别名，也不会改变

#### 同类型对象虚表指针相同

![image-20220810003259732](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/imageimage-20220810003259732.png)

#### 存储位置

普通函数和虚函数的存储位置一样吗？

一样，都是存在代码段，只是虚函数要把地址存到虚表，多态的时候找，方便实现多态。

#### 确定地址的时间(主要看是不是多态)

多态调用，在编译时，不能确定调用的是哪个函数。

是多态，则运行时，去p指向的对象的许表中找到虚函数的地址。

不是多态，编译时就会确定地址。

## 虚表的继承

```
class Base
{
public:
	virtual void Func1()
	{
		cout << "Base::Func1()" << endl;
	}

	virtual void Func2()
	{
		cout << "Base::Func2()" << endl;
	}

	//void Func3()
	//{
	//	cout << "Base::Func3()" << endl;
	//}

private:
	int _b = 1;
};

class Derive : public Base
{
public:
	virtual void Func1()
	{
		cout << "Derive::Func1()" << endl;
	}

	//virtual void Func4()
	//{
	//	cout << "Derive::Func4()" << endl;
	//}
private:
	int _d = 2;
};

int main()
{
	Base b;
	Derive d;
	
	Base* p1 = &b;
	p1->Func1();
	p1 = &d;
	p1->Func1();
	
	return 0;
}
```

![image-20220810010355409](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/imageimage-20220810010355409.png)

---

假如 class A 有fun1、fun2

class B 有fun1(重写) 、fun3

虚表继承后，派生类B的虚表指针是不同的 指向不同的虚表，虚表中 重写的fun1 地址会修改，而继承的fun2的地址和基类的相同，  fun3也在虚表里，但是在vs监视窗口看不到，内存可看。(下图)

![image-20220810010648688](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/imageimage-20220810010648688.png)

---

**==而虚表中存的也不是 函数的地址，而是跳转地址==**，再跳一层才会到函数的第一句指令的地址。(下图)

**红线指向的顺序，是说明了虚表中存储的并不是函数的地址，而是跳转的地址，通过跳转再找到函数的地址红线指向的顺序，是说明了虚表中存储的并不是函数的地址，而是跳转的地址，通过跳转再找到函数的地址**

![image-20220810012259128](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/imageimage-20220810012259128.png)

#### 虚表存在哪里？

表存在常量区和代码段之间  ==更接近常量区==

表指针存在栈上

#### 多继承的虚函数表

```c++
class Base1 {
public:
	virtual void func1() { cout << "Base1::func1" << endl; }
	virtual void func2() { cout << "Base1::func2" << endl; }
private:
	int b1;
};
class Base2 {
public:
	virtual void func1() { cout << "Base2::func1" << endl; }
	virtual void func2() { cout << "Base2::func2" << endl; }
private:
	int b2;
};
class Derive : public Base1, public Base2 {
public:
	virtual void func1() { cout << "Derive::func1" << endl; }
	virtual void func3() { cout << "Derive::func3" << endl; }
private:
	int d1;
};

int main()
{
	Derive d;

	Base1* p1 = &d;
	p1->func1();

	Base2* p2 = &d;
	p2->func1();

	return 0;
}
```

##### fun3的继承

d的虚表有俩张，而fun3会存在第一张虚表中，也就是先继承的那张虚表，第二张虚表没fun3

##### 继承的fun1地址不同？

虽然继承的fun1地址不同，但是这只是jump的地址，==最后会跳转到同一个地址==

![image-20220810014313391](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/imageimage-20220810014313391.png)

**总结：**多继承时，子类重写了Base1和Base2寻函数fun1，但是许表中重写的fun1的地址不一样。但是没关系，他们最终调到的还是同一个函数

---

第二个许表中的fun1 要跳转多次，主要是因为，Base2继承后的切片位置的修正。(如图)

![image-20220810015218825](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/imageimage-20220810015218825.png)

### 重写关系

当ABCD， BC继承A，D继承BC，构成菱形继承后。 A中的F1在BC中重写后，必须在D中也重写，因为如果不重写，将会有歧义

## 接口继承

虚函数重写时，继承父类的虚函数接口，也就是函数、返回值、参数，重写的是虚函数的实现。

```c++
class A
{
public:
	virtual void func(int val = 1){std::cout<<"A->"<<val<<std::endl;}
};
class B:public A
{
public:
	void func(int val = 0){std::cout<<"B->"<<val<<std::endl;}
};
```

也就是说此时如果形成多态，而B调用B的dunc时，val的缺省值是父类继承下来的，而不是自己的，只有实现才是按照自己写的调用。

# 问答

## 1.什么是多态

多态分为静态多态、动态多态

### 静态多态

静态：编译时

函数重载（调用时传不同的参数

函数名的修饰规则（参数不同

### 动态多态

动态：运行时

运行时去虚标找，指针指向谁就找到谁

## 2.什么是重载、重写、重定义



## 3.多态实现的原理



## 4.inline函数可以是虚函数吗

**内联函数**的特点是在调用的地方展开、函数没有地址、 

可以，不过编译器就忽略inline属性，这个函数就不再是inline，因为虚函数要放到虚表中 

## 5.静态成员函数可以是虚函数吗

不能，因为静态成员函数没有this指针，使用类型::成员函数的调用方式无法访问到虚函数表，所以静态成员函数无法放进虚函数表

## 6.构造函数可以是虚函数吗

不可以

虚函数的地址放在虚表

虚表指针构造函数初始化列表初始化

虚函数重写多态的条件之一



虚函数的指针在构造函数的初始化列表初始化，而如果构造函数可以是虚函数，也找不到虚函数的地址，因为构造函数还没初始化这个指向虚表的指针，所以构造函数是虚函数没有意义

### 6.1拷贝构造和赋值函数，能不能是虚函数

赋值可以，最好不要

拷贝不可以

## 7.析构函数可以是虚函数吗？

可以，做好是把基类的析构函数定义成虚函数

## 8.对象访问普通函数快，还是虚函数更快

首先是普通对象是一样的

如果是指针对象或者引用的对象，则调用的普通函数快，因为构成多态，运行时调用虚函数需要到虚表中查找

## 9.虚函数是在什么阶段生成的，存在那

虚表是在编译阶段生成，存在代码段

### 9.1虚表指针呢？

虚表指针是在构造函数初始化阶段生成

## 10.C++菱形继承问题，虚继承的原理

虚函数表：虚函数的地址，实现多态

虚基表：存的是偏移量，解决数据冗余和二义性



## 11.什么是抽象类，抽象类的作用
