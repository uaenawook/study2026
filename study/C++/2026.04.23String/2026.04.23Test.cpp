#include<iostream>
#include<string>
using namespace std;

// 尝试使用string
int main()
{
	
	string s1;// string();

	string s2(s1);// string(const string & str);

	string s3("hello world");// string(const char* s);

	string s4(s3, 6);// string(const string & str, size_t pos, size_t len = npos);
	string s44(s3, 6,999); //size_t npos = -1,整形最大值 42亿

	string s5("hello world", 5);// string(const char* s, size_t n);

	string s6(10,'x');// string(size_t n, char c);


	return 0;
}