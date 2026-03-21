# 💒sting

## 🧸练习

### 💜写一个简单的string

```c++
namespace luo
{
	class string
	{
	public:
		//构造函数
		string(const char* str)
			:_str(new char[strlen(str)+1])
		{
			strcpy(_str, str);
		}
		//析构函数
		~string()
		{
			delete[] _str;
			_str = nullptr;
		}
	private:
		char* _str;
	};
	void test_string1()
	{
		string s1("hello world");
		
	}
}
```

### 💜构造函数

#### 🌸s1("hello")

**浅拷贝**(s1、s2指向同一块空间)

当对象出作用域后，同一块空间将析构两次，则会出现错误

```c++
//s1("hello")
string(const char* str)
    :_str(new char[strlen(str)+1])//开空间
{
    strcpy(_str, str);//按字符拷贝，包括\0
}
```

#### 🌸strcpy()

```c++
char * strcpy ( char * 目标, const char * 源);
将源指向的C字符串复制到目标指向的数组中，包括终止的字符(并在该点停止)；
```

#### 🌸s1(s2)

**深拷贝**：开空间后在拷贝

```
//s2(s1)
string(const string& s)
    :_str(new char[strlen(s._str)+1])
{
    strcpy(_str, s._str);
}
```

#### 🌸s3 = s1

```c++
//s3 = s1
string& operator=(const string& s)
{
    //避免自己赋值自己 判断一下
    if (this != &s)
    {
        char* tmp = new char[strlen(s._str) + 1];
        strcpy(tmp,s._str);
        delete[] _str;
        _str = tmp;
    }
    return *this;
}
```

### 💜问题：

浅拷贝造成的 问题如何解决？

先开好自己的空间 ，再strcpy数据。

## 🧸string类实现

```c++
private:
    char* _str;
    size_t _size;//存储有效字符
    size_t _capacity;//显示能存储的有效空间，排除\0
```

### 💜构造函数

#### 🌸string(const char* str)

```c++
//构造函数
// "\0"的效果相同 这里不能给nullptr ""常量字符串默认添加\0
// 因为strlen 直接解引用访问就会 造成空指针
string(const char* str = "")//带缺省值如果是空str 则用缺省值，""里是\0
    :_size(strlen(str))//strlen("\0") == 0
    ,_capacity(_size)//拷贝构造，str多大，capacity就多大
{
    _str = new char[strlen(str) + 1];
    strcpy(_str, str);
}
```

#### 🌸string(const string& s)

```c++
//s2(s1) sting参数
string(const string& s)
    :_size(s._size)//s2.size = s1.size
    ,_capacity(s._capacity)//s2.capacity = s1.capacity
{
    _str = new char[strlen(s._str) + 1];//开空间，多开一个为\0准备
    strcpy(_str, s._str);
}
```

复用string(const char* str)

```c++
string(const string &s)
	:_str(nullptr)
	,_size(0)
	,_capacity(0)
{
	string tmp(s._str);//复用string(const char* str)
	//this->swap(tmp);
	swap(tmp);//swap在下面
}
```

### 💜析构函数

#### 🌸~string()

```c++
~string()
{
	delete[] _str;
	_str = nullptr;
	_size = _capacity = 0;
}
```



### 💜迭代器

#### 🌸begin()

是char*类型，指向string的第一个字符

迭代器返回的是 迭代器(iterator)类型

```c++
typedef char*iterator;
typedef const char*const_iterator;
const_iterator begin() const
{
	return _str;
}
iterator begin() 
{
	return _str;
}
```

#### 🌸end()

是char*类型，指向string的最后一个字符的下一个位置

```c++
typedef char*iterator;
typedef const char*const_iterator;
const_iterator end() const
{
	return _str + _size;
}
iterator end()
{
    return _str + _size;
}
```

### 💜成员函数

#### 🌸clear()

//清理数据/不清理空间

```c++
void clear()
{
    _str[0] = '\0';
    _size = 0;
}
```



#### 🌸swap()

交换函数

```c++
void swap(string &s)
{
	std::swap(_str,s._str);//指定std里的swap
	std::swap(_size,s._size);
	std::swap(_capacity,s._capacity);
}
```

#### 🌸c_str()

char*类型 返回c类型字符串，包含\0

因为_str是私有的，访问不到，所以有了c_str();又因为这个字符串不支持修改，所以返回const类型  ，而后面的const修饰的是this指针，this指针内容不能被修改

```c++
//c_str 遇到\0结束
const char* c_str() const
{
	return _str;
}
```

#### 🌸size()

size_t类型，返回的是string类型创建的对象，的有效字符，不包含\0

```c++
size_t size() cosnt
{
	return _size;
}
```

#### 🌸operator[]:访问函数

返回的是 char&, 引用返回，则首先可以减少拷贝，其次可以修改返回的参数

```c++
char& operator[](size_t pos)
{
	assert(pos<_size);
	return _str[pos];
}
const char& operator[](size_t pos) const
{
	assert(pos<_size);
	return _str[pos];
}
```

#### 🌸reverse():扩容

只扩容，不初始化，当n<capacity,不会缩容

```c++
void reverse(size_t n)
{
	//判断一下，只增容，不缩容
	if(n>_capacity)
	{
		char* tmp = new char[n+1];//有效字符+\0
		strcpy(tmp ,_str);
		delete[] _str;
		_str = tmp;
		_capacity = n;
	}
}
```

#### 🌸resize():扩容+初始化

扩容的同时 默认将扩容的空间初始化为0；

可以给定值初始化

如果n<capacity,不会缩容，但是会将有效字符size 减少到n个

```
void resize(size_t n,char ch = '\0')
{
	if(n < _size)
	{
		_size = n;
		_str[_size] = '\0';
	}
	else
	{
		if(n > _capacity)
		{
			reverse(n);
		}
		memset(_str + _size,ch,n - _size);//起始位置，字符，拷贝多少个字符
		_size = n;
		_str[_size] = '\0';
		
	}
}
```

#### 🌼memset

```
void * memset ( void * ptr, int value, size_t num );
```

填充内存块

*将ptr*指向的内存块 的前*num*字节设置为指定*值*value（解释为`unsigned char`）。

#### 🌸insert()

在pos前插入ch

```c++
string& insert(size_t pos,char ch)
{
	assert(pos <= _size);
	if(_size == _capacity)
    {
        reverse(_capacity == 0? 4:_capacity*2);
    }
    size_t end = _size+1;
    //挪动数据
    while(end>pos)
    {
    	_str[end] = _str[end-1];
    	--end;
    }
    _str[pos] = ch;
    ++_size;
    
    return *this;
}
```

```c++
string& insert(size_t pos, const char* s)
{
    assert(pos <= _size);
    size_t len = strlen(s);
    if (_size + len > _capacity)
    {
        reverse(_size + len);
    }
    //挪动数据 给s留出位置
    size_t end = _size + len;
    while (end> pos+len)//小心越界，画图可知
    {
        _str[end] = _str[end - len];
        --end;
    }
    strncpy(_str + pos, s, len);
    _size += len;
    return *this;
}
```

#### 🌼strncpy

```
char * strncpy ( char * 目标, const char * 源, size_t num );
```

从字符串中复制字符

将 *源* 的前*num*个字符 复制到*目标*。

#### 🌸push_back()

尾插

```c++
void push_back(char ch)
{
	if(_size == _capacity)
    {
        //增容  为了避免capacity一开始就是0
        reverse(_capacity == 0? 4:_capacity*2);
    }
    _str[_size] = ch;
    ++_size;
    _str[_size] = '\0';
}

void push_back(char ch)
{
 	insert(_size,ch);   
}
```

#### 🌸append()

追加字符串

```c++
void append(const char* str)
{
    size_t len = strlen(str);
    if (_size+len > _capacity)
    {
        reverse(_capacity * 2);
    }
    strcpy(_str + _size, str);
    _size += len;
}

void append(const char* str)
{	
    insert(_size,str);//string& insert(size_t pos, const char* s)
}
```

#### 🌸find 

查找第一次出现的字符

当指定*pos*时，搜索仅包括位置*pos*或之后的字符，返回该字符串的下标

```c++
class luo
{
	size_t find(char ch)
	{
		for(size_t i = 0;i<_size;++i)
		{
			if(ch == _str[i])
			{
				return i;
			}
		}
		return npos;
	}
    size_t find(const char* s ,size_t pos = 0)
    {
    //ptr记录 s第一次出现的位置  _str+pos是查找的起始位置
        const char* ptr = strstr(_str + pos,s);
        //当strstr查找失败 则返回空指针
        if(ptr == nullptr)
        {
            return npos;//-1
        }
        else
        {
        	return ptr - _str;//两个指针相减的得到的是 闭区间的元素个数 0-3 = 3
        	//也就是返回了下标3
        }
    }

private:
    char* _str;
    size_t _size;
    size_t _capacity; // 能存储有效字符的空间数，不包含\0

    static const size_t npos;
};

const size_t string::npos = -1;
```

测试返回的位置

```c++
int main()
{
	//luo::test_string1();
	string s1("abcdef");
	size_t pos = s1.find('c');
	cout << pos << endl;  //pos == 2
	return 0;
}
```

> 
>
> <img src="https://picgo-1311604203.cos.ap-beijing.myqcloud.com/image/202206260943904.png"/>

#### 🌼strstr

```
const char * strstr ( const char * str1, const char * str2 );
      char * strstr (       char * str1, const char * str2 );
```

返回指向 str1 中第一次出现*str2*的指针，如果*str2*不是 str1 的一部分，则*返回**空*指针。 匹配过程不包括终止的空字符，但它会停在那里。

#### 🌸erase

删除pos位置后的len个字符

```c++
string& erase(size_t pos = 0, size_t len = npos)
{
    assert(pos < _size);
    //第一种情况 要删除的数据超出了size则全部删除
    if (len == npos || len + pos > _size)
    {
        _str[pos] = '\0';//设置标识符
        _size = pos;//减少size
    }
    //第二种情况，删一部分，将后面没删完的往前挪
    else
    {
        strcpy(_str + pos, _str + pos + len);//这里会自动将之前的\0拷贝
        _size -= len; //删了len个字符，减len
    }
    return *this;
}
```

#### 🌼strcmp

```
int strcmp ( const char * str1, const char * str2 );
```

比较两个字符串

将 C 字符串*str1*与 C 字符串*str2*进行比较。

返回一个整数值，表示字符串之间的关系：

| 返回值 | 表示                                               |
| ------ | -------------------------------------------------- |
| `<0`   | 第一个不匹配的字符在*ptr1*中的值低于在*ptr2中的值* |
| `0`    | 两个字符串的内容相等                               |
| `>0`   | 第一个不匹配的字符在*ptr1*中的值大于在*ptr2中的值* |

### 💜赋值函数

#### 🌸operator=

```c++
//s3 = s1
string& operator=(const string& s)
{
    //避免自己赋值自己 判断一下
    if (this != &s)
    {
        //先开空间，开成功再赋值，不然先delete，new失败了，原来的数据也没了
        char* tmp = new char[strlen(s._str) + 1];
        strcpy(tmp, s._str);
        delete[] _str;
        _str = tmp;
        _size = s._size;
        _capacity = s._capacity;
    }
    return *this;
}
```

#### 🌸operator+=

尾部追加字符 或 字符串

因为 加等 的需要有返回值  例如 s2 += s3

```c++
string& operator+=(char ch)
{
	push_back(ch);//复用尾插
	return *this;
}

string& operator+=(const char* str)
{
	append(str);//复用追加字符串
	return *this;
}
```

#### 🌸写了 < 和 == 其他就可以复用了

#### 🌸operator<

```c++
bool operator<(const string& s1, const string& s2)
{
    size_t i1 = 0, i2 = 0;
    while (i1 < s1.size() && i2<s2.size())
    {
        if (s1[i1] < s2[i2])
        {
            return true;
        }
        else if (s1[i1] > s2[i2])
        {
            //大于 false
            return false;
        }
        else
        {
            //相等则继续比
            ++i1;
            ++i2;
        }
    }
    // "abcd"  =  "abcd"  false
    // "abcd"  <  "abcde" true
    // "abcde" >  "abcd"  false 
    return i2 < s2.size() ? true : false;
}

bool operator<(const string& s1, const string& s2)
{
    return strcmp(s1.c_str(), s2.c_str()) < 0;
}
```

#### 🌸operator==

```c++
bool operator==(const string& s1, const string& s2)
{
    return strcmp(s1.c_str(), s2.c_str()) == 0;
}
```

#### 🌸operator<<

流提取 ，范围for必须有迭代器支持

```c++
//要有返回值 cout<<s1 -> operator(cout,s1)
ostream& operator<<(ostream& out, const string& s)
{
    for (auto& ch : s)
    {
        out << ch;
    }
    return out;
}
//写法2
ostream& operator<<(ostream& out, const string& s)
{
    for (size_t i = 0; i < s.size(); i++)
    {
        out << s[i];
    }
    return out;
}	
```

#### 🌸operator>>

```c++
istream& operator>>(istream& in,string& s)//s不能是const
{
    //先清理，不清除的话，原有的数据还保留
    s.clear();
    char ch = in.get();
    //遇到空格 换行结束
    while (ch != ' ' || ch != '\n')
    {
        s += ch;
        ch = in.get();
    }
    return in;
}
```

