#include<iostream>
#include<set>
#include<map>
using namespace std;

// set使用

int main()
{
	set<int> st = {5,9,8,6,3,44,50,0};
	set<int>::iterator it = st.begin();
	while (it != st.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;

	map<string, string> mp = { {"哈哈","haha"},{"你好","hello"}, {"世界","world"}, {"林纳斯托瓦兹","Linux"} };
	map<string, string>::iterator mit = mp.begin();
	while (mit != mp.end())
	{
		cout << mit->first << " " << mit->second <<endl;
		++mit;
	}
	cout << endl;

}