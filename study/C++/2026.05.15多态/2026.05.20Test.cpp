#include<iostream>
using namespace std;



/*
	函数重载：
		1.在同一作用域下
		2.函数名相同
		3.参数类型、参数个数 不同就构成重载; 仅返回值不同不构成函数重载

	函数模板：
		同一个函数可以出传不同类型的值
*/

// 函数重载
//int add(const int& a, const int& b)
//{
//	return a + b;
//}
//
//double add(const double& a, const double& b)
//{
//	return a + b;
//}
//
//double add(const double& a, const int& b)
//{
//	return a + b;
//}
//
//int main()
//{
//	cout << add(3, 3) << endl;
//	cout << add(3.3, 3.3) << endl;
//	cout << add(3.3, 3) << endl;
//	return 0;
//}





// 函数模板
//template<class T>
//T func(const T& a, const T& b)
//{
//	return a + b;
//}
//
//int main()
//{
//	cout << func(1, 2) << endl;
//	cout << func(2.2, 4.4) << endl;
//
//	return 0;
//}

/*
	重写/覆盖 ：
		1.函数在父类和子类中同时存在
		2.函数名、参数类型、参数个数、返回值类型 必须相同
		3*.函数必须是虚函数
		4.重写后可以实现多态
		5.父类函数必须是virtual，子类可以不写
		6.重写和虚函数的关系
			- 父类不virtual->子类同名函数->隐藏
			- 父类virtual->子类同名函数->重写（多态）
	重载：
		1.函数在同一作用域
		2.函数名必须相同，参数类型、参数个数必须不同。仅返回值不同不构成重载
		3.重载后可以实现同一函数名传不同参数实现不同功能
		4.重载可以发生在类内或全局
		5.重写与作用域相关
	隐藏：
		1.函数在父类和子类中同时存在
		2.函数名相同，参数列表返回值可以相同或者不同
		3.隐藏后，可以隐藏掉父类继承来的函数， 隐藏的作用？？？？

*/
// 隐藏的作用
// 作用1：函数遮蔽（名字隐藏）
//		子类同名函数屏蔽父类的所有同名函数
//		即使参数不同，也无法直接访问父类版本
//class Base {
//public:
//	void func(int) { cout << "Base int" << endl; }
//	void func(double) { cout << "Base double" << endl; }
//};
//
//class Derived : public Base {
//public:
//	// 隐藏父类的所有func函数
//	void func(string) { cout << "Derived string" << endl; }
//};
//
//// 作用2：替代基类功能
//class Animal {
//public:
//	void eat() { cout << "吃草" << endl; }
//};
//
//class Cat : public Animal {
//public:
//	// 隐藏eat()，实现自己的eat
//	void eat() { cout << "吃鱼" << endl; }
//};
// 作用3：防止误调用
// 父类有多个重载函数
// 子类只想要部分功能时，可以通过隐藏只保留需要的版本

// 使用：
//int main()
//{
//	Derived d;
//	//d.func(10);      // ❌ 错误！隐藏后无法调用父类的func(int)
//	d.func("abc");   // ✓ 调用Derived的func(string)
//	return 0;
//}


/*
特性		|	重写			重载			隐藏
-----------------------------------------
位置		|	父子类		同作用域		父子类
函数名	|	相同			相同			相同
参数		|	相同			不同			相同或不同
virtual	|	需要			不需要		不需要
结果		|	多态			函数重载		父类函数不可见
*/



/*
	多态
		1.存在于父类和子类中
		2.函数必须是虚函数
		3.函数必须满足：返回值类型、参数类型和个数、函数名相同
		4.多态实现必须是父类的指针或者引用指向子类
		5.构成重写时 父亲必须写virtual，子类可以不写
		6.析构函数通常也设为virtual，防止内存泄漏
		7.调用方式：基类指针/引用->调用派生类函数
	
	override
		写在子类函数括号后
		用于判断子类函数是否构成多态
	final
		只能修饰虚函数
		写在类函数括号后
		用于限制父类的虚函数不被重写

*/

//class person
//{
//public:
//	virtual void func() { cout << "person func()" << endl; }
//};
//
//class student:public person
//{
//public:
//	virtual void func() { cout << "student func()" << endl; }
//};
//
//int main()
//{
//	student st;
//	person* pp = &st;
//	student* ps = &st;
//
//	pp->func();
//	ps->func();
//
//
//	person& py = st;
//	py.func();
//
//	return 0;
//}


//class A
//{
//	public :
//	virtual void func(int val = 1) { std::cout << "A->" << val << std::endl; }
//	//virtual void test() { func(); }
//	virtual void test() 
//	{ 
//		cout << typeid(this).name() << endl; //class A * 
//		cout << typeid(*this).name() << endl; //class B
//		func();
//		this->func();
//	}
//};
//class B : public A
//{
//	public :
//	void func(int val = 0) { std::cout << "B->" << val << std::endl; }
//};
//int main(int argc, char* argv[])
//{
//	B* p = new B;
//	p->test();
//	return 0;
//}
//
//class A
//{
//public:
//	virtual ~A()
//	{
//		cout << "~A()" << endl;
//	}
//	virtual void func() final
//	{
//		cout << "func()" << endl;
//	}
//};
//class B : public A {
//public:
//	~B() override
//	{
//		cout << "~B()->delete:" << _p << endl;
//		delete _p;
//	}
//	//virtual void func()
//	//{
//	//	cout << "func()" << endl;
//	//}
//protected:
//	int* _p = new int[10];
//};
//// 只有派⽣类Student的析构函数重写了Person的析构函数，下⾯的delete对象调⽤析构函数，才能
////构成多态，才能保证p1和p2指向的对象正确的调⽤析构函数。
//int main()
//{
//	A* p1 = new A;
//	A* p2 = new B;
//	delete p1;
//	delete p2;
//	return 0;
//}



//
//class Base
//{
//public:
//	virtual void Func1()
//	{
//		cout << "Func1()" << endl;
//	}
//protected:
//	int _b = 1;
//	char _ch = 'x';
//};
//int main()
//{
//	Base b;
//	cout << sizeof(b) << endl; //12 ,64位下 16
//	return 0;
//}

/*
	类型			|	32位			64位
	--------------------------------
	int			|	4			4
	long(linux)	|	4			8
	long(win)	|	4			4
	void*		|	4			8
	size_t		|	4			8
	long long	|	8			8
*/

//
//class Person {
//public:
//	virtual void BuyTicket() { cout << "买票-全价" << endl; }
//private:
//	string _name;
//};
//class Student : public Person {
//public:
//	virtual void BuyTicket() { cout << "买票-打折" << endl; }
//private:
//	string _id;
//};
//class Soldier : public Person {
//public:
//	virtual void BuyTicket() { cout << "买票-优先" << endl; }
//private:
//	string _codename;
//};
//void Func(Person* ptr)
//{
//	// 这⾥可以看到虽然都是Person指针Ptr在调⽤BuyTicket
//	// 但是跟ptr没关系，⽽是由ptr指向的对象决定的。
//	ptr->BuyTicket();
//} 
//int main()
//{
//	// 其次多态不仅仅发⽣在派⽣类对象之间，多个派⽣类继承基类，重写虚函数后
//	// 多态也会发⽣在多个派⽣类之间。
//	Person ps;
//	Student st;
//	Soldier sr;
//	Func(&ps);
//	Func(&st);
//	Func(&sr);
//	return 0;
//}
class Base {
public:
	virtual void func1() { cout << "Base::func1" << endl; }
	virtual void func2() { cout << "Base::func2" << endl; }
	void func5() { cout << "Base::func5" << endl; }
protected:
	int a = 1;
};
class Derive : public Base
{
public:
	// 重写基类的func1
	virtual void func1() { cout << "Derive::func1" << endl; }
	virtual void func3() { cout << "Derive::func1" << endl; }
	void func4() { cout << "Derive::func4" << endl; }
protected:
	int b = 2;
};
//int main()
//{
//	Base b; // &b的值的地址里 有两个值 + 00 00 00 00 ，也就是func1和func2
//	Derive d; // d的虚表有func3，需要去内存看 &d 的值，再进入这个值的地址，发现有三个地址和 00 00 00 00；
//	return 0;
//}
//
int main()
{
	int i = 0;
	static int j = 1;
	int* p1 = new int;
	const char* p2 = "xxxxxxxx";
	printf("栈:%p\n", &i);
	printf("静态区:%p\n", &j);
	printf("堆:%p\n", p1);
	printf("常量区:%p\n", p2);
	printf("栈:%p\n", &p2);
	Base b;
	Derive d;
	Base* p3 = &b;
	Derive* p4 = &d;
	printf("Person虚表地址:%p\n", *(int*)p3);
	printf("Student虚表地址:%p\n", *(int*)p4);
	printf("虚函数地址:%p\n", &Base::func1);
	printf("普通函数地址:%p\n", &Base::func5);
	return 0;
}
//
//#include <stdio.h>
//
//int main() {
//	const char* p2 = "xxxxxxxx";
//
//	// 1. 字符串内容所在的地址（只读数据区）
//	printf("字符串内容地址: %p\n", (void*)p2);
//
//	// 2. 指针变量p2本身的地址（栈上）
//	printf("指针变量p2地址: %p\n", (void*)&p2);
//
//	// 3. 打印字符串内容
//	printf("字符串内容: %s\n", p2);
//
//	// 4. 验证是否只读（尝试修改会报错）
//	// p2[0] = 'y';  // 取消注释会导致段错误（Segmentation Fault）
//
//	return 0;
//}

/*

高地址
┌─────────────────────┐  ↑
│   内核空间           │  │
├─────────────────────┤
│   命令行参数/env     │  │
│   内存映射区         │  │ (mmap区域，动态库等)
│   (共享库等)         │  │
├─────────────────────┤
│   栈 (Stack)         │  │  向下增长
│   ┌───────────────┐  │
│   │ 局部变量       │  │
│   │ 函数参数       │  │
│   │ 返回地址       │  │
│   └───────────────┘  │
├─────────────────────┤
│   堆 (Heap)          │  │  向上增长
│   ┌───────────────┐  │
│   │ malloc/new    │  │
│   └───────────────┘  │
├─────────────────────┤
│   .bss 段            │  │ 未初始化全局/静态变量
│   .data 段           │  │ 已初始化全局/静态变量
├─────────────────────┤
│   .rodata 段         │  │ 常量（字符串字面量、const）
├─────────────────────┤
│   .text 段           │  │ 代码/指令
├─────────────────────┤
│   内核空间           │
低地址



字符串 "hello"
┌──────────────────────────────────┐
│ .rodata (常量区，只读)             │
│  ┌───┬───┬───┬───┬───┬───┐       │
│  │ h │ e │ l │ l │ o │ \0│       │  ← 只有一份，多个指针共享
│  └───┴───┴───┴───┴───┴───┘       │
│            ↑                      │
│         const char* s1            │
│         char* s3                  │
│         char* s4                  │
└──────────────────────────────────┘

char s2[] = "world"
┌──────────────────────────────────┐
│  栈 (Stack)                       │
│  ┌───┬───┬───┬───┬───┬───┐       │
│  │ w │ o │ r │ l │ d │ \0│       │  ← 独立副本，可修改
│  └───┴───┴───┴───┴───┴───┘       │
│            ↑                      │
│           s2                      │
└──────────────────────────────────┘

*/