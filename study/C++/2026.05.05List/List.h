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

	};

	template <class T>
	class list
	{
		typedef list_node<T> Node;
	public:

		list()
		{
			_head = new Node;
			_head->prev = _head;
			_head->next = _head;
		}

		void push_back(const T& val)
		{
			Node* prev = _head->prev;
			Node* newNode = new Node(val);

			newNode->next = _head;
			newNode->prev = prev;
			prev->next = newNode;
			_head->prev = newNode;
		}

	private:
		Node* _head;

	};
}