
#include"List.h"


void test_list()
{
	list<int> mylist1;
	mylist1.push_back(1);
	mylist1.push_back(2);
	mylist1.push_back(3);
	mylist1.push_back(4);

	list<int> mylist2;
	mylist2.push_back(5);
	mylist2.push_back(6);
	mylist2.push_back(7);
	mylist2.push_back(8);



	// mylist2.splice(mylist2.begin(), mylist1); // mylist2 1 2 3 4 5 6 7 8
	// mylist2.splice(mylist2.begin(), mylist1,mylist1.begin()); // mylist2 1 5 6 7 8
	int x = 0;
	cin >> x;
	list<int>::iterator it = find(mylist2.begin(),mylist2.end(),x);
	//mylist2.splice(mylist2.begin(), mylist2,it); // ÊäÈë 8 mylist2 8 5 6 7
	mylist2.splice(mylist2.begin(), mylist2,it,mylist2.end()); // ÊäÈë 7 mylist2 7 8 5 6 
	for (auto e : mylist2)
	{
		cout << e << " ";
	}
	cout << endl;

	for (auto e : mylist1)
	{
		cout << e << " ";
	}
	cout << endl;
}

namespace wx
{
	void test_list1()
	{
		list<int> l1;
		l1.push_back(1);
		l1.push_back(2);
		l1.push_back(3);

	}
}
int main()
{
	//test_list();
	wx::test_list1();
	return 0;
}