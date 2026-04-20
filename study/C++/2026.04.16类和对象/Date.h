#pragma once
#include<iostream>
using namespace std;


class Date
{

	friend ostream& operator<<(ostream& out, const Date& d);
	friend istream& operator>>(istream& in, Date& d);
public:
	Date(int year = 1970, int month = 1, int day = 1);
	void print() const;

	int GetMonthDay(int year, int month) const
	{
		static int arr[13] = { -1,31,28,31,30,31,30,31,31,30,31,30,31 };
		// 润年：4年一润、百年不润，400年一润
		if (month == 2 &&( (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)))
			return 29;
		else
			return arr[month];
	}

	bool CheckDate() const;

	bool operator<(const Date& d) const;
	bool operator<=(const Date& d) const;
	bool operator>(const Date& d) const;
	bool operator>=(const Date& d) const;
	bool operator==(const Date& d) const;
	bool operator!=(const Date& d) const;
	// d1 += 天数​
	Date& operator+=(int day);
	Date operator+(int day) const;

	Date& operator-=(int day);
	Date operator-(int day) const;

	int operator-(const Date& d) const;
	// ++d1 -> d1.operator++()
	Date& operator++();
	// d1++ -> d1.operator++(0)
	// 为了区分，构成重载，给后置++，强行增加了一个int形参​
	// 这里不需要写形参名，因为接收值是多少不重要，也不需要用​
	// 这个参数仅仅是为了跟前置++构成重载区分​
	Date operator++(int);

	Date& operator--();
	Date operator--(int);

	Date* operator&()
	{
		return this;

		//return nullptr;
		//return (Date*)0x0012FF40;
		
	}
	const Date* operator&()const
	{
		return this;

		//return nullptr;
		//return (Date*)0x0012FF80;
	}


private:
	int _year;
	int _month;
	int _day;
};

ostream& operator<<(ostream& out, const Date& d);
istream& operator>>(istream& in, Date& d);