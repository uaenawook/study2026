#include"String.h"

namespace wx
{
	// Ô¤¶¨ÈÝÁ¿
	void string::reserve(size_t n)
	{
		if (n > _capacity)
		{
			char* tmp = new char[n + 1];
			strcpy(tmp, _str);
			delete[] _str;
			_str = tmp;
			_capacity = n;
		}
		
	}

	void string::push_back(char ch)
	{
		if (_size + 1 > _capacity)
		{
			reserve(_capacity == 0 ? 4 : _capacity * 2);
		}
		_str[_size] = ch;
		++_size;
		_str[_size] = '\0';
	}

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


	}

}
