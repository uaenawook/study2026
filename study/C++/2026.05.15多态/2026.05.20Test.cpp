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
class Base {
public:
	void func(int) { cout << "Base int" << endl; }
	void func(double) { cout << "Base double" << endl; }
};

class Derived : public Base {
public:
	// 隐藏父类的所有func函数
	void func(string) { cout << "Derived string" << endl; }
};

// 作用2：替代基类功能
class Animal {
public:
	void eat() { cout << "吃草" << endl; }
};

class Cat : public Animal {
public:
	// 隐藏eat()，实现自己的eat
	void eat() { cout << "吃鱼" << endl; }
};
// 作用3：防止误调用
// 父类有多个重载函数
// 子类只想要部分功能时，可以通过隐藏只保留需要的版本

// 使用：
int main()
{
	Derived d;
	//d.func(10);      // ❌ 错误！隐藏后无法调用父类的func(int)
	d.func("abc");   // ✓ 调用Derived的func(string)
	return 0;
}


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




