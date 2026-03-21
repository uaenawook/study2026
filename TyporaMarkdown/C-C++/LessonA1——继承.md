# 继承

## 继承的概念及定义

继承机制是面向对象程序设计**使代码可以复用**的最重要的手段

| 类成员/继承方式      | public继承             | protected继承          | private继承          |
| -------------------- | ---------------------- | ---------------------- | -------------------- |
| 基类的public成员     | 派生类的public成员     | 派生类的protected成 员 | 派生类的private成 员 |
| 基类的protected成 员 | 派生类的protected成 员 | 派生类的protected成 员 | 派生类的private成 员 |
| 基类的private成员    | 在派生类中不可见       | 在派生类中不可见       | 在派生类中不可见     |

### 命名：

父类/基类

子类/派生类

### 继承关系

|           |                                                     |
| --------- | --------------------------------------------------- |
| public    | 父子 类内外都可用                                   |
| protected | 父子 类内可以用，父子类外不可用，下一层可以继承     |
| private   | 父 类内可以用，父类外和其他不可用，下一层不可以继承 |

### 常见的继承使用：

父类成员：公有和保护

子类继承方式：公有继承

### 不写访问限定符

struct 默认公有、class默认私有

#### 不写继承方式

struct 默认公有、class默认私有，按照 public > protected > private 取最小的使用

## 赋值兼容规则

### 切片/切割(公有继承)

**【私有继承】则不可以切割，可能存在权限的转换。**(在子类继承方式中是私有的，在父类中可能是公有，则会发生权限的放大，不支持)

#### 子 给 父 

```c++
class Person// 父
{
public:
	void print()
	{
		cout << "name:" << _name << endl;
		cout << "age:" << _age << endl;
	}
	int _ss;
protected:
	string _name = "peter";
	int _age = 18;
private:
	int _aa;

};

struct Student :  public Person   //子类
{
public:
	void f()
	{
		print();
	}
protected:
	int _stuid;//学号
};
int main()
{
	Person p;
	Student s;

	//父类 = 子类赋值兼容 -> 切片 切割  (公有继承可用)
    //这里不是类型转换，是无法天然的支持行为 ，转换时不产生临时变量
	p = s;
	Person* ptr = &s;  //指向切片的部分
	Person& ref = s;   //指向切片的部分

	return 0;
}
```

**把 子类中继承父类 的成员  切割出来赋值给父类，至于子类中多余的成员被切割掉了  不赋值。**

#### 父 给 子

不可以，但是指针和引用可以，小心用可能会发生越界访问

```c++
class Person
{
public:
	void print()
	{
		cout << "name:" << _name << endl;
		cout << "age:" << _age << endl;
		
	}
	int _ss;
protected:
	string _name = "peter";
	int _age = 18;
private:
	int _aa;
};
struct Student : public Person
{
public:
	void f()
    {}
protected:
	int _stuid;//学号
public:
	int _No;
};

//子类 = 父类
int main()
{
	Person p;
	Student s;
	//子类 = 父类
	//s = p;//不可以
	//但是指针和引用可以，小心用可能会发生越界访问
	Student* pptr = (Student*)&p;
	Student& rref = (Student&)p;
	
    //危险的，存在越界访问的风险
	pptr->_No = 1;

	return 0;
}
```

## 继承中的作用域

在父子作用域中 可以有相同的变量名，优先局部，访问父类 需要指定作用域

子类和父类出现同名成员，称为：**隐藏/重定义**



```c++
class Person
{
protected:
	string _name = "小花";
	int _num = 111;
};
class Student :public Person
{
public:
	void Print()
	{
		cout << " 姓名：" << _name << endl; //小花
		cout << _num << endl;//999
		cout << Person::_num << endl;//111
	}
protected:
	int _num = 999;
};


int main()
{
	Student s;
	s.Print();
	return 0;
}
```

**成员函数只要函数相同就构成隐藏，与参数无关。**

不建议 设置重名成员

```c++
class A
{
protected:
	void fun()
	{
		cout << "fun()" <<endl;
	}
}
class B:public A
{
public:
	void fun(int a)
	{
		cout <<"fun(int a)"<<endl;
	}
protected:
	int _num = 999;
};


int main()
{
	Student s;
	s.fun(1);
	s.fun(); //被隐藏了调用不了
	s.A::fun();
	return 0;
}
```

**我们不写默认生成的派生的构造和析构？** 
a、父类继承下来得 (调用父类默认构造和析构处理)  b、自己的（内置类型和自定义类型成员）(跟普通类一样)
**我们不写默认生成的拷贝构造和operator=？**
a、父类继承下来得 (调用父类拷贝构造和operator=) b、自己的（内置类型和自定义类型成员）(跟普通类一样：内置不处理，或完成浅拷贝。自定义类型调用自定义类型的拷贝和赋值)

**总结**：原则，继承下来调用父类处理，自己的按普通类基本规则。

**什么情况下必须自己写？**
1、父类没有默认构造，需要我们自己显示写构造
2、如果子类有资源需要释放，就需要自己显示写析构
3、如果子类存在浅拷贝问题，就需要自己实现拷贝构造和赋值解决浅拷贝问题

 **如果我们要自己写怎么办？如何自己写？**
父类成员调用父类的对应构造、拷贝构造、operator=和析构处理
自己成员按普通类处理。

```c++
Student(const char* name = "张三",int num = 1)
	:Person(name)
	,_num(num)
{}
//s2(s1)
Student(cont Student& s)
	:Person(s) //父类调用父类的值(切片) 拷贝   s1的父类部分初始化s2的父类部分
	,_num(s._num)
{}

```

**析构函数，不用自己调用**

子类析构结函数束时，会自动调用父类的析构函数

这样才能保证析构自雷成员，在析构父类成员

如果自己显示的写析构，会重复析构两次。

## 继承与友元

友元关系不能继承

父类的友元就是父类的友元，子类不能继承

## 继承与静态成员

基类定义了static静态成员，则整个继承体系里面只有一个这样的成员  

## 复杂的菱形继承及菱形虚拟继承  

菱形继承 会出现数据冗余和二义性

```c++
							class Person
class student :public Person				class tencher :public Person
			class Assistant:public student ,public Teacher 
						
```

此时，学生和教师类中都有 姓名，那么 Assistant访问谁的name呢？

出现二义性如何解决？（指定类域）

```c++
Assistant a;
a.Student::_name = "张三";
a.Teacher::_name = "李四";
```

### 虚继承

如何解决数据冗余？（virtual  ）

当Person中有一个4w字节的数组，Assistant会继承8w字节

```c++
class Person
{};
class Student :virtual public Person
{};
class Teacher :virtual public Person
{};
class Assistant : public student ,public Teacher 
```

先继承的在内存中存在前面 ，后继承的存在后面 、

```
class A
{
public:
	int _a;
};

//class B : public A
class B : virtual public A
{
public:
	int _b;
};

//class C : public A
class C : virtual public A
{
public:
	int _c;
};

class D : public B, public C
{
public:
	int _d;
};

int main()
{
	D d;
	d.B::_a = 1;
	d.C::_a = 2;
	d._b = 3;
	d._c = 4;
	d._d = 5;
	d._a = 0;

	return 0;
}
```

![image-20220804165628876](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/imageimage-20220804165628876.png)

先继承的B，所以B的成员在前面。 公共的在最后，要找到公共的通过偏移量来计算

![image-20220804170005780](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/imageimage-20220804170005780.png)

菱形继承的虚继承位置

![image-20220806174023736](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/imageimage-20220806174023736.png)



## 继承的总结和反思  

C++缺陷：没有垃圾回收器、菱形继承



### 继承和组合

[优先使用对象组合，而不是类继承](https://www.cnblogs.com/nexiyi/archive/2013/06/16/3138568.html)

#### 继承

public继承是一种**is-a**的关系。也就是说每个派生类对象都是一个基类对象  

B就是A

白箱复用：基类的内部细节对子类可见**(派生类和基类间的依赖关系很强，耦合度高)**

```c++
class A	//person
{	int _a; };
class B: public A	//Student
{	int _b; };
B可以直接访问A的公有和保护成员
```

#### 组合(优先)

组合是一种**has-a**的关系。假设B组合了A，每个B对象中都有一个A对象  

D里面有C

黑箱复用：对象内部细节不可见**(组合类之间没有很强的依赖关系，耦合度低)**

```c++
class C //眼睛
{	int _c; };
class D  //头
{
	C _c;//复用
    int _d;
};
D只能访问C的公有，不能直接访问成员
```

### 低耦合 高内聚

低耦合： (类似旅游的自由团，自由度高，自己的行程不会影响别人)

**高内聚**：类内部的成员关联关系紧密，依赖度高，关联不紧密的少。

**低耦合**：类和类之间的关系若 ，两个类之间的关联少。

**关联关系越弱越好，当一个位置崩溃不会影响其他位置。**

### 组合这么好，直接用组合，抛弃继承语法可以吗？不可以

多态是建立在继承的基础上的 

