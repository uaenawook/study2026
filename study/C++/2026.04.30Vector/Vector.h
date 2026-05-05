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

		//构造函数、析构函数
		// 写了析构函数test_vector4会崩溃 2026.05.02遗留
		// 缺少深拷贝的拷贝构造
		vector()
		{}

		// 1. 自己开空间，拷贝
		/*vector(const vector<T>& v)
		{
			size_t capacity = v.capacity();
			_start = new T[capacity];
			_finish = _start;
			_end_of_storage = _start + capacity;

			for (size_t i = 0; i < v.size(); i++)
			{
				*_finish = v[i];
				++_finish;
			}

		}*/

		// 2. 直接给this扩容，然后插入数据
		vector(const vector<T>& v)
		{
			reserve(v.capacity());
			for (auto& e : v)
			{
				push_back(e);
			}
		}

		// 2026-5-4继续写
		template <class InputIterator>
		vector(InputIterator first, InputIterator last)
		{
			//size_t n = last - first;
			//reserve(n);
			while (first != last)
			{
				push_back(*first);
				++first;
			}
		}
		vector(size_t n, const T& val = T())
		{
			reserve(n);
			while (n--)
			{
				push_back(val);
			}
		}
		vector(int n, const T& val = T())
		{
			reserve(n);
			while (n--)
			{
				push_back(val);
			}
		}

		vector<T>& operator=(vector<T> tmp)
		{
			swap(tmp);
			return *this;
		}

		~vector()
		{
			delete[] _start;
			_start = _finish = _end_of_storage = nullptr;
		}
		size_t capacity() const
		{
			return _end_of_storage - _start;
		}

		size_t size() const
		{
			return _finish - _start;
		}
		

		
		bool empty() const
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

		const_iterator begin() const
		{
			return _start;
		}

		const_iterator end() const
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
				//memcpy(tmp, _start, old_size *sizeof(T)); //memcpy 传大小的时候必须算字节
				for (size_t i = 0; i < old_size; ++i)
				{
					tmp[i] = _start[i];
				}
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

		// 插入数据，可能会扩容
		void resize(size_t n, T val = T())
		{
			// n<_finish ,删除数据到n个
			// _end_of_storage < n >_finish 插入n个val，增加_finish
			// n > _end_of_storage 扩容
			if (n <= size())
			{
				_finish = _start + n;
			}
			else
			{
				reserve(n);
				for(int i = size();i<n;++i)
				{
					push_back(val);
				}
			}

			
		}

		iterator erase(iterator pos)
		{
			// 在pos位置进行删除，返回pos的位置
			assert(pos < _finish&& pos >= _start);
			// 挪动数据
			iterator cur = pos+1;
			while (cur != _finish)
			{
				*(cur - 1) = *cur;
				++cur;
			}
			--_finish;
			return pos;
		}

		iterator erase(iterator first, iterator last)
		{
			// 删除一段区间 删除是[first,last) ,删去区间是作弊又开，返回的是first
			size_t n = last - first;
			vector<int>::iterator cur = last;
			while (cur != _finish)
			{
				*(cur - n) = *cur;
				++cur;
			}
			_finish -= n;
			return first;
		}

		void clear()
		{
			_finish = _start;
		}


		void swap(vector<T>& v)
		{
			std::swap(_start, v._start);
			std::swap(_finish, v._finish);
			std::swap(_end_of_storage, v._end_of_storage);
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
	template <class container>
	void print_container(const container& v)
	{
		for (const auto& e : v)
		{
			cout << e << " ";
		}
		cout << endl;
	}
}

//  继续实现vector的插入、插入n个数据，插入不同类型的数据、迭代器失效、深拷贝、等功能