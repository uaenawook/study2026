#include"String.h"


// 模拟实现string
// 晚上继续实现string 2026.04.27

namespace wx
{
	void String_Test1()
	{

		string s1("hello world");
		cout << s1.c_str() << endl;

		string s2(s1);
		cout << s2.c_str() << endl;
		cout << s2[0] << endl;
		cout << s2.size() << endl;
		cout << s2.capacity() << endl;

		s2.push_back('x');
		cout << s2.c_str() << endl;

		string s3("hello world");
		char arr[] = "xxx";
		s3.append(arr);
		cout << s3.c_str() << endl;

		s3 += 'y';
		s3 += arr;
		cout << s3.c_str() << endl;

		string s4("hello world");
		s4.insert(5, 'x');
		cout << s4.c_str() << endl;

		s4.insert(0, 'x');
		cout << s4.c_str() << endl;

		string s5("hello world");
		s5.insert(5, "xxx");
		cout << s5.c_str() << endl;

		s5.insert(0, "");
		cout << s5.c_str() << endl;

		string s6("hello worlde");
		s6.erase(6,1);
		cout << s6.c_str() << endl;

		cout << s6.find('e',3) << endl;

		string s7("hello eworld ewo");
		cout << s7.find("ewo", 7) << endl;

		string s("hello world");
		string suffix = s.substr(6);
		cout << suffix.c_str() << endl;
	}

	void String_Test2()
	{

		string s1("hello world");
		string s2("hello world");
		cout << (s1 >= s2) << endl;

		cout << s1 << endl;

		cin >> s1;
		cout << s1 << endl;



	}
}
// 改造拷贝构造和赋值拷贝
int main()
{
	//wx::String_Test1();
	wx::String_Test2();

	//string s4("hello world");
	//s4.insert(5, "x");
	//cout << s4 << endl;



	return 0;
}