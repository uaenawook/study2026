
/*
	函数模板
		（为什么）为什么设计模板？
			因为在编码时一个函数可能要处理多个类型的数据，而处理多个类型就要写多个函数
			有了模板，把类型设计成模板，有编译器自动生成对应类型的函数代码，更方便使用
		（是什么）什么是模板
			可以更通用的东西，一个函数模板可以创造很多不同类型的函数
		（怎么办）怎么使用——关键字、格式、等
		关键字 template、typename、class
	类模板

	string
		底层是什么
		有哪些接口
		怎么使用
*/
#include<iostream>
using namespace std;

//
////template<typename T>
//template<class T>
//void Swap(T& x,T& y)
//{
//	T tmp = x;
//	x = y;
//	y = tmp;
//}
//
////template<class X>
////X Add(const X& m, const X& n)
////{
////	return m + n;
////}
//
//
//
//
//int main()
//{
//	/*int a = 10;
//	int b = 20;
//	cout << a <<" " << b << endl;
//	Swap(a, b);
//	cout << a << " " << b << endl;
//	cout << "************" << endl;
//
//	double m = 1.1;
//	double n = 2.2;
//	cout << m << " " << n << endl;
//	Swap(m,n);
//	cout << m << " " << n << endl;
//	cout << "************" << endl;
//
//	char x = 'x';
//	char y = 'y';
//	cout << x << " " << y << endl;
//	Swap(x, y);
//	cout << x << " " << y << endl;
//	cout << "************" << endl;*/
//
//
//	//int a = 10;
//	//double b = 20.0;
//	//// 显式实例化
//	//cout << Add<int>(a, b) << endl;
//
//	return 0;
//}


//
//// 专门处理int的加法函数
//int Add(int left, int right)
//{
//	return left + right;
//}
//// 通用加法函数
//template<class T>
//T Add(T left, T right)
//{
//	return left + right;
//}
//void Test()
//{
//	Add(1, 2); // 与非模板函数匹配，编译器不需要特化
//	Add<int>(1, 2); // 调用编译器特化的Add版本
//}
//
//int main()
//{
//	Test();
//
//	return 0;
//}

#include<iostream>
using namespace std;


// 类模版
template<typename T>
class Stack
{
public:
	Stack(size_t capacity = 4)
	{
		_array = new T[capacity];
		_capacity = capacity;
		_size = 0;
	}
	void Push(const T& data);
private:
	T* _array;
	size_t _capacity;
	size_t _size;
};

// 模版不建议声明和定义分离到两个文件.h 和.cpp会出现链接错误，具体原因后面会讲
template<class T>
void Stack<T>::Push(const T& data)
{
	// 扩容
	_array[_size] = data;
	++_size;
}


int main()
{
	Stack<int> st1; // int
	Stack<double> st2; // double
	return 0;
}