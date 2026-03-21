# string

## 模板：



### 泛型编程

#### 函数模板

```c++
模板关键字：tmplate<calss T> //T可以随意改
template<class T> //template<typename T> 模板参数列表 - 参数类型
void Swap(T& x1, T& x2) //函数参数列表 - 参数对象
{
	T x = x1;
	x1 = x2;
	x2 = x;
}
传入不同的类型 会调用不同的实例化函数
多个类型：
    template<class T1,class T2>
```

#### 模板实例化

调用Swap时 会实例化出不同类型的函数
**实例化**：是指在面向对象的编程中，把用类创建对象的过程称为实例化。 是将一个抽象的概念类，具体到该类实物的过程。 实例化过程中一般由类名对象名= new 类名（参数1，参数2...参数n）构成。

#### 函数模板的实例化

```c
template<class T>
T Add(const T& left, const T& right)//做返回值 和
{
    return left + right;
}
int main()
{
    int a1 = 10, a2 = 20;
    double d1 = 10.1, d2 = 20.2;
    cout << Add(a1, a2) << endl;
    cout << Add(d1, d2) << endl;
    
    cout << Add((double)a1, d2) << endl;
    
    //显示实例化
    cout << Add<int>(d1, d2) << endl; //指定类型
    cout << Add<double>(d1, d2) << endl; 
    
    return 0;
}
结果：
30
30.3
30.2
30
30.3
```

**如果函数模板 和 普通函数 同时存在，优先使用普通函数**

### 类模板

一个栈类型 只能是 int 或 double 或...
定义对象只能满足 int栈 或者double栈
想要存储多个类型 则需要建多个不同类型的 类

```c
template<class T>
class Stack
{
privvate:
    T* _a;
    int _top;
    int _capacity;
}
int main()
{
    Stack<int> st1;//存储int
    Stack<double> st2;//存储double
}
```



### 函数模板



```c++
//定义参数类型 T - Type
template<class T>  //template<typename T> 
void Swap(T& x1,T& x2)
{
	T x = x1;
	x1 = x2;
	x2 = x;
}
//多个类型
template<class T1，class T2>

```

#### 函数模板实例化

将不同类型，替换到函数中，实例出一个新的固定类型的函数，然后进行调用！

#### 显示实例化

```c++
int a = 10;
double b = 20.2;
Add<int>(a1,d2);//指定类型
```

1.函数模板和普通模板都实现，优先普通模板

> 当普通函数只有声明，没有定义时，会报错

```c++
viod swap(int a,int b);
template<class T>
void swap(T a,T b)
{}
int main()
{
	int a = 10, b = 20;
	swap(a,b);
}//此时 会优先调用 普通函数，但是会报错，因为普通函数只有声明，没有定义！
```

2.可以通过空模板参数列表强制调用函数模板

```c++
myswap<>(a,b);
```

3.函数模板可以重载

```c++
template<class T>
viod swap(T a,T b)
{}
template<class T>
void swap(T a,T b,T c)
{}
```

4.如果函数模板可以产生更好的匹配，有限调用函数模板

```c++
viod swap(int a,int b)
{}
template<class T>
void swap(T a,T b)
{}
int main()
{
	char a = 'a';
	char b = 'b';
	swap(a,b);//此时会调用函数 函数模板，因为普通函数还要隐式类型转换
}
```



### 类型模板

使用 

函数模板与类型模板的区别

1.函数模板可以推导类型，类型模板不能自动推导

```c++
template<class T1,class T2>
class Person
{
public:
    Person(T1 name,T2 age)
	{
		_name = name;
		_age = age;
	}
	T1 _name;
	T2 _age;
};
int main(){
	Person<string,int> p1("张三"，23);//只能显示指定类型，不能自动推导
    //Preson p("张三"，23);
}
```

2.类型模板可以写默认参数，函数模板不行！

```c++
template<class T1,class T2 = int>//缺省值
class Person
{
public:
    Person(T1 name,T2 age)
	{
		_name = name;
		_age = age;
	}
	T1 _name;
	T2 _age;
};
int main(){
	Person<string> p1("张三",23);
}
```

#### 类模板什么时候创建？

在调用的时候才会创建，不调用则编译的时候也不会创建，也不会出错。

#### 类名和类型

```
//Person 类名
//Person<T> 类型
template<class T>
class Person
{

}
```



## STL:

**S标准T模板L库**
Vue - 前端贡献：尤雨溪

### 书籍推荐 

《STL源码剖析》《effcrive C++》 继承多态学完看 《高质量C++》现在看

### STL 六大组件
算法、容器、迭代器、配接器、仿函数、空间配置器(内存池)

## string 成员函数

### c++文档：

https://cplusplus.com/

### 编码补充

编码 - 值 -- 符号建立映射
ASCII码表 - 表示英文编码表
unicode - 表示全世界文字编码表 utf-8
gbk - 中文编码表



### 常用的string 

- 赋值

|       default (1) | `string(); `                                                 |
| ----------------: | ------------------------------------------------------------ |
|          copy (2) | `string (const string& str); `                               |
|     substring (3) | `string (const string& str, size_t pos, size_t len = npos); ` |
| from c-string (4) | `string (const char* s);`                                    |

- [**size**](https://cplusplus.com/reference/string/string/size/)：计算长度

  Return length of string (public member function )

- [**capacity**](https://cplusplus.com/reference/string/string/capacity/)：计算空间大小 不算\0 所以是15

  Return size of allocated storage (public member function )

- [**clear**](https://cplusplus.com/reference/string/string/clear/)：清除string内容

  Clear string (public member function )

- [**reserve**](https://cplusplus.com/reference/string/string/reserve/)

  Request a change in capacity (public member function )

- [**operator[ ]**](https://cplusplus.com/reference/string/string/operator[]/):出错断言assert

  Get character of string (public member function )

  ```
        char& operator[] (size_t pos);
  const char& operator[] (size_t pos) const;
  这里的引用返回时为了 修改返回对象
  ```

  ```c++
  读取
  s1[i] = s1.operator[]  的重载
  ```

  > ![image-20220619201146602](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/image/202206192011736.png)

  ```
  修改
  s1[i]+=1;
  ```

  > <img src="https://picgo-1311604203.cos.ap-beijing.myqcloud.com/image/202206192015956.png" alt="image-20220619201539923" style="zoom:50%;" />

  

- [**at**](https://m.cplusplus.com/reference/string/string/at/)：获取字符串的字符，出错抛异常

  Get character in string (public member function)

- [**operator+=**](https://m.cplusplus.com/reference/string/string/operator+=/)：尾插字符或字符串

  Append to string (public member function)

  ```c++
  string s1;
  s1 += ':';
  s1 += "hello world";
  cout << s1 << endl;
  ```

- [**append**](https://m.cplusplus.com/reference/string/string/append/)：尾插字符串 不常用

  Append to string (public member function)

- [**push_back**](https://m.cplusplus.com/reference/string/string/push_back/)：尾插字符 不常用

  Append character to string (public member function)

```c++
string s1;
s1.push_back('a');
s1.append("bcde");
cout << s1 << endl;
```

## string 迭代器



```
	//遍历+修改
	//方式1：下标+[]  
	//返回对应位置的引用  可以直接修改s1[i]
	for (size_t i = 0; i < s1.size(); ++i)
	{
		s1[i] += 1;
	}
	for (size_t i = 0; i < s1.size(); ++i)
	{
		cout << s1[i] << " ";
	}
	cout << endl;
```

迭代器想象成：像指针一样的类型

### end()/begin()

```c++
typedef char*iterator;
typedef const char*const_iterator;

		iterator begin();
const_iterator begin() const;

      iterator end();
const_iterator end() const;
```

```c++
string s1("hello world");
//方式2：迭代器(iterator)
//begin()指的是第一个元素的位置  end()是最后一个元素的【下一个】
//it像指针一样指向第一个元素 ，可以解引用，可以++
string::iterator it = s1.begin();
while (it != s1.end())
{
    *it -= 1;
    ++it;
}
it = s1.begin();//重置it的位置
while (it != s1.end())
{
    cout << *it << " ";
    ++it;
}
cout << endl;
```

### iterator begin();

范围for会替换成迭代器

```c++
//方式3：范围for   语法糖用起来很爽很甜
// C++11   linux：-std=c++11
//把s1中的值取出来 赋值给e 自动++
//for (char& e : s1) 
for (auto& e : s1) //引用  
{
    e += 1;
}
for (auto e:s1)
{
    cout << e << " ";
}
cout << endl;
```

### const_iterator begin() const;

const 版本只能读取 不能修改

```c++
void func(const string& s1)
{
	string::const_iterator it = s1.begin();
	//auto it = s1.cbegin(); //cbegin()和cend()代表const
	while (it != s1.end())
	{
		//*it -= 1; //不能修改
		cout << *it << " ";
		++it;
	}
	cout << endl;
}
```



### rbegin()  / rend(): 反向迭代器 

```c++
      reverse_iterator rbegin();
const_reverse_iterator rbegin() const;
```

- **rbegin() 最后一个字符**
- **rebing()的 ++ 是向前走**
- **rend()是第一个字符的前一个**

```c++
void test_string2()
{
	string s1("hello world");
	//反向迭代器
	//rbegin() 指向最后一个字符 
	//
	//反向++ 是逆向的
	//string::reverse_iterator rit = s1.rbegin(); // string::reverse_iterator是类型
	auto rit = s1.rbegin();//代替上面那句自动推到类型
	while (rit != s1.rend())
	{
		cout << *rit << " ";
		++rit;
	}
	cout << endl;

	string cstr("hello world");
	func(cstr);
}
```

### c++11 新增const迭代器

- [**cbegin**](https://m.cplusplus.com/reference/string/string/cbegin/)

- [**cend**](https://m.cplusplus.com/reference/string/string/cend/)

- [**crbegin**](https://m.cplusplus.com/reference/string/string/crbegin/)

- [**crend**](https://m.cplusplus.com/reference/string/string/crend/)

### 迭代器的意义是什么？

> **所有的容器都可以使用迭代器这种方式去访问修改**

#### 答：

对于string，下标和[]就足够好用，确实可以不用迭代器。

#### **其他容器(数据结构)呢？**

(list、map/set 并不支持下标，只有数组才支持[]，这些是链表和二叉树并不支持下标+[])

>  **所以迭代器才是通用的方式**

## string 增容

### 测试代码

```c++
void TestPushBack()
{
	string s;
	//s.reserve(1000);//申请至少能存储10000个字符的空间  不一定是1000 要空间对其

	size_t sz = s.capacity();
	cout << "capacity changed: " << sz << '\n';
	cout << "making s grow:\n";
	for (int i = 0; i < 2000; ++i)
	{
		s.push_back('c');
		if (sz != s.capacity())
		{
			sz = s.capacity();
			cout << "capacity changed: " << sz << '\n';
		}
	}
}
```

结果

```c++
capacity changed: 15	//本质是16 但是没算\0  有效字符位置有15个
making s grow:
capacity changed: 31	//本质是32 但是没算\0  有效字符位置有31个
capacity changed: 47
capacity changed: 70
capacity changed: 105
capacity changed: 157
capacity changed: 235
```

### [**reserve**](https://m.cplusplus.com/reference/string/string/reserve/)**：扩容，只开空间**

### [**resize**](https://m.cplusplus.com/reference/string/string/resize/)**：扩容+初始化**

**开空间，并给初始值 进行初始化**

如果resize扩容比已有数据少，则会删除多余数据，不会改变空间大小

reverse也不会缩容

```c++
void test_string3()
{
	string s1;
	s1.reserve(100);
	//开空间并初始化
	string s2;
	//s2.resize(100); // 初始化的 \0
	s2.resize(100,'x');//指定字符初始化
	//resize不会把已有数据覆盖初始化，如果比已有数据小，则会除多余的数据
}
```

## string 查找

### [**c_str**](https://m.cplusplus.com/reference/string/string/c_str/)：**返回C格式字符串**

```c++
const char* c_str() const;
```

```c++
void test_string4()
{
	string s("hello world");
	cout << s << endl;//流插入  size是多少 打印多少
	cout << s.c_str() << endl;//const char*  遇到\0结束
    
    //应用场景 这里fopen的第一个参数需要const char*类型的字符串
    string file("test.txt");
	FILE* fout = fopen(file.c_str(), "w");
}
```

[**find**](https://m.cplusplus.com/reference/string/string/find/)：找位置

：**从字符串pos位置开始往后找字符c，返回该字符在字符串中的下标**

|    string (1) | `size_t find (const string& str, size_t pos = 0) const; `   |
| ------------: | ----------------------------------------------------------- |
|  c-string (2) | `size_t find (const char* s, size_t pos = 0) const; `       |
|    buffer (3) | `size_t find (const char* s, size_t pos, size_t n) const; ` |
| character (4) | `size_t find (char c, size_t pos = 0) const;`               |

> ![image-20220626094342788](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/image/202206260943904.png)

### [**npos**](https://m.cplusplus.com/reference/string/string/npos/)：-1

：**size_t类型的 -1 一个很大的数**

### [**substr**](https://m.cplusplus.com/reference/string/string/substr/)：查找字符串

：**在str中从pos位置开始，截取n个字符，然后将其返回**

```c++
string substr (size_t pos = 0, size_t len = npos) const;
```

```c++
string file("test.txt");
FILE* fout = fopen(file.c_str(), "w");
size_t pos = file.find('.');
if (pos != string::npos)//npos是 -1  size_t全1
{
    //string suffix = file.substr(pos, file.size() - pos);
    string suffix = file.substr(pos);//直接用默认缺省值 取到最后
    cout << suffix << endl;
}
```

**如果是连续后缀 ，要从右往左找**

### [**rfind**](https://m.cplusplus.com/reference/string/string/rfind/)：**反向找**

```c++
	string file("test.txt.zip");
	FILE* fout = fopen(file.c_str(), "w");
	size_t pos = file.rfind('.');//这里用rfind
	if (pos != string::npos)
	{
		string suffix = file.substr(pos);
		cout << suffix << endl;
	}
}
```

- **解析URL**

  ```c++
  	string url("https://www.cplusplus.com/reference/string/string/rfind/");
  	//取协议
  	size_t pos1 = url.find(':');
  	string protocol = url.substr(0, pos1 - 0);
  	cout << protocol << endl;
  	//取域名
  	size_t pos2 = url.find('/',pos1+3);//冒号+3是w的位置开始找/ 
  	string domain = url.substr(pos1 + 3,pos2-(pos1+3));
  	cout << domain << endl;
  	//取路径
  	string uri = url.substr(pos2 + 1);//从域名后的/ +1 的位置找到最后
  	cout << uri << endl;
  
  https
  www.cplusplus.com
  reference/string/string/rfind/
  ```

## string 插入删除

### [**insert**](https://m.cplusplus.com/reference/string/string/insert/)：**插入**

|           string (1)** | ` string& insert (size_t pos, const string& str); `          |
| ---------------------: | ------------------------------------------------------------ |
|          substring (2) | ` string& insert (size_t pos, const string& str, size_t subpos, size_t sublen); ` |
|           c-string (3) | ` string& insert (size_t pos, const char* s); `              |
|             buffer (4) | ` string& insert (size_t pos, const char* s, size_t n); `    |
|             fill (5)** | ` string& insert (size_t pos, size_t n, char c);    void insert (iterator p, size_t n, char c); ` |
| single character (6)** | `iterator insert (iterator p, char c); `                     |
|              range (7) | `template <class InputIterator>   void insert (iterator p, InputIterator first, InputIterator last);` |

```c++
void test_string5()
{
	string s("hello world");
	s += ' ';//尾插
	s += "!!!";
	cout << endl;
	//头插 效率低 O(N) 尽量少用
	s.insert(0, 1, 'x');//在0的位置插入1个x
	s.insert(s.begin(), 'y');//在头部插入y
	s.insert(0, "test");//在0的位置插入test
	cout << s << endl;
	//中间位置插入，尽量少用
	s.insert(4, "&&&&&&");
	cout << s << endl;
}
```



### [**erase**](https://m.cplusplus.com/reference/string/string/erase/)：**删除**

| sequence (1)** | ` string& erase (size_t pos = 0, size_t len = npos); ` |
| -------------: | ------------------------------------------------------ |
|  character (2) | `iterator erase (iterator p); `                        |
|      range (3) | `     iterator erase (iterator first, iterator last);` |

```c++
void test_string6()
{
	string s("hello world");
	//尽量少用头部和中间的删除，效率低
	s.erase(0,1);//删除头上的一个字符
	s.erase(s.size()-1,1);//删除尾部的一个字符
	cout << s << endl;
    s.erase(3);//从第三个位置 后面全部删除
	cout << s << endl;
}
```

### [**operator+**](https://m.cplusplus.com/reference/string/string/operator+/)：**加**

字符串相加，返回新的字符串

```c++
// concatenating strings
#include <iostream>
#include <string>

main ()
{
  std::string firstlevel ("com");
  std::string secondlevel ("cplusplus");
  std::string scheme ("http://");
  std::string hostname;
  std::string url;

  hostname = "www." + secondlevel + '.' + firstlevel;
  url = scheme + hostname;

  std::cout << url << '\n';

  return 0;
}

输出：http://www.cplusplus.com
```



## [**getline**](https://m.cplusplus.com/reference/string/string/getline/)：**连续获取一行字符串**

**方法一的代码就是getline的原理，一个字符一个字符的获取！**

|  (1) | `istream& getline (istream& is, string& str, char delim); ` |
| ---: | ----------------------------------------------------------- |
|  (2) | `istream& getline (istream& is, string& str);`              |

[字符串里面最后一个单词的长度](https://www.nowcoder.com/practice/8c949ea5f36f422594b306a2300315da?tpId=37&&tqId=21224&rp=5&ru=/activity/oj&qru=/ta/huawei/question-ranking)

```c++
#include <iostream>
using namespace std;

int main()
{
    string s;
    //cin>>s;//cin读到空格或换行结束 scanf同理
    //方法一：一个字符一个字符拿
//     char ch = getchar();
//     //char ch = cin.get();
//     while(ch!='\n')
//     {
//         s+=ch;
//         ch = getchar();
//     }
    //方式二：
    getline(cin,s);
    
    size_t pos = s.rfind(' ');
    if(pos == string::npos)
    {
        cout <<s.size()<<endl;
    }
    else{
        cout << s.size() - pos-1;
    }
    return 0;    
}
```

## string 比较大小

[**relational operators**](https://m.cplusplus.com/reference/string/string/operators/)：**比较大小**

|  (1) | `bool operator== (const string& lhs, const string& rhs); bool operator== (const char*   lhs, const string& rhs); bool operator== (const string& lhs, const char*   rhs); ` |
| ---: | ------------------------------------------------------------ |
|  (2) | `bool operator!= (const string& lhs, const string& rhs); bool operator!= (const char*   lhs, const string& rhs); bool operator!= (const string& lhs, const char*   rhs); ` |
|  (3) | `bool operator<  (const string& lhs, const string& rhs); bool operator<  (const char*   lhs, const string& rhs); bool operator<  (const string& lhs, const char*   rhs); ` |
|  (4) | `bool operator<= (const string& lhs, const string& rhs); bool operator<= (const char*   lhs, const string& rhs); bool operator<= (const string& lhs, const char*   rhs); ` |
|  (5) | `bool operator>  (const string& lhs, const string& rhs); bool operator>  (const char*   lhs, const string& rhs); bool operator>  (const string& lhs, const char*   rhs); ` |
|  (6) | `bool operator>= (const string& lhs, const string& rhs); bool operator>= (const char*   lhs, const string& rhs); bool operator>= (const string& lhs, const char*   rhs);` |

```c++
void test_string7()
{
	string s1("hello world");
	string s2("string");
	const char* ps = "char";

	cout << (s1 < s2) << endl;//1
	cout << (s1 < ps) << endl;//0
	cout << ("hhh" < s2) << endl;//1
	cout << (s1 < "sss") << endl;//1
}
```

## C++11 补充

### [**stoi** ](https://cplusplus.com/reference/string/stoi/)：str转int

```c+
int stoi (const string&  str, size_t* idx = 0, int base = 10);
int stoi (const wstring& str, size_t* idx = 0, int base = 10);
```

```c+
	int val = stoi("1234");
	cout << val << endl;
```

- [**stoi** ](https://cplusplus.com/reference/string/stoi/)

- [**stol** ](https://cplusplus.com/reference/string/stol/)

- [**stoul** ](https://cplusplus.com/reference/string/stoul/)

- [**stoull** ](https://cplusplus.com/reference/string/stoull/)[**stof** ](https://cplusplus.com/reference/string/stof/)

- [**stod** ](https://cplusplus.com/reference/string/stod/)

- [**stold** ](https://cplusplus.com/reference/string/stold/)

### [**to_string** ](https://cplusplus.com/reference/string/to_string/)：int 转 str

```c++
string to_string (int val);
string to_string (long val);
string to_string (long long val);
string to_string (unsigned val);
string to_string (unsigned long val);
string to_string (unsigned long long val);
string to_string (float val);
string to_string (double val);
string to_string (long double val);
```

```c++
	string str = to_string(3.14);
	cout << str << endl;//3.140000
```

## 练习题

### [125. 验证回文串](https://leetcode.cn/problems/valid-palindrome/)

```c++
class Solution {
public:
    bool isLeterOrNumber(char ch)
    {
        if(ch>='0' && ch<='9')
            return true;
        if(ch>= 'a' && ch<='z')
            return true;
        
        if(ch>='A' && ch<= 'Z')
            return true;
        return false;
    }
    bool isPalindrome(string s) {
        int begin = 0,end = s.size()-1;
        while(begin<end)
        {
            while(begin<end && !isLeterOrNumber(s[begin]))
                ++begin;
            while(begin<end && !isLeterOrNumber(s[end]))
                --end;

            if(tolower(s[begin]) != tolower(s[end]))            
                return false;
            ++begin;
            --end;
        }
        return true;
    }
};
```



### [415. 字符串相加](https://leetcode.cn/problems/add-strings/)

> ![image-20220621230055358](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/image/202206212301448.png)

```c++
class Solution {
public:
    string addStrings(string num1, string num2) {
        int end1 = num1.size()-1;int end2 = num2.size()-1;
        int next = 0;//计算进位
        string retStr;
        while(end1>=0 || end2>=0)
        {
            
            int X1 = 0;
            if(end1>=0)
            {
                X1 = num1[end1]-'0';
                --end1;
            } 
            int X2 = 0;
            if(end2>=0)
            {
                X2 = num2[end2]-'0';
                --end2;
            }
            int retVal = X1 + X2 + next;

            if(retVal > 9)
            {
                next = 1;
                retVal -= 10;
            }
            else
            {
                next = 0;
            }
            
            retStr += retVal+'0';

        } 
        if(next == 1)
        {
            retStr += '1';
        }
        reverse(retStr.begin(),retStr.end());
        return retStr;
    }
};
```

## 两个swap的区别？

### [**string::swap**](https://cplusplus.com/reference/string/string/swap/)：string专属

```c++
void swap (string& str);
```

### [std::swap](https://cplusplus.com/reference/utility/swap/?kw=swap)：全局

适用于内置类型

```c++
template <class T> void swap ( T& a, T& b )
{
  T c(a); a=b; b=c;
}
```

### 区别：

`string::swap` 对于string效率高，只交换资源，改变指针的指向

`std::swap` 对于string会拷贝构造c (深拷贝1)、a=b(深拷贝2)、b=c(深拷贝3) 进行三次string的深拷贝，代价极高

## 浅拷贝问题

1.浅拷贝会析构两次

2.期中一个对象进行修改会影响另一个

### 引用计数(解决浅拷贝)

> 如果对象不修改，则只增加了引用计数，不进行深拷贝，提高了效率
>
> 缺陷：引用计数存在线程安全问题，需要加锁，在多线程环境下要付出代价，在动态库、静态库中有些场景也会存在问题

当一块空间有多个指针指向，则会增加引用计数，例如2个指针指向 ，则引用计数是2

当指针析构的时候，引用计数不是1 则 会减减引用计数，直到只有一个指针的时候才析构

​		也就是说10指针指向a，前9个指着都不会析构a空间，只会减减引用计数，只有最后一个指针会析构a空间

### 写时拷贝

> insert/+=/erase等函数中，先查看引用计数，如果引用计数不是1，要先进性深拷贝，再去修改

当引用计数不是1 ，则进行写实拷贝，因为这块空间不是一个指针维护，所以不能修改



## 开区间取值

0 - 9 的下标是10个有效字符

所以算有效字符是size - 0  (size是最后一个字符的下一个)

## string 补充:vs下

```
class string
{
private:
	char _Buf[16];	//字符长度小于16，就存在这个数组_Buf中
	char* _Ptr; 	//大于等于16，就会去堆上申请,存在_Ptr中
	size_t _mySize;
	size_t _myRes;
}
sizeof()  //28字节
```

> ![image-20220701114058992](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/imageimage-20220701114058992.png)

> ![image-20220701114159833](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/imageimage-20220701114159833.png)

