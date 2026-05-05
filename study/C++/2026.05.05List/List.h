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

	template <class T>
	struct list_iterator
	{
		typedef list_node<T> Node;
		typedef list_iterator<T> iterator;

		Node* _node;


		list_iterator(Node* node)
			:_node(node)
		{}

		T& operator*()
		{
			return _node->data;
		}

		iterator& operator++()
		{
			_node = _node->next;
			return *this;
		}

		iterator& operator--()
		{
			_node = _node->prev;
			return *this;
		}

		bool operator!=(const iterator& L) const
		{
			return _node != L._node;
		}

		bool operator==(const iterator& L) const
		{
			return _node == L._node;
		}
	};

	template <class T>
	class list
	{
		typedef list_node<T> Node;
	public:
		typedef list_iterator<T> iterator;

		iterator begin()
		{
			//iterator it(_head->next);
			//return it;

			//return iterator(_head->next);

			return _head->next;
		}

		iterator end()
		{
			return _head;
		}

		list()
		{
			_head = new Node;
			_head->prev = _head;
			_head->next = _head;
			_size = 0;
		}

		void push_back(const T& val)
		{
			Node* prev = _head->prev;
			Node* newNode = new Node(val);

			newNode->next = _head;
			newNode->prev = prev;
			prev->next = newNode;
			_head->prev = newNode;
			++_size;
		}


		void insert(iterator pos,const T& val)
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
		}
		
		void erase(iterator pos)
		{
			assert(pos != end());
			Node* prev = pos._node->prev;
			Node* next = pos._node->next;

			prev->next = next;
			next->prev = prev;

			delete pos._node;
			--_size;
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
}