#include<iostream>
using namespace std;


// 按照课件：类和对象下复习
	/*
		初始化列表
			1. 定义对象 D d1;不传参，此时y、m、d默认值是2
							传参，此时y、m、d会接收传来的参数如（2024,4,21）
			2. 初始化列表写了_y(y),则y的值是2或者2024，就会把值传给_y
			3. 初始化列表没写_d(d),则_d不会接收d的值，会去声明找缺省值
								如果声明时写了 int _d = 1; 则_d被初始化为1
								如果声明没写缺省值 int _d; 则_d为垃圾值
			4.在{ }里写的 _y = y;这是赋值，而不是初始化
								按下面的例子，初始化只写了 _y(y),_m(m) 则进入 {} 前 _y、_m、_d 就被写入了 2024、2、垃圾值。
			5.初始化时是按照 变量声明的顺序进行的，而不是初始化列表显示写的顺序进行

		类型转换
			Time A = 1; 1会被隐式类型转换为Time再赋值给A，函数前加explicit，则不会形成隐式类型转换
		static成员
			变量必须在类外初始化，类的大小不包含静态变量，静态变量生命周期在全局，但受类的访问限定符限制
			静态成员函数没有this指针，可以访问静态变量，但不成访问非静态变量
				非静态成员函数可以访问 静态变量和静态函数
		友元
			友元函数可以声明在类内任何地方，不受访问限定符限制
			友元声明是单向的，没有传递性
			一个函数可以是多个类的友元
			关键字：friend
		内部类
			内部类默认是外部的友元，class	A { class B{} } B默认能访问A的成员变量和函数
		匿名对象
			生命周期只有一行，用作临时对象
	*/

// 初始化列表


//class D
//{
//public:
//	/* 初始化列表：
//		1. 定义对象 D d1;不传参，此时y、m、d默认值是2
//						传参，此时y、m、d会接收传来的参数如（2024,4,21）
//		2. 初始化列表写了_y(y),则y的值是2或者2024，就会把值传给_y
//		3. 初始化列表没写_d(d),则_d不会接收d的值，会去声明找缺省值
//							如果声明时写了 int _d = 1; 则_d被初始化为1
//							如果声明没写缺省值 int _d; 则_d为垃圾值
//		4.在{ }里写的 _y = y;这是赋值，而不是初始化
//							按下面的例子，初始化只写了 _y(y),_m(m) 则进入 {} 前 _y、_m、_d 就被写入了 2024、2、垃圾值。
//		5.初始化时是按照 变量声明的顺序进行的，而不是初始化列表显示写的顺序进行																	
//	*/
//	D(int y = 2 ,int m = 2,int d = 2)
//		:_y(y)
//		, _m(m)
//	{
//		//_y = y;
//		//_m = m;
//		//_d = d;
//	}
//
//	void print()
//	{
//		cout << _y << "-" << _m << "-" << _d << endl;
//	}
//
//private:
//	int _y = 1;
//	int _m = 1;
//	int _d;
//};
//
//int main()
//{
//	D d1(2024); //不传参时 必须不能写括号()，不然会被判断成函数
//	d1.print(); 
//	return 0;
//}

//#include<iostream>
//using namespace std;
//class Time
//{
//public:
//	Time(int hour)
//		:_hour(hour)
//	{
//		cout << "Time()" << endl;
//	}
//	void Print() const
//	{
//		cout <<_hour << endl;
//	}
//private:
//	int _hour;
//};
//class Date
//{
//public:
//	Date(int& x, int year = 1, int month = 1, int day = 1)
//		:_year(year)
//		, _month(month)
//		, _day(day)
//		, _t(12)
//		, _ref(x)
//		, _n(1)
//	{
//		// error C2512: “Time”: 没有合适的默认构造函数可用​
//		// error C2530 : “Date::_ref” : 必须初始化引用​
//		// error C2789 : “Date::_n” : 必须初始化常量限定类型的对象​
//	}
//	void Print() const
//	{
//		cout << _year << "-" << _month << "-" << _day << endl;
//	}
//private:
//	int _year;
//	int _month;
//	int _day;
//	Time _t; // 没有默认构造​
//	int& _ref; // 引用​
//	const int _n; // const
//};
//int main()
//{
//	//int i = 0;
//	//Date d1(i);
//	//d1.Print();
//
//
//	// 1构造一个A的临时对象，再用这个临时对象拷贝构造aa3​
//	// 编译器遇到连续构造+拷贝构造->优化为直接构造​
//	Time aa1 = 1;
//	aa1.Print();
//	return 0;
//}

#include<iostream>
using namespace std;
class A
{
private:
	static int _k;
	//int _h = 1;
public:
	class B // B默认就是A的友元​
	{
	public:
		void foo(const A& a)
		{
			cout << _k << endl; //OK
			//cout << a._h << endl; //OK
		}
		int _b1;
	};
};
int A::_k = 1;
int main()
{
	cout << sizeof(A) << endl;
	//A::B b;
	//A aa;
	//b.foo(aa);
	return 0;
}