#pragma once


namespace wx
{
	template<class T>
	class Less
	{
	public:

		bool operator()(const T& x, const T& y)
		{
			return x < y;
		}
	};

	template<class T>
	class Greater
	{
	public:
		bool operator()(const T& x, const T& y)
		{
			return x > y;
		}
	};



	template <class T, class Container = vector<T>,class Compare = Greater<T>>
	class priority_queue
	{
		Compare com;

		void AdjustUp()
		{
			size_t child = size() - 1;
			size_t parent = (child - 1) / 2;
			while (child > 0)
			{
				//if (  _con[parent] < _con[child])
				if (com(_con[parent] , _con[child]))
				{
					swap(_con[child], _con[parent]);
					child = parent;
					parent = (child - 1) / 2;
				}
				else
				{
					break;
				}
			}

		}
		// 默认升序 建大堆
		void AdjustDown(size_t parent)
		{
			size_t child = parent * 2 + 1;
			size_t n = size();

			while (child < n)
			{
				//if (child + 1 < n && _con[child] < _con[child + 1])
				if (child + 1 < n && com(_con[child] , _con[child + 1]))
				{
					++child;
				}

				//if (_con[parent] < _con[child])
				if (com(_con[parent] , _con[child]))
				{
					swap(_con[parent], _con[child]);
					parent = child;
					child = parent * 2 + 1;
				}
				else
				{
					break;
				}
			}
		}
	public:
		

		void push(const T& x)
		{
			_con.push_back(x);
			AdjustUp();
		}

		void pop()
		{
			swap(_con[0], _con[size() - 1]);
			_con.pop_back(); // 先pop 不然向下调整时size没变，还会把最后一个元素进行调整

			AdjustDown(0);
		}

		T& top()
		{
			return  _con[0];
		}

		const T& top() const
		{
			return  _con[0];
		}

		bool empty() const
		{
			return _con.empty();
		}

		size_t size() const
		{
			return _con.size();
		}


	private:
		Container _con;
	};
}