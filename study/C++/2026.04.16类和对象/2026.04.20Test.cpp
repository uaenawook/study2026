#include"Date.h"




// 完善日期类
// 友元函数
// const 修饰this指针

void DateTest1()
{
	Date d1(2026, 4, 20);
	Date d2 = d1 + -100;
	d1.print();
	d2.print();
}
void DateTest2()
{
	Date d1(2026, 4, 13);
	Date d2(2026, 4, 20);
	cout << (d1 <= d2) << endl;

	cout << d1 - d2 << endl;
	cout << d2 - d1 << endl;

	cout << d1 << " " << d2 << endl;


	//cin >> d1 >> d2;
	//cout << d1 << " " << d2 << endl;

}


void DateTest3()
{
	Date d1(2026, 12, -20);
	//cout << d1 << endl;
	Date d2(2026, 4, 20);

	cout << &d1 << " " << &d2 << endl;

}
int main()
{
	DateTest1();

	DateTest2();

	DateTest3();
	return 0;
}