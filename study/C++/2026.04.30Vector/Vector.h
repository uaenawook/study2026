#pragma once
#include<assert.h>

namespace wx
{
	template <class T>
	class vector
	{
	public:
		typedef T* iterator;
		typedef const T* const_iterator;

		size_t size()
		{
			return _finish - _start;
		}

		size_t capacity()
		{
			return _end_of_storage - _start;
		}

		bool empty()
		{
			return _start == _finish;
		}

		iterator& begin()
		{
			return _start;
		}

		iterator& end()
		{
			return _finish;
		}

		const_iterator& begin() const
		{
			return _start;
		}

		const_iterator& end() const
		{
			return _finish;
		}

		void print_vector()
		{
			for (auto e : *this)
			{
				cout << e << ' ';
			}
			cout << endl;
		}

		void reserve(size_t n)
		{
			// 开新空间，把就数据拷贝，更新数据
			if (n > capacity())
			{
				size_t old_size = size();
				T* tmp = new T[n];
				memcpy(tmp, _start, size()*sizeof(T)); //memcpy 传大小的时候必须算字节
				delete[] _start;

				_start = tmp;
				_finish = tmp + old_size;
				_end_of_storage = tmp + n;
			}

		}
		void push_back(const T& x)
		{
			if (_finish == _end_of_storage)
			{
				reserve(capacity() == 0 ? 4 : 2 * capacity());
			}

			*_finish = x;
			++_finish;
		}
		void pop_back()
		{
			assert(!empty());
			--_finish;
		}
		iterator insert(iterator pos, const T& x)
		{
			if (_finish == _end_of_storage)
			{
				// 如果发生扩容 pos 还指向原空间，则会失效
				size_t old_size = pos - _start;
				reserve(capacity() == 0 ? 4 : 2 * capacity());
				pos = _start + old_size; //用新的空间起始位置 + old_size 就是新的pos位置
			}

			iterator end = _finish;
			while (pos < end)
			{
				*(end) = *(end - 1);
				--end;
			}
			*pos = x;
			++_finish;

			return pos;
		}
		T& operator[](size_t i)
		{
			assert(i < size());
			return *(_start + i);
		}

		const T& operator[](size_t i) const
		{
			assert(i < size());
			return *(_start + i);
		}

	private:
		iterator _start = nullptr;
		iterator _finish = nullptr;
		iterator _end_of_storage = nullptr;
	};


	template <class T>
	void print_vector(vector<T>& v)
	{
		// 当vector的参数不实例化时，编译器需要明确写 iterator 类型是 typename
		typename vector<T>::const_iterator it = v.begin();
		while (it != v.end())
		{
			cout << (*it) << " ";
			++it;
		}
		cout << endl;


	}
}