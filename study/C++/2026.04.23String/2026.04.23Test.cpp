#include<iostream>
#include<string>
using namespace std;

// 尝试使用string
//int main()
//{
//	
//	string s1;// string();
//
//	string s2(s1);// string(const string & str);
//
//	string s3("hello world");// string(const char* s);
//
//	string s4(s3, 6);// string(const string & str, size_t pos, size_t len = npos);
//	string s44(s3, 6,999); //size_t npos = -1,整形最大值 42亿
//
//	string s5("hello world", 5);// string(const char* s, size_t n);
//
//	string s6(10,'x');// string(size_t n, char c);
//
//
//	return 0;
//}

// 2026.04.24
/*
	迭代器
		iterator
		string::iterator si = s1.begin();
	auto/范围for
	string 的接口
	length,size,[],begin(),capacity,
	做题
*/

//int main()
//{
//	string st("hello world");
//	cout << st << endl;
//
//	for (int i = 0; i < st.size(); i++)
//	{
//		cout << st[i] << " ";
//	}
//	cout << endl;
//
//	string::iterator sti = st.begin();
//	while (sti != st.end())
//	{
//		*sti += 1;
//		cout << *sti << " ";
//		++sti;
//	}
//	cout << endl;
//
//	for (auto& ch : st)
//	{
//		ch+= 1;
//		cout << ch << ' ';
//	}
//	cout << endl;
//
//	string::reverse_iterator rsti = st.rbegin();
//
//	cout << *rsti << endl;
//
//
//	return 0;
//}


void TestFunc1()
{
	string s2("hello world!hello world!");
	cout << s2.length() << endl;
	cout << s2.size() << endl; //显示是11，其实开了12个空间 还有一个空间存了\0;

	cout << s2.max_size() << endl;

	cout << s2.capacity() << endl;
	if (s2[s2.size()] == '\0')
	{
		cout << "\\0" << endl;
	}

	cout << typeid(s2).name() << endl;

	int a = 10;
	cout << typeid(a).name() << endl;

}
// auto 能做返回值，不能做参数
auto func1()
{

}

int main()
{
	//TestFunc1();
	int a[26] = { 0 };
	for (auto ch : a)
	{
		cout << ch << ' ';
	}
	return 0;
}