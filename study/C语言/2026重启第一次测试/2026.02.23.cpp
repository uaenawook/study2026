//#include <iostream>
//using namespace std;
//int main()
//{
//	double d = 2.22222222;
//	printf("%.2lf\n", d);
//	cout << d << endl;
//	cout << &d << endl;
//
//	return 0;
//}

//#include<iostream>
//using namespace std;
//
//int main()
//{
//	// 在io需求比较高的地方，如部分大量输入的竞赛题中，加上以下3行代码
//	// 可以提高C++IO效率
//	ios_base::sync_with_stdio(false);
//	cin.tie(nullptr);
//	cout.tie(nullptr);
//
//	return 0;
//}

//#include <iostream>
//using namespace std;
//
//void Func(int a = 0)
//{
//	cout << a << endl;
//}
//
//// 全缺省
//void Func1(int a = 10, int b = 20, int c = 30)
//{
//	cout << "a = " << a << endl;
//	cout << "b = " << b << endl;
//	cout << "c = " << c << endl << endl;
//}
//
//// 半缺省
//void Func2(int a, int b = 10, int c = 20)
//{
//	cout << "a = " << a << endl;
//	cout << "b = " << b << endl;
//	cout << "c = " << c << endl << endl;
//}
//
//int main()
//{
//	Func(); // 没有传参时，使用参数的默认值
//	Func(10); // 传参时，使用指定的实参
//
//	Func1();
//	Func1(1);
//	Func1(1, 2);
//	Func1(1, 2, 3);
//
//	//Func2();
//	Func2(100);
//	Func2(100, 200);
//	Func2(100, 200, 300);
//
//	return 0;
//}

//#include<iostream>
//using namespace std;
//
//#include"Stack.h"
//
//int main()
//{
//	bit::ST s1;
//	bit::STInit(&s1);
//
//	// 确定知道要插入1000个数据，初始化时一把开好，避免扩容
//	bit::ST s2;
//	bit::STInit(&s2, 1000);
//
//	for (size_t i = 0; i < 1000; i++)
//	{
//		bit::STPush(&s2, i);
//	}
//
//	return 0;
//}
//
//
//
//#include<iostream>
//using namespace std;
//
//// 1、参数类型不同
//int Add(int left, int right)
//{
//	cout << "int Add(int left, int right)" << endl;
//	return left + right;
//}
//
//double Add(double left, double right)
//{
//	cout << "double Add(double left, double right)" << endl;
//	return left + right;
//}
//
//void Swap(int* px, int* py)
//{}
//
//void Swap(double* px, double* py)
//{}
//
//// 2、参数个数不同
//void f()
//{
//	cout << "f()" << endl;
//}
//void f(int a)
//{
//	cout << "f(int a)" << endl;
//}
//int main()
//{
//	f(10);
//	return 0;
//}
//// 3、参数类型顺序不同
//void f(int a, char b)
//{
//	cout << "f(int a,char b)" << endl;
//}
//
//void f(char b, int a)
//{
//	cout << "f(char b, int a)" << endl;
//}
//
// //下面两个函数构成重载
// //f()但是调用时，会报错，存在歧义，编译器不知道调用谁
//
//namespace bit1
//{
//	void f1()
//	{
//		cout << "f()" << endl;
//	}
//}
//
//
//void f1()
//{
//	cout << "f()" << endl;
//}
//
//void f1(int a = 10)
//{
//	cout << "f(int a)" << endl;
//}

 //返回值不同不能作为重载条件，因为调用时也无法区分
//void fxx()
//{}
//
//int fxx()
//{
//	return 0;
//}




#include<iostream>
#include<assert.h>
using namespace std;
//
//int main()
//{
//	int a = 0;
//	// 引用：b和c是a的别名
//	int& b = a;
//	int& c = a;
//
//	// 也可以给别名b取别名，d相当于还是a的别名
//	int& d = b;
//	//++d;
//
//	// 这里取地址我们看到是一样的
//	cout << &a << endl;
//	cout << &b << endl;
//	cout << &c << endl;
//	cout << &d << endl;
//	cout << a << endl;
//	return 0;
//}




//void Swap(int* px, int* py)
//{}
//
//typedef int STDataType;
//typedef struct Stack
//{
//	STDataType* a;
//	int top;
//	int capacity;
//}ST;
//
//void STInit(ST& rs, int n = 4)
//{
//	rs.a = (STDataType*)malloc(n * sizeof(STDataType));
//	rs.top = 0;
//	rs.capacity = n;
//}
//
//// 栈顶
//void STPush(ST& rs, STDataType x)
//{
//	//assert(ps);
//
//	// 满了， 扩容
//	if (rs.top == rs.capacity)
//	{
//		printf("扩容\n");
//		int newcapacity = rs.capacity == 0 ? 4 : rs.capacity * 2;
//		STDataType* tmp = (STDataType*)realloc(rs.a, newcapacity *
//			sizeof(STDataType));
//		if (tmp == NULL)
//		{
//			perror("realloc fail");
//			return;
//		}
//		rs.a = tmp;
//		rs.capacity = newcapacity;
//	}
//	rs.a[rs.top] = x;
//	rs.top++;
//}
//// int STTop(ST& rs)
//int& STTop(ST& rs)
//{
//	assert(rs.top > 0);
//	return rs.a[rs.top];
//}
//void Swap(int& rx, int& ry)
//{
//	int tmp = rx;
//	rx = ry;
//	ry = tmp;
//}
//void Swap1(int* rx, int* ry)
//{
//	int tmp = *rx;
//	*rx = *ry;
//	*ry = tmp;
//}
//int main()
//{
//	int x = 0, y = 1;
//	cout << x << " " << y << endl;
//	Swap1(&x, &y);
//
//	//Swap(x, y);
//	cout << x << " " << y << endl;
//
//
//	// 调用全局的
//	//ST st1;
//	//STInit(st1);
//	//STPush(st1, 1);
//	//STPush(st1, 2);
//
//	//cout << STTop(st1) << endl;
//
//	return 0;
//}
