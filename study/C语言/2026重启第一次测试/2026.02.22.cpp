#define _CRT_SECURE_NO_WARNINGS 0

#include <iostream>
using namespace std;
//int main()
//{
//	std::cout << "hello world!" << std::endl;
//	return 0;
//}
// 
// 
// 
// 域
//namespace bit
//{
//	int rand = 10;
//}
//
//int a = 0;
//
//int main()
//{
//	printf("%p\n", rand);
//	printf("%p\n", bit::rand);
//	printf("%d\n", bit::rand);
//
//	int a = 1;
//	printf("%d\n", a);
//
//	// ::域作用限定符
//	printf("%d\n",::a);
//
//	return 0;
//}
// 
// 
// 
//#include <stdio.h>
//#include <stdlib.h>
//namespace bit
//{
//	// 鹏哥
//	namespace pg
//	{
//		int rand = 1;
//		int Add(int left, int right)
//		{
//		return left + right;
//		}
//	}
//
//	// 杭哥
//	namespace hg
//	{
//		int rand = 2;
//		int Add(int left, int right)
//		{
//			return (left + right) * 10;
//		}
//	}
//}
//
//int main()
//{
//	printf("%d\n", bit::pg::rand);
//	printf("%d\n", bit::hg::rand);
//
//
//	return 0;
//}


 //test.cpp
//#include"Queue.h"
#include"Stack.h"

//// 全局定义了一份单独的Stack
//typedef struct Stack
//{
//	int a[10];
//	int top;
//}ST;
//void STInit(ST* ps) {}
//void STPush(ST* ps, int x) {}
//
//int main()
//{
//	// 调用全局的
//	ST st1;
//	STInit(&st1);
//	STPush(&st1, 1);
//	STPush(&st1, 2);
//	printf("%d\n", sizeof(st1));
//
//	// 调用bit namespace的
//	bit::ST st2;
//	printf("%d\n", sizeof(st2));
//	bit::STInit(&st2, 4);
//	bit::STPush(&st2, 1);
//	bit::STPush(&st2, 2);
//
//	return 0;
//}


#include<iostream>
using namespace std;

//int main()
//{
//	//int i = 1234;
//	//int j = -1234;
//	////std::cout << i << endl;
//	//cout << i << endl;
//
//	int a = 0;
//	double b = 0.1;
//	char c = 'x';
//
//	cout << a << "             " << b << " " << c << "\n" << '\n' << endl;
//	std::cout << a << " " << b << " " << c << std::endl;
//
//	scanf("%d%lf", &a, &b);
//	printf("%d %lf\n", a, b);
//
//	// 可以自动识别变量的类型
//	//cin >> a;
//	//cin >> b >> c;
//	cin >>a>> b >> c;
//	cout << a << endl;
//	cout << b << " " << c << endl;
//
//	return 0;
//}

//int main()
//{
//	int a = 0;
//	double b = 0.1;
//	char c = 'x';
//	cin >> a >> b >> c;
//	cout << a << ' ' << b << ' ' << c << endl;
//	return 0;
//}