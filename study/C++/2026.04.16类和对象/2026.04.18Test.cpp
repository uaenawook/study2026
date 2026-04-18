#include<iostream>
using namespace std;
//
// 引用返回，局部对象引用返回，局部对象传值返回，谁会调用拷贝对象，谁会消失
// 成员函数指针 

// 拷贝构造 和 复制重载 什么区别
// 复制重载什么时候调用，拷贝构造什么时候调用

// 运算符重载关键字，哪些符号不能重载
// 私有关键字 
// 复习课件


class Stack
{

};
// 写、不写引用 有什么区别？
// Stack st;何时销毁，何时被拷贝
Stack func2()
{
	Stack st;
	return st;
}

int main()
{
	Stack ret = func2();
	return 0;
}


//class A
//{
//public:
//	void func()
//	{
//		cout << "A::func()" << endl;
//	}
//};
//
//typedef void(A::*PF)(); //成员函数指针类型
//
//int main()
//{
//	// void(A::*pf)() = nullptr;
//	PF pf = nullptr;
//	// C++规定成员函数要加&才能取到函数指针
//
//	pf = &A::func;
//	A aa;
//	(aa.*pf)();
//}