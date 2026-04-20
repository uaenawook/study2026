#include"Date.h"


Date::Date(int year, int month, int day)
{
	_year = year;
	_month = month;
	_day = day;
	if (!CheckDate())
	{
		cout << "非法日期：";
		print();
	}
}
void Date::print() const
{
	cout << _year << "-" << _month << "-" << _day << endl;
}

bool Date::CheckDate() const
{
	if (  (_month > 0 && _month < 13)
		&&(_day > 0 && _day <= GetMonthDay(_year, _month)) )
	{
			return true;
	}
	else
	{
		return false;
	}
}

//d1 < d2
bool Date::operator<(const Date& d) const
{
	if (_year < d._year) // 写成了d._day 导致了逻辑错误
	{
		return true;
	}
	else if (_year == d._year)
	{
		if (_month < d._month)
		{
			return true;
		}
		else if (_month == d._month)
		{
			if (_day < d._day)
			{
				return true;
			}
		}
	}
	return false;
}
bool Date::operator<=(const Date& d) const
{
	return *this < d || *this == d; // || 写成了&& 导致逻辑错误
}
//20 > 21
bool Date::operator>(const Date& d) const
{
	return !(*this <= d);
}
bool Date::operator>=(const Date& d) const
{
	return *this > d || *this == d; // || 写成了&& 导致逻辑错误
}
bool Date::operator==(const Date& d) const
{
	return _year == d._year
		&& _month == d._month
		&& _day == d._day;
}
bool Date::operator!=(const Date& d) const
{
	return !(*this == d);
}
// d1 += 天数​
Date& Date::operator+=(int day)
{
	if (day < 0)
	{
		return *this -= -day;
	}
	_day += day;

	while (_day > GetMonthDay(_year, _month))
	{
		_day -= GetMonthDay(_year, _month);
		++_month;
		if (_month == 13)
		{
			++_year;
			_month = 1;
		}
	}
	return *this;
}
Date Date::operator+(int day) const
{
	if (day < 0)
	{
		return *this - -day;
	}
	Date tmp = *this;
	tmp += day;
	return tmp;
}

Date& Date::operator-=(int day)
{
	if (day < 0)
	{
		return *this += -day;
	}
	_day -= day;
	while (_day <= 0)
	{
		--_month;
		if (_month == 0)
		{
			_month = 12;
			--_year;
		}
		_day += GetMonthDay(_year, _month);

	}
	return *this;
}
Date Date::operator-(int day) const
{
	if (day < 0)
	{
		return *this + -day;
	}
	Date tmp = *this;
	tmp -= day;
	return tmp;
}


// 日期减日期
int Date::operator-(const Date& d) const
{
	int flag = 1;
	int n = 0;
	Date max = *this;
	Date min = d;
	if (max < min)
	{
		max = d;
		min = *this;
		flag = -1; // 如果*this<d,那减出来是负数
	}
	while (min != max)
	{
		min += 1;
		++n;
	}
	return n * flag;
}

// 前置++
Date& Date::operator++()
{
	return *this += 1;
}
// 后置++
Date Date::operator++(int)
{
	Date tmp = *this;
	*this += 1;
	return tmp;
}

// 前置--
Date& Date::operator--()
{
	return *this -= 1;
}
// 后置--
Date Date::operator--(int)
{
	Date tmp = *this;
	*this -= 1;
	return tmp;
}


ostream& operator<<(ostream& out, const Date& d)
{
	out << d._year << "年" << d._month << "月" << d._day << "日";
	return out;
}

istream& operator>>(istream& in, Date& d)
{
	while (1)
	{
		cout << "请输入日期:";
		in >> d._year >> d._month >> d._day;
		if (!d.CheckDate())
		{
			cout << "非法日期,请重新输入：";
			d.print();
		}
		else
		{
			break;
		}
	}
	return in;
}