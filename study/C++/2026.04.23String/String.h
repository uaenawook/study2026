#pragma once
#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<assert.h>

using namespace std;

namespace wx
{
	class string
	{

	public:
		typedef char* iterator;
		typedef const char* const_iterator;

		iterator begin()
		{
			return _str;
		}
		iterator end()
		{
			return _str + _size;
		}
		const_iterator begin() const
		{
			return _str;
		}
		const_iterator end() const
		{
			return _str + _size;
		}
		void clear()
		{
			_str[0] = '\0';
			_size = 0;
		}
		size_t size() const
		{
			return _size;
		}
		size_t capacity() const
		{
			return _capacity;
		}
		char& operator[](size_t pos)
		{
			assert(pos <= _size);
			//return (*this)._str[pos];
			return _str[pos];
		}
		const char& operator[](size_t pos) const
		{
			assert(pos <= _size);
			return _str[pos];
		}


		//string()
		//	:_str(new char[1]{'\0'})
		//	,_size(0)
		//	,_capacity(0)
		//{}
		const char* c_str() const
		{
			return _str;
		}

		string(const char* str = "")
		{
			_size = strlen(str);
			_capacity = _size;

			_str = new char[_capacity + 1];
			strcpy(_str, str);
		}

		string(string& str)
		{
			_size = str._size;
			_capacity = str._capacity;
			_str = new char[_capacity + 1];
			strcpy(_str, str.c_str());
		}

		~string()
		{
			delete[] _str;
			_str = nullptr;
			_size = _capacity = 0;
		}



		void reserve(size_t n);
		void push_back(char ch);

		void append(const char* str);
		string& operator+=(char ch);
		string& operator+=(const char* str);

		void insert(size_t pos, char ch);
		void insert(size_t pos, const char* str);
		void erase(size_t pos, size_t len = npos);


	private:

		char* _str;
		size_t _size;
		size_t _capacity;


		static const size_t npos;
	};


	void String_Test1();
}