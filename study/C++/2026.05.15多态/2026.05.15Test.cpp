#include<iostream>

using namespace std;
//
//class A
//{
//public:
//	~A()
//	{
//		cout << "~A()" << endl;
//	}
//};
//
//class B : public A 
//{
//public:
//	~B()
//	{
//		cout << "~B()->delete:" << _p << endl;
//		delete _p;
//	}
//protected:
//	int* _p = new int[10];
//};
//// 只有派⽣类Student的析构函数重写了Person的析构函数，下⾯的delete对象调⽤析构函数，才能
////构成多态，才能保证p1和p2指向的对象正确的调⽤析构函数。
//int main()
//{
//	// 调用两次~A没问题吗？？？？？？？？？？？？？？？？
//	A* p1 = new A;
//	A* p2 = new B;
//
//	delete p1;
//	delete p2;
//	return 0;
//}

class Base
{
protected:
	int _b = 1;
	char _ch = 'x';
public :
	virtual void Func1()
	{
		cout << "Func1()" << endl;
	}

};
int main()
{
	Base b;
	cout << sizeof(b) << endl;
	return 0;
}
