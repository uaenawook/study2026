#define _CRT_SECURE_NO_WARNINGS 1

#include"func.h"
namespace wx
{
	int a = 10;

	namespace wx
	{
		int c = 30;
	}
}


namespace wx
{
	int b = 20;



}

// 函数重载：参数个数不同、或者类型不同可以重载
// C不支持同名函数
void f1(int a, int b)
{

}
void f1(char a, int b)
{

}
void f1(int a)
{

}
// 返回值不同不能作为重载条件，因为调用时也无法区分​
//void fxx()
//{}
//
//int fxx()
//{
// return 0;
//}
//int main()
//{
//	printf("%d ", wx::a);
//	printf("%d ", wx::b);
//	printf("%d ", wx::wx::c);
//
//	//int c = wx::func(10);
//	//printf("%d ", c);
//
//	int a = 10;
//	int& b = a;
//	int& c = b;
//	int d = 200;
//	int& e = d;
//	b = d;
//	c = 10;
//	cout << a << endl;
//	cout << c << endl;
//
//
//	int a1;
//	double a2;
//	short a3;
//	char a4;
//	cin >> a1 >> a2 >> a3 >> a4;
//	cout << a1 <<" " << a2 << " " << a3 << " " << a4 << " " << endl;
//	scanf("%d %lf %hd %c", &a1, &a2, &a3, &a4);
//	cout << a1 << " " << a2 << " " << a3 << " " << a4 << " " << endl;
//
//	return 0;
//}


//void Swap(int& rx, int& ry)
//{
//	int tmp = rx;
//	rx = ry;
//	ry = tmp;
//}
//int main()
//{
//	int x = 0, y = 1;
//	cout << x << " " << y << endl;
//	Swap(x, y);
//	cout << x << " " << y << endl;
//	return 0;
//}

//typedef int STDataType;
//typedef struct Stack
//{
//	STDataType* a;
//	int top;
//	int capacity;
//}ST;
//void STInit(ST& rs, int n = 4)
//{
//	rs.a = (STDataType*)malloc(n * sizeof(STDataType));
//	rs.top = 0;
//	rs.capacity = n;
//}
//// 栈顶
//void STPush(ST& rs, STDataType x)
//{
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
//	return rs.a[rs.top-1];
//}
//int main()
//{
//	// 调用全局的
//	ST st1;
//	STInit(st1);
//	STPush(st1, 1);
//	STPush(st1, 2);
//	cout << STTop(st1) << endl;
//	STTop(st1) += 10;
//	cout << STTop(st1) << endl;
//	return 0;
//}



int main()
{
	int a = 10;
	const int& ra = 30;
	// 编译报错: “初始化”: 无法从“int”转换为“int &”​
	// int& rb = a * 3;
	const int& rb = a * 3;
	double d = 12.34;
	// 编译报错：“初始化”: 无法从“double”转换为“int &”​
	// int& rd = d;
	const int& rd = d;

	// 当int&被const修饰，所接收的例如a*3产生的临时结果，会被编译器在栈上分配空间，让rb指向这个空间
	// const修饰后临时变量的声明周期从 ; 延长到了rb的生命周期
	// 正常a*3的结果存在寄存器中，拷贝给被赋值的对象后就消失了。临时变量的生命周期在包含它的完整表达式结束处（通常是遇到分号 ; 时） 就会被销毁。
	return 0;
}