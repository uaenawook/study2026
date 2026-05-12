#include<iostream>
using namespace std;

// 2026.5.12
/*
	不能被继承的类
		final
			class Base final
			{};

	继承和友元
		友元函数不能被子类继承，需要在子类重新声明友元

	继承与静态成员
		静态成员可以用类域访问限定符访问，并且子类和父类都可以访问


	多继承

		菱形继承
			a
		b		c
			d
					b、c继承a，
					d继承b、c。构成菱形继承
					d中会包含两份a，一份来自b继承的a，另一份来自c继承的a
				
		虚继承
			virtual
			当出现菱形继承时需要用到虚继承，谁冗余就在谁的子类用虚继承
			可以避免数据冗余
			class Student : virtual public Person


	继承和组合
		继承就是子类继承父类的 变量和函数、子类包含了父类所有东西
		组合是，一个类里面使用其他类，stack使用vector作为存储结构，但stack里不包含vector的变量和函数



	链表的回文：https://leetcode.cn/problems/palindrome-linked-list/solutions/
		思路：找到中间节点
			逆置后半段
			双指针同时走
*/

class Base final
{
public:
	void func5() { cout << "Base::func5" << endl; }
protected:
	int a = 1;
private:
	// C++98的方法​
	/*Base()
	{}*/
};
//class A :public Base{}; //报错


// 静态成员
//
//class Person
//{
//public:
//	string _name;
//	static int _count;
//};
//
//int Person::_count = 0;
//
//class Student : public Person
//{
//protected:
//	int _stuNum;
//};
//
//int main()
//{
//	Person p;
//	Student s;
//	cout << &p._name << endl;
//	cout << &s._name << endl;
//
//
//	cout << &p._count << endl;
//	cout << &s._count << endl;
//
//	p._count++;
//	s._count++;
//	Person::_count++;
//	Student::_count++;
//	cout << Person::_count << endl;
//	//cout << Person::_name << endl;
//
//	cout << Student::_count << endl;
//	//cout << Student::_name << endl;
//
//	return 0;
//}

// 菱形继承
class Person
{
public:
	Person(const char* name)
		:_name(name)
	{}

	string _name;
	//static int _count;
};

class Student : virtual public Person
{
public:
	Student(const char* name,int num)
		:Person(name)
		,_num(num)
	{}
protected:
	int _num; //学号​
};

class Teacher : virtual public Person
{
public:
	Teacher(const char* name, int id)
		:Person(name)
		, _id(id)
	{}
protected:
	int _id; // 职工编号​
};

class Assistant : public Student, public Teacher
{
public:
	Assistant(const char* name1, const char* name2, const char* name3)
		:Person(name3)
		, Student(name1, 1)
		, Teacher(name2, 2)
	{}

protected:
	string _majorCourse; // 主修课程​
};

int main()
{
	//// 编译报错：error C2385: 对“_name”的访问不明确​
	//Assistant a;
	
	////访问的是同一个 _name
	//a._name = "peter";
	//// 需要显示指定访问哪个基类的成员可以解决二义性问题，但是数据冗余问题无法解决​
	//a.Student::_name = "xxx";
	//a.Teacher::_name = "yyy";

	// _name的结果是 王五，Person()先初始化， student和teacher的person(name)不会进去，但必须写
	Assistant a("张三", "李四", "王五");

	return 0;
}