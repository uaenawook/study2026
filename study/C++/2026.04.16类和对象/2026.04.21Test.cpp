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

	// 2026.4.22
	// 对象拷贝时编译器的优化？
	/*
		
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

//#include<iostream>
//using namespace std;
//class A
//{
//private:
//	static int _k;
//	//int _h = 1;
//public:
//	class B // B默认就是A的友元​
//	{
//	public:
//		void foo(const A& a)
//		{
//			cout << _k << endl; //OK
//			//cout << a._h << endl; //OK
//		}
//		int _b1;
//	};
//};
//int A::_k = 1;
//int main()
//{
//	cout << sizeof(A) << endl;
//	//A::B b;
//	//A aa;
//	//b.foo(aa);
//	return 0;
//}


#include<iostream>
using namespace std;
class A
{
public:
	A(int a = 0) // 默认构造函数 Default ctor
		:_a1(a)
	{
		cout << "A(int a)" << endl;
	}
	A(const A& aa)
		:_a1(aa._a1) // 拷贝构造函数 copy ctor
	{
		cout << "A(const A& aa)" << endl;
	}
	A& operator=(const A& aa) // 赋值运算符重载函数  Assignment Operator Overloading
	{
		cout << "A& operator=(const A& aa)" << endl;
		if (this != &aa)
		{
			_a1 = aa._a1;
		}
		return *this;
	}
	~A() // 析构函数 Destructor
	{
		cout << "~A()" << endl;
	}
private:
		int _a1 = 1;
};
void f1(A aa)
{}
A f2()
{
	A aa;
	return aa;
}
int main()
{
	//// 传值传参​
	A aa1; // 默认构造
	//cout << "*****" << endl;
	f1(aa1); // 拷贝构造临时变量 + 函数结束后 析构临时变量
	cout << "*****" << endl;
	cout << endl; 
	////return 0; // 执行return 前，析构aa1


	// 如果不考虑编译器优化
	// 1被隐式类型转换为A ，需要构造临时匿名对象，调用一次默认构造
	// 1作为值被传递给f1(aa), 值传递调用拷贝构造，A 临时匿名对象 拷贝构造 aa,调用一次拷贝构造
	// f1()函数结束，析构 aa,调用一次析构
	// f1(1);调用函数结束，析构临时匿名对象，调用一次析构
	// -----
	// 编译器优化后，把临时对象优化了，直接用1构造aa，过程中 调用一次默认构造、一次析构
	//f1(1); 

	// 构造匿名对象，匿名对象直接拷贝构造aa，aa析构，匿名对象析构
	// 期间不存在 匿名的临时对象，因为A(2) 与 aa的类型时匹配的，传参直接调用拷贝构造，临时对象的产生一般发生在 类型转换和 函数返回值。
	//f1(A(2)); 

	//cout << endl;
	//cout << "***********************************************" << endl;



	// 传值返回​
	// 不优化的情况下传值返回，编译器会生成一个拷贝返回对象的临时对象作为函数调用表达式的返回值​
	// 无优化 （vs2019 debug）​
	// 一些编译器会优化得更厉害，将构造的局部对象和拷贝构造的临时对象优化为直接构造（vs2022 debug）​
	// 构造aa,拷贝构造临时对象，析构aa，析构临时对象
	//f2();
	//cout << endl;

	// 返回时一个表达式中，连续拷贝构造+拷贝构造->优化一个拷贝构造 （vs2019 debug）​
	// 一些编译器会优化得更厉害，进行跨行合并优化，将构造的局部对象aa和拷贝的临时对象和接收返回值对象aa2优化为一个直接构造。（vs2022 debug）​
	// 构造aa,拷贝构造临时对象，析构aa，拷贝构造aa2，析构临时对象，析构aa2
	//A aa2 = f2();
	//cout << endl;
	 
	 
	// 一个表达式中，开始构造，中间拷贝构造+赋值重载->无法优化（vs2019 debug）​
	// 一些编译器会优化得更厉害，进行跨行合并优化，将构造的局部对象aa和拷贝临时对象合并为一个直接构造（vs2022 debug）​
	// 默认构造aa,aa拷贝构造临时对象，aa析构，临时对象 赋值重载 aa1，临时对象析构，aa1析构
	aa1 = f2();
	cout << endl;
	return 0;
}