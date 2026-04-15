
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

	int c = wx::func(10);
	printf("%d ", c);
	return 0;
}