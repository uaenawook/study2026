#pragma once
#include<iostream>
using namespace std;


class Date
{
public:
	Date(int year = 1970, int month = 1, int day = 1);
	void print();

	int GetMonthDay(int year, int month)
	{
		static int arr[13] = { -1,31,28,31,30,31,30,31,31,30,31,30,31 };
		// 润年：4年一润、百年不润，400年一润
		if (month == 2 &&( (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)))
			return 29;
		else
			return arr[month];
	}

	bool operator<(const Date& d);
	bool operator<=(const Date& d);
	bool operator>(const Date& d);
	bool operator>=(const Date& d);
	bool operator==(const Date& d);
	bool operator!=(const Date& d);
	// d1 += 天数​
	Date& operator+=(int day);
	Date operator+(int day);



private:
	int _year;
	int _month;
	int _day;
};