#include<iostream>
#include<vector>
#include<list>
#include<stack>
using namespace std;

#include"Stack.h"	
#include"Queue.h"	
#include"PriorityQueue.h"	

void test1()
{
	//wx::Stack<int> st;
	wx::Stack<int, list<int>> st;
	st.push(1);
	st.push(2);
	st.push(3);
	st.push(4);

	st.top() += 100;

	while (!st.empty())
	{
		cout << st.top() << " ";
		st.pop();
	}
	cout << endl;

	wx::Queue<int> qu;
	qu.push(1);
	qu.push(2);
	qu.push(3);
	qu.push(4);

	while (!qu.empty())
	{
		cout << qu.top() << " ";
		qu.pop();
	}
	cout << endl;


	wx::priority_queue<int> pq;
	pq.push(5);
	pq.push(100);
	pq.push(3);
	pq.push(1);

	while (!pq.empty())
	{
		cout << pq.top() << " ";
		pq.pop();
	}
	cout << endl;
}
int main()
{
	test1();

	stack<int> st;
	st.push(1);
	st.push(2);
	st.push(3);
	st.push(4);
	st.top() += 100;
	cout << st.top() << endl;

	return 0;
}