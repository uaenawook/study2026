#pragma once

namespace wx
{
	template <class T, class Container = list<T>>
	class Queue
	{
	public:
		void push(const T& x)
		{
			_con.push_back(x);
		}

		void pop()
		{
			_con.pop_front();
		}

		T& top()
		{
			return  _con.front();
		}

		const T& top() const
		{
			return  _con.front();
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