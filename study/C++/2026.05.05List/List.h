#pragma once
#include<iostream>
#include<assert.h>
#include<algorithm>
#include<list>
using namespace std;

namespace wx
{
	
	template <class T>
	struct list_node
	{
		list_node<T>* prev;
		list_node<T>* next;
		T data;

		list_node(const T& data = T())
			:data(data)
			,prev(nullptr)
			,next(nullptr)
		{}
	};

	// 改造const iterator模板类
	template <class T,class Ref,class Ptr>
	struct list_iterator
	{
		typedef list_node<T> Node;
		typedef list_iterator<T, Ref, Ptr> self;

		Node* _node;


		list_iterator(Node* node)
			:_node(node)
		{}

		Ref operator*()
		{
			return _node->data;
		}

		Ptr operator->()
		{
			return &(_node->data);
		}


		// 补充后置++ 后置++先使用再++，返回++之前的值
		self operator++(int)
		{
			self tmp(*this);
			_node = _node->next;
			return tmp;
		}

		self& operator++()
		{
			_node = _node->next;
			return *this;
		}

		// 补充后置--
		self operator--(int)
		{
			self tmp(*this);
			_node = _node->prev;
			return tmp;
		}

		self& operator--()
		{
			_node = _node->prev;
			return *this;
		}

		bool operator!=(const self& L) const
		{
			return _node != L._node;
		}

		bool operator==(const self& L) const
		{
			return _node == L._node;
		}
	};

	template <class T>
	class list
	{
		typedef list_node<T> Node;
	public:
		typedef list_iterator<T, T&, T*> iterator;
		typedef list_iterator<T, const T&, const T*> const_iterator;

		iterator begin()
		{
			//iterator it(_head->next);
			//return it;

			//return iterator(_head->next);

			return _head->next; // 因为返回值是iterator 所以会发生隐式类型转换，使_head->next转换为iterator类型
		}

		iterator end()
		{
			return _head;
		}

		const_iterator begin() const
		{
			return _head->next;
		}
		const_iterator end() const
		{
			return _head;
		}



		void empty_init()
		{
			_head = new Node;
			_head->prev = _head;
			_head->next = _head;
			_size = 0;
		}

		list()
		{
			empty_init();
		}

		~list()
		{
			clear();
			delete _head;
			_head = nullptr;
		}
		// list多参数构造
		list(initializer_list<T> il)
		{
			empty_init();
			for (auto& e : il)
			{
				push_back(e);
			}
		}

		//lt2(lt1)
		list(const list<T>& lt)
		{
			empty_init();
			for (auto& e : lt)
			{
				push_back(e);
			}
		}
		// clear
		void clear()
		{
			typename list<T>::iterator it = (*this).begin();
			while (it != end())
			{
				it = erase(it);
			}
		}

		void swap(list<T>& lt)
		{
			std::swap(_head, lt._head);
			std::swap(_size, lt._size);
		}

		// lt1 = lt3
		//list<T>& operator=(const list<T>& lt)
		//{
		//	clear();
		//	for (auto& e : lt)
		//	{
		//		push_back(e);
		//	}
		//	return *this;
		//}
		list<T>& operator=(list<T> lt)
		{
			swap(lt);
			return *this;
		}


		

		void push_back(const T& val)
		{
			/*Node* prev = _head->prev;
			Node* newNode = new Node(val);

			newNode->next = _head;
			newNode->prev = prev;
			prev->next = newNode;
			_head->prev = newNode;
			++_size;*/
			insert(end(), val);
		}
		
		void push_front(const T& val)
		{
			insert(begin(), val);
		}


		void pop_back()
		{
			erase(--end());
		}
		void pop_front()
		{
			erase(begin());
		}

		Node* insert(iterator pos,const T& val)
		{
			Node* newNode = new Node(val);

			Node* cur = pos._node;
			Node* prev = cur->prev;

			// prev newNode pos;
			newNode->next = cur;
			cur->prev = newNode;
			newNode->prev = prev;
			prev->next = newNode;

			++_size;
			return newNode;
		}
		
		Node* erase(iterator pos)
		{
			assert(pos != end());
			Node* prev = pos._node->prev;
			Node* next = pos._node->next;

			prev->next = next;
			next->prev = prev;

			delete pos._node;
			--_size;
			return next;
		}


		size_t size()
		{
			return _size;
		}
		bool empty()
		{
			return _size == 0;
		}

	private:
		Node* _head;
		size_t _size;
	};

	template <class container>
	void printf_container(const container& t)
	{
		//auto it = t.begin();
		typename container::const_iterator it = t.begin();
		while (it != t.end())
		{
			cout << *it << " ";
			++it;
		}
		cout << endl;
	}
}