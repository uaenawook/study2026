#include"String.h"

namespace wx
{

	const size_t string::npos = -1;

	// 预定容量
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

	// 附加子串
	void string::append(const char* str)
	{
		size_t len = strlen(str);
		if (_size + len > _capacity)
		{
			reserve(_size + len > 2 * _capacity ? _size + len : 2 * _capacity);
		}
		for (int i = 0; i < len; i++)
		{
			_str[_size++] = str[i];
		}
		_str[_size] = '\0';

	}

	string& string::operator+=(char ch)
	{
		push_back(ch);
		return *this;
	}
	string& string::operator+=(const char* str)
	{
		append(str);
		return *this;

	}

	void string::insert(size_t pos, char ch)
	{
		assert(pos < _size);
		if (_size + 1 > _capacity)
		{
			reserve(_capacity == 0 ? 4 : _capacity * 2);
		}
		int end = _size + 1;

		//while (pos <= end) 此时end == -1 会被转换成size_t类型进行比较，所以end 永远不可能小于pos
		//while ((int)pos <= end) 把pos转成int可解决问题
		while (pos < end)
		{

			_str[end] = _str[end - 1];
			--end;
		}
		_str[pos] = ch;
		++_size;
	}
	int myStrlen(const char* arr)
	{
		// "xxx\0";
		int n = 0;
		while (arr[n] != '\0')
		{
			n++;
		}
		return n;
	}
	void string::insert(size_t pos, const char* str)
	{
		assert(pos < _size);

		int len = myStrlen(str);
		if (_size + len > _capacity)
		{
			reserve(_size + len > 2 * _capacity ? _size + len : 2 * _capacity);
		}

		int end = _size + len;
		while (pos+len-1 < end)
		{

			_str[end] = _str[end - len];
			--end;
		}
		for (int i = 0; i < len; i++)
		{
			_str[pos + i] = str[i];
		}
		_size += len;
	}
	void string::erase(size_t pos, size_t len)
	{
		//if (pos + len >= _size) // 此时不能写pos+len，因为len = -1，len是全1，例如 全1 + 5 = 4，有1个数用作进位了。
		if (len >= _size - pos) // 
		{
			_str[pos] = '\0';
			_size = pos;
		}
		else
		{
			while (pos + len <= _size)
			{
				_str[pos++] = _str[pos + len];
			}
			_size -= len;
		}
	}

	size_t string::find(char ch, size_t pos)
	{
		for(int i = pos;i<_size;i++)
		{
			if (_str[i] == ch)
			{
				return i;
			}
		}
		return npos;
	}

	size_t string::find(const char* str, size_t pos)
	{
		char* tmp = strstr(_str + pos, str);
		if (tmp == nullptr)
		{
			return npos;
		}
		else
		{
			return tmp - _str;
		}
	}

	string string::substr(size_t pos, size_t len)
	{
		if (len > _size - pos)
		{
			len = _size - pos;
		}
		string tmp;
		for (int i = pos; i < pos + len; i++)
		{
			tmp.push_back(_str[i]);
		}
		return tmp;
	}

}
