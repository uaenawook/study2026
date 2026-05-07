#pragma once


namespace wx
{
	// 栈 先进后出 
	template <class T,class Container = vector<T>>
	class Stack
	{
	public:
		void push(const T& x)
		{
			_con.push_back(x);
		}

		void pop()
		{
			_con.pop_back();
		}

		T& top()
		{
			return  _con.back();
		}
		const T& top() const
		{
			return  _con.back();
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