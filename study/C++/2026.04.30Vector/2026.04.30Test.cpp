#include<iostream>
#include<vector>

using namespace std;

void print_vector(const vector<int>& v1)
{
	for (auto e : v1)
	{
		cout << e << ' ';
	}
	cout << endl;
}
void test_vector1()
{
	vector<int> v1(10, 1);
	print_vector(v1);

	v1.push_back(2);
	print_vector(v1);

	v1.pop_back();
	print_vector(v1);

	vector<int> v2(v1);
	print_vector(v2);
	vector<int> v3 = { 1,2,3,4,5 };

	vector<int> v4 = v3;

	print_vector(v3);
	print_vector(v4);
	cout << v4.size() << endl;

	for (size_t i = 0; i < v4.size(); ++i)
	{
		v4[i] += 1;
		cout << v4[i] << " ";
	}
	cout << endl;

}

#include"Vector.h"

namespace wx
{
	void test_vector1()
	{
		vector<int> v1;
		v1.push_back(1);
		v1.push_back(2);
		v1.push_back(3);
		v1.push_back(4);
		//v1.push_back(5);
		v1.print_vector();

		//v1.pop_back();
		//v1.pop_back();
		//v1.pop_back();
		//v1.pop_back();
		//v1.pop_back();

		//v1.print_vector();

		int x = 2;
		//cin >> x;
		vector<int>::iterator pos = find(v1.begin(), v1.end(), x);

		v1.insert(pos, 20);
		v1.print_vector();


		vector<double> v2;
		v2.push_back(1.1);
		v2.push_back(2.2);
		v2.push_back(3.3);
		v2.push_back(4.4);
		v2.push_back(5.5);

		v2.print_vector();

		print_vector(v2);
	}

	void test_vector2()
	{
		vector<int> v1;
		v1.push_back(1);
		v1.push_back(2);
		v1.push_back(3);
		v1.push_back(4);
		print_vector(v1);

		int x = 2;
		vector<int>::iterator pos = find(v1.begin(), v1.end(), x);
		v1.erase(pos);

		print_vector(v1);
	}

	void test_vector3()
	{
		vector<int> v1;
		v1.push_back(1);
		v1.push_back(2);
		v1.push_back(3);
		v1.push_back(4);
		v1.push_back(5);
		v1.push_back(6);
		v1.push_back(7);
		v1.push_back(8);
		v1.push_back(9);
		v1.push_back(10);
		//print_vector(v1);

		for (auto& ch : v1)
		{
			cout << ch << " ";
		}
		cout << endl;

		vector<int>::iterator ret2 = v1.erase(v1.begin() + 3, v1.begin()+7);
		for (auto& ch : v1)
		{
			cout << ch << " ";
		}
		cout << endl;
		cout << *ret2 << endl;


	}

	void test_vector4()
	{
		vector<int> v1;
		v1.push_back(1);
		v1.push_back(2);
		v1.push_back(3);
		v1.push_back(4);
		v1.push_back(5);
		v1.reserve(8);
		print_vector(v1);

		v1.resize(3);
		print_vector(v1);

		v1.resize(5,2);
		print_vector(v1);

		v1.resize(10,100);
		print_vector(v1);

		v1.resize(20);
		print_vector(v1);
		vector<int>v2 = v1;
		print_vector(v2);


	}
}


//  π”√vector
int main()
{
	//test_vector1();
	//wx::test_vector1();
	//wx::test_vector2();

	wx::test_vector4();
	
	return 0;
}