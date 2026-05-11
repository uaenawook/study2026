#include<iostream>
using namespace std;


// 2026.5.11
/*
	类继承
		继承的访问限定符权限是怎样的
		继承方式 和 父类 取权限小的继承

		隐藏、和重载的区别
			重载的定义，在同一作用域的不同明函数
			

			类中 父类和子类的变量名相同、函数名相同 构成什么？
			父类和子类的同名变量和同名函数构成隐藏、析构函数也构成隐藏

		切片概念

			子类给父类
				子类 赋值给父类时会自动把继承父类的参数赋值给父类
				子类独有的参数会被切除
					Person p1 = s1;
					Person* p2 = &s1;
					Person& p3 = s1;

			父类给子类
				父类的对象 给不了 子类
				但是 指针 和引用可以给子类，需要强转
					//Student s2 = (Student)p4;
					Student* ps1= (Student*)p2;
					Student& ps2= (Student&)p3;
				
			哪个可以给，哪个需要强转，产生临时对象吗？
				父类对象、引用、指针 可以接收子类，不产生临时对象
				子类接收父类指针和引用时，父类需要强转成子类类型

		构造、拷贝构造、赋值、析构 需要如何调用、调用顺序
			构造、拷贝构造、赋值 需要显示调用父类的
				:Person(name, address, tel, age)
				初始化列表顺序是先调用父类构造，再走子类的初始化，按照定义的顺序初始化


			析构不用显示写，编译器自动调用
				析构是先析构子类再析构父类
				后定义的先析构
			

*/


class Person
{
public:
	Person(const string& name, const string& address, const string& tel, const int& age)
		:_name(name)
		,_address(address)
		,_tel(tel)
		,_age(age)
	{

	}
	void identity()
	{
		cout << "identity()" << endl;
	}

protected:
	string _name = "张三";
	string _address = "内蒙";
	string _tel = "1234";
	int _age =20;
};


//class Student:public Person
//class Student: Person // 此处不写public class默认private  
					  // s1.identity();“Person::identity”不可访问，因为“Student”使用“private”从“Person”继承	2026.05.11继承
struct Student : Person // 此处不写public struct默认public 
{
public:
	Student(const string& name, const string& address, const string& tel, const int& age)
		:Person(name, address, tel, age)
	{

	}
	void study()
	{
		cout << _age << endl;
	}
protected:
	int _stuid = 0001;
};

class Teacher :public Person
{
public:
	Teacher(const string& name, const string& address, const string&tel,const int& age,const string& title)
		:Person(name, address, tel,age)
		,_title(title)
	{

	}

protected:
	string _title = "教师";
};

//int main()
//{
//	Student s1("张三","内蒙","6666",20);
//	Teacher t1("李四", "西安", "2222", 30,"教授");
//
//	//Person p1 = s1;
//	//Person* p2 = &s1;
//	//Person& p3 = s1;
//
//	//Person p4("王五", "北京", "999", 25);
//	////Student s2 = (Student)p4;
//	//Student* ps1= (Student*)p2;
//	//Student& ps2= (Student&)p3;
//	s1.study();
//	s1.identity();
//
//	return 0;
//}


#include<vector>
#include<list>
#include<deque>
namespace wx
{
	// 栈 先进后出 
	template <class T>
	class Stack:public std::vector<T>
	{
	public:
		void push(const T& x)
		{
			_con.push_back(x);
		}

		void pop()
		{
			_con.pop_back();
		}

		T& top()
		{
			return  _con.back();
		}
		const T& top() const
		{
			return  _con.back();
		}

		bool empty() const
		{
			return _con.empty();
		}

		size_t size() const
		{
			return _con.size();
		}





	private:
		vector<T> _con;
	};
}

//int main()
//{
//	wx::Stack<int> s1;
//	s1.push(1);
//	s1.push(2);
//	s1.push(3);
//	while (!s1.empty())
//	{
//		cout << s1.top()<< " ";
//		s1.pop();
//	}
//	cout << endl;
//
//
//
//	return 0;
//}


namespace wx2
{
	//template<class T>
	//class vector
	//{};
	// stack和vector的关系，既符合is-a，也符合has-a​
	template<class T>
	class stack : public std::vector<T>
	{
	public:
		void push(const T& x)
		{
			// 基类是类模板时，需要指定一下类域，​
			// 否则编译报错:error C3861: “push_back”: 找不到标识符​
			// 因为stack<int>实例化时，也实例化vector<int>了​
			// 但是模版是按需实例化，push_back等成员函数未实例化，所以找不到​
			vector<T>::push_back(x);
			//push_back(x);
		}
		void pop()
		{
			vector<T>::pop_back();
		}
		const T& top()
		{
			return vector<T>::back();
		}
		bool empty()
		{
			return vector<T>::empty();
		}
	};
}
int main()
{
	wx2::stack<int> st;
	st.push(1);
	st.push(2);
	st.push(3);
	while (!st.empty())
	{
		cout << st.top() << " ";
		st.pop();
	}
	return 0;
}