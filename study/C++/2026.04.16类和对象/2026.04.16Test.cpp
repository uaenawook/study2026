#include<iostream>

// 在 C++ 中结构体升级成类，并且支持原来C的类
// 在 C++ 中struct结构体内访问权限默认是public
struct ListC
{
	//// C里 struct list是类型
	//int a;
	//struct Stack* next;
	
	// C++里 list 就是类型
	int a;
	ListC* next;
};

// 类用class定义，类内默认访问权限是 private(私有的)
// public 到下一个权限截止，或者到}截止
class ListCPP
{
public:
	void StackInit()
	{

	}
private:
	// 一般变量是私有，并且用 _ 区分
	int _a;
	ListCPP* _next;

};


// class Date
struct Date
{
public:
	//当你调用 d1.Init(2026, 4, 16); 时，编译器实际上把它转换成了类似这样的形式：
	//Init(&d1, 2026, 4, 16);
	//而在成员函数内部，你写的 _year = year; ，实际上被编译器补全成了：
	//this->_year = year;

	void Init(int year, int month, int day) 
	{
		this->_year = year;
		_month = month;
		_day = day;
	}
	void Init2(int year, int month, int day);

	//private:
		// 为了区分成员变量，一般习惯上成员变量
		// 会加一个特殊标识，如_ 或者 m开头
		// 声明
	int _year; // year_ m_year
	int _month;
	int _day;
};

void Date::Init2(int year, int month, int day)
{
	// 不能写 Date::_year = year;
	// 也不能写 Date::this->_year = year;
	// 老老实实在 Init 前加 Date::
	_year = year;
	_month = month;
	_day = day;
}

//int main()
//{
//	Date d2;
//	Date d3;
//
//	d2.Init(2024, 7, 9);
//
//	struct Date d1;
//
//	ListCPP node;
//
//	//Date::_year = 2024; // 类的声明不能被修改
//
//
//	return 0;
//}