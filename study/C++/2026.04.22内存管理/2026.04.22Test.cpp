#include<stdio.h>
#include<stdlib.h>
/*
	内存分布
	new和delete
	new和delete的底层是什么，怎么调用？
*/

// 选择题
int globalVar = 1;
static int staticGlobalVar = 1;
void Test1()
{
	static int staticVar = 1;
	int localVar = 1;
	int num1[10] = { 1, 2, 3, 4 };
	char char2[] = "abcd";  // "abcd" 在编译时就放在了常量区，与进程同生死，
							// *char2在栈上，而char2[]里存的是常量区"abcd"的拷贝，所以可以随意修改：char[0] ='x';
							// 常量区里永远有一份 "abcd\0"（源头，只读）。
							// 栈区 char2 的内存里有一份 'a', 'b', 'c', 'd', '\0'（克隆体，可写）。
							// 
							// 如果想减少这种拷贝就要用 const char* pChar3 = "abcd";
	const char* pChar3 = "abcd";
	int* ptr1 = (int*)malloc(sizeof(int) * 4);
	int* ptr2 = (int*)calloc(4, sizeof(int));
	int* ptr3 = (int*)realloc(ptr2, sizeof(int) * 4);
	free(ptr1);
	free(ptr3);
}

/*
1. 选择题：
选项: A.栈 B.堆 C.数据段(静态区) D.代码段(常量区)
globalVar在哪里？____ 错了两次
staticGlobalVar在哪里？____
staticVar在哪里？____
localVar在哪里？____
num1 在哪里？____ 错了一次


char2在哪里？____
*char2在哪里？___
pChar3在哪里？____
*pChar3在哪里？____ 错了一次
ptr1在哪里？____
*ptr1在哪里？____
*/

/*
1. 栈又叫堆栈--非静态局部变量/函数参数/返回值等等，栈是向下增长的。
2. 内存映射段是高效的I/O映射方式，用于装载一个共享的动态内存库。用户可使用系统接口
创建共享共享内存，做进程间通信。
3. 堆用于程序运行时动态内存分配，堆是可以上增长的。
4. 数据段--存储全局数据和静态数据。
5. 代码段--可执行的代码/只读常量。
*/

// 2026.04.22 晚上看 3 - 6的位置

void Test()
{
	// 动态申请一个int类型的空间
	int* ptr4 = new int;

	// 动态申请一个int类型的空间并初始化为10
	int* ptr5 = new int(10);

	// 动态申请10个int类型的空间
	int* ptr6 = new int[10];

	// 动态申请10个int类型的空间 初始化为0
	int* ptr7 = new int[10]{ 0 };

	delete ptr4;
	delete ptr5;
	delete[] ptr6;	// new[] 和 delete[] 要匹配使用
}

//int main()
//{
//	Test();
//
//
//	return 0;
//}
#include<iostream>
using namespace std;

class A
{
public:
	A(int a = 0)
		: _a(a)
	{
		cout << "A():" << this << endl;
	}
	//~A()
	//{
	//	cout << "~A():" << this << endl;
	//}
private:
	//注意：在申请自定义类型的空间时，new会调用构造函数，delete会调用析构函数，而malloc与free不会。
	int _a;
	//int _b;
};

/*
	new 的底层是malloc，new对象会调用operator new,operator new 里是malloc，成功正常返回，失败则抛异常 
	new = 先operator new + 再调用构造函数

	new[] 会先调用1次operator new[]开一块连续的大空间，再在这块内存上调用N次构造函数
	new[] = 1次operator new[] + N次构造函数

	delete 的底层时 free ，delete对象会调用 operator delete,operator delete里是free。
	delete = 调用析构函数  + operator delete

	delete[] 先调用 N次 析构函数，再调用1次 operator delete[]释放这块空间，
	delete[] = N次析构函数 + 1次operator delete[]

*/

int main()
{
	// new/delete 和 malloc/free最大区别是 new/delete对于【自定义类型】除了开空间还会调用构造函数和析构函数
	A* p1 = (A*)malloc(sizeof(A));
	A* p2 = new A(1);
	free(p1);
	delete p2;


	// 内置类型是几乎是一样的
	int* p3 = (int*)malloc(sizeof(int)); // C
	int* p4 = new int;
	free(p3);
	delete p4;


	A* p5 = (A*)malloc(sizeof(A) * 10);
	A* p6 = new A[10];	// 正常10int为40字节，
						// 编译器开了44字节，在第一个地址前多开了4字节存 10，方便确定析构次数。而返回的地址是从4字节之后返回40个字节
						// 出现这种情况是因为A类写了析构函数。
						// 此时如果只使用delete p6,缺少[],则会崩溃，释放空间不能只释放一半
						// 尽量匹配使用new/delete 和 new[]/delete[]

	free(p5);
	delete[] p6;


	return 0;
}


// 2026.04.23 下午看6-7的位置














/*
答案：C、C、C、A、A、   A、A、A、D、A、B、
*/

