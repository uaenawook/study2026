#pragma once
#include<iostream>
#include<assert.h>

using namespace std;

namespace wx
{
	class string
	{

	public:
		string()
		{}

		~string()
		{}


	private:

		char* _str;
		size_t _size;
		size_t _capacity;
	};


	void String_Test1();
}