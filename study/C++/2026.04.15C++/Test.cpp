
#include"func.h"
namespace wx
{
	int a = 10;

	namespace wx
	{
		int c = 30;
	}
}


namespace wx
{
	int b = 20;



}



int main()
{
	printf("%d ", wx::a);
	printf("%d ", wx::b);
	printf("%d ", wx::wx::c);

	//int c = wx::func(10);
	//printf("%d ", c);

	int a = 10;
	int& b = a;
	int& c = b;
	int d = 200;
	int& e = d;
	b = d;
	c = 10;
	cout << a << endl;
	cout << c << endl;
	return 0;
}