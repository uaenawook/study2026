#include<iostream>
using namespace std;

// 模板
// 模板的非类型参数，一般传参用T T可能是int double 等，或者传vector<T> ,list<T>等
// 非类型参数是用一个常量作为模板参数

//template <class T,size_t N>
template <class T,size_t N = 10>
class A
{
public:
//private:
	T arr[N];
	size_t size;
};
//int main()
//{
//
//	//A<double,10> a;
//	A<double> a;
//	a.arr[0] = 10;
//	cout << a.arr[0] << endl;
//	cout << sizeof(a.arr) << endl;
//
//	return 0;
//}

// 模板的特化
// 1. 函数模板

template<class T>
bool Less(T left, T right)
{
	return left < right;
}
template<>
bool Less<int*>(int* left, int* right)
{
	return *left < *right;
}


//int main()
//{
//	int a = 10;
//	int b = 20;
//	cout << Less(a, b) << endl;
//
//	int* pa = &a;
//	int* pb = &b;
//	cout << Less(pa, pb) << endl;
//
//	return 0;
//}

// 2. 类模板特化
// 全特化
template<class T1, class T2>
class Data
{
public:
	Data() { cout << "Data<T1, T2>" << endl; }
private:
	T1 _d1;
	T2 _d2;
};
template<>
class Data<int,char>
{
public:
	Data() { cout << "Data<int, char >" << endl; }
private:
	int _d1;
	char _d2;
};

// 偏特化
template<class T5>
class Data<T5, char>
{
public:
	Data() { cout << "Data<T5, char>" << endl; }
private:
	T5 _d1;
	char _d2;
};

// 所有指针走这个 偏特化
template<class T7,class T8>
class Data<T7*, T8*>
{
public:
	Data() { cout << "Data<T7*, T8*>" << endl; }
private:
	T7* _d1;
	T8* _d2;
};

// 所有引用走这个 偏特化
template<class T9,class T10>
class Data<T9&, T10&>
{
public:
	Data(const T9& d1, const T9& d2)
		:_d1(d1)
		,_d2(d2)
	{ cout << "Data<T9&, T10&>" << endl; }
private:
	const T9& _d1;
	const T10& _d2;
};


void TestVector()
{
	Data<int, int> d1;
	Data<int, char> d2;
	Data<int*, char> d3;
	Data<double, char> d4;
	Data<double*, char*> d5;
	Data<int&, int&> d6(1,2);
}
int main()
{
	TestVector();
	return 0;
}

// 为什么模板不能分文件写声明和定义
/*
	因为编译要经过以下过程
	预处理：展开头文件、删除注释、宏替换
	编译：检查语法、生成符号表、代码转换成汇编代码
	汇编：汇编代码转换成机器码
	链接：合并文件，形成可执行程序
	
	当main.c文件看到模板声明时会 进行记录，
	但模板.c文件因为链接之前 没有被显示的被调用，所以没有实例化，没有在符号表里生成具体的地址
	链接之前的过程 各个文件都是独立进行预处理、编译、汇编的，所以连接时找不到 未实例化的类模板，所以报错
	就是因为模板没有调用，所以没被实例化。




*/

// 晚上英语、学习编译链接过程