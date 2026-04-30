#include<iostream>
#include<vector>

using namespace std;

//  π”√vector
int main()
{

	vector<int> v1(10,1);
	for (auto e : v1)
	{
		cout << e << ' ';
	}
	cout << endl;


	return 0;
}