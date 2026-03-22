#include<iostream>
using namespace std;

void func1(int& x)
{
	x++;
}

//int& func2()
//{}

int main()
{
	int a = 10;
	// 编译报错：“ra”: 必须初始化引用
	//int& ra;

	func1(a);
	cout << a << endl;

	int& b = a;
	int& c = b;

	int d = 20;
	b = d;

	cout << &a << endl;
	cout << a << endl;
	cout << &b << endl;
	cout << b << endl;
	cout << &d << endl;
	cout << d << endl;

	return 0;
}