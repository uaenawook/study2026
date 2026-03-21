## 1.0vector的介绍及使用

### vector的介绍

**[vector的文档介绍](https://cplusplus.com/reference/vector/vector/)**

> ![image-20220630083834744](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/imageimage-20220630083834744.png)

可改变size的顺序表！

|      |                                                    |
| ---- | -------------------------------------------------- |
| 优点 | 下标随机访问，尾插尾删效率高   (CPU高速缓存命中高) |
| 缺点 | 扩容(效率、空间浪费)、不适合头插头删               |



## 1.2 vector的使用

### 1初始化

> ```c++
> void test_vector1()
> {
> 	vector<int> v1;
> 	vector<int> v2(10, 8);//10个8初始化
> 	vector<int> v3(++v2.begin(), --v2.end());//迭代器区间
> 	vector<int> v4(v3);//迭代器区间
> 
> 	string s("hello world");//string 结尾有\0
> 	vector<char> v5(s.begin(), s.end());//vector 结尾没有\0
> }
> ```

### 2 迭代器

| iterator的使用                                               | 类型                                         | 接口说明                                                     |
| ------------------------------------------------------------ | -------------------------------------------- | ------------------------------------------------------------ |
| [begin](https://cplusplus.com/reference/vector/vector/begin/)+ [end](https://cplusplus.com/reference/vector/vector/end/) | iterator<br />const_iterator                 | 获取第一个数据位置的iterator/const_iterator， 获取最后一个数据的下一个位置 的iterator/const_iterator |
| [rbegin](https://cplusplus.com/reference/vector/vector/rbegin/) + [rend](https://cplusplus.com/reference/vector/vector/rend/) | reverse_iterator<br />const_reverse_iterator | 获取最后一个数据reverse_iterator，获取第一个数据前一个位置的 reverse_iterator |

> ![image-20220710175732221](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/imageimage-20220710175732221.png)

#### 迭代器遍历

##### **operator[] 遍历**

```c++
//遍历:
for (size_t i = 0;i<v.size();++i)
{
    v[i] += 1;
    cout << v[i] << ' ';
}
cout << endl;
```

##### **iterator 遍历**

```c++
//遍历：迭代器
vector<int>::iterator it = v.begin();
while (it != v.end())
{
    *it -= 1;
    cout << *it << " ";
    ++it;
}
cout << endl;
```

##### **范围for 遍历**

```c++
//遍历：范围for
for (auto e : v)
{
    cout << e << " ";
}
cout << endl;
```

##### **指针 遍历**

```c++
int a[] = { 1,2,3 };
//原生指针就是天然的迭代器，数组支持范围for，会被替换成指针
for (int* p = a; p < a + sizeof(a) / sizeof(int); ++p)
{
    //
}
```

### 迭代器分类

| 类型                   | 中文名     | 特点                | 迭代器                                                       | 参数是迭代器的对象                                           | 可传参数                 |
| ---------------------- | ---------- | ------------------- | ------------------------------------------------------------ | ------------------------------------------------------------ | ------------------------ |
| iterator               | 迭代器     |                     | 查看类的迭代器类型，<br />看iterator的类型                   |                                                              |                          |
| input_iterator         | 只写迭代器 |                     | 没有实际对应的类型                                           |                                                              | 单向<br />双向<br />随机 |
| output_iterator        | 只读迭代器 |                     | 没有实际对应的类型                                           |                                                              |                          |
| forwad_iterator        | 单向迭代器 | 只能++              | [**<forward_list>** ](https://cplusplus.com/reference/forward_list/forward_list/)<br />[**<unordered_set>** ](https://cplusplus.com/reference/unordered_set/)<br />[**<unordered_map>** ](https://cplusplus.com/reference/unordered_map/) |                                                              |                          |
| bidirectional_iterator | 双向迭代器 | ++ / --             | [**< list>**](https://cplusplus.com/reference/list/)<br />[**< map>**](https://cplusplus.com/reference/map/)<br />[**< set>**](https://cplusplus.com/reference/set/) | [**< reverse>**](https://cplusplus.com/reference/algorithm/reverse/?kw=reverse) | 随机<br />双向           |
| randomaccess_iterator  | 随机迭代器 | ++ /-- <br /> + / - | [**< deque>**](https://cplusplus.com/reference/deque/)<br />[**< vector>**](https://cplusplus.com/reference/vector/)<br />[**< string>**](https://cplusplus.com/reference/string/string/?kw=string)<br /> | [**< sort>**](https://cplusplus.com/reference/algorithm/sort/?kw=sort) | 随机                     |

查看迭代器类型

> ![image-20220630092300979](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/imageimage-20220630092300979.png)

### 迭代器失效

一般发生在`insert/erase`中

```c++
void test_vector4()
{
    //场景
    //1 2 3 4 5 -> 正常
    //1 2 4 5   -> 没删除完

        //1245 -> it指向2  2删除后得到145 然后直接++it  it指向了5 跳过了4；
        //所以不能直接++；
        //或者erase有的编译器会缩容，缩容后it也会失效，跟insert类似
        //SGI版本和PJ版本的vector都没有采用缩容的做法。避免了频繁申请空间。
    //1 2 3 4   -> 崩溃
        //最后一个是偶数，当删除完，_finish指向了it的位置，然后it++了，则it永远不可能等于v1.begin()
        //所以崩溃了，while (it != v1.end())，可以改成小于吗？ 小于只能用在 随机迭代器身上，物理空间连续
                                            //而list呢？，所以!=是通用的！
    //上述单中问题，本质都是erase(it)以后it的意义变了，再去++it是不对的。(it失效了)
    vector<int> v1;
    v1.push_back(1);
    v1.push_back(2);
    //v1.push_back(3);
    v1.push_back(4);
    //v1.push_back(5);
    //vector<int>::iterator it = find(v1.begin(), v1.end(), 2);
    //if (it != v1.end())
    //{
    //	//如果insert中发生了扩容，那么会导致it指向空间被释放
    //	//it本质就是一个野指针，这种问题，我们就叫做迭代器失效
    //	v1.erase(it);
    //}
    //vector<int>::iterator it = v1.begin();
    //while (it != v1.end())
    //{
    //	if (*it % 2 == 0)
    //	{
    //		v1.erase(it);
    //	}

    //	++it;
    //}
    //正确写法
    vector<int>::iterator it = v1.begin();
    while (it != v1.end())
    {
        if (*it % 2 == 0)
        {
            it = v1.erase(it);
            //erase 以后it失效 返回it的下一个位置  下一个位置已更新，已经向前挪动，所以返回的看起来还是当前位置
        }
        else
        {
            ++it;
        }
    }

    for (auto e : v1)
    {
        cout << e << " ";
    }
    cout << endl;
}
```

> <img src="https://picgo-1311604203.cos.ap-beijing.myqcloud.com/imageimage-20220701091234068.png" alt="image-20220701091234068" style="zoom:67%;" />
>
> <img src="https://picgo-1311604203.cos.ap-beijing.myqcloud.com/imageimage-20220701092132822.png" alt="image-20220701092132822" style="zoom:60%;" />

Q：`string`的`insert`/`erase`迭代器是否会失效？

A：**会** ， `string`什么事后会失效，参考`vector`，跟`vector`完全类似。`sting`的`insert` 一般用下下标`size_t`参数，所以很少会失效

**结论：**只要使用迭代器访问的容器都可能会涉及迭代器失效



### 3 增删查改

| vector增删查改                                               | 类型/参数                                                    | 接口说明                                               |
| ------------------------------------------------------------ | ------------------------------------------------------------ | ------------------------------------------------------ |
| [push_back](https://cplusplus.com/reference/vector/vector/push_back/)（重点） | void push_back (const value_type& val);                      | 尾插                                                   |
| [pop_back ](https://cplusplus.com/reference/vector/vector/pop_back/)（重点） | void pop_back();                                             | 尾删                                                   |
| [find ](https://cplusplus.com/reference/algorithm/find/?kw=find) | template <class InputIterator, class T>    <br />InputIterator find (InputIterator first, InputIterator last, const T& val); | 查找。（注意这个是算法模块实现，不是vector的成员接口） |
| [insert](https://cplusplus.com/reference/vector/vector/insert/) | iterator insert (iterator position, const value_type& val);  | 在position之前插入val                                  |
| [erase ](https://cplusplus.com/reference/vector/vector/erase/) | iterator erase (iterator position);<br />iterator erase (iterator first, iterator last); | 删除position位置的数据                                 |
| [swap ](https://cplusplus.com/reference/vector/vector/swap/) | void swap (vector& x);                                       | 交换两个vector的数据空间                               |
| [operator[]](https://cplusplus.com/reference/vector/vector/operator%5b%5d/) （重点） | reference operator[] (size_type n); <br />const_reference operator[] (size_type n) const; | 像数组一样访问                                         |

####   增删：扩容

| 接口名                                                       | 类型/参数                                                 | 接口说明                                           |
| ------------------------------------------------------------ | --------------------------------------------------------- | -------------------------------------------------- |
| [**reserve**](https://cplusplus.com/reference/vector/vector/reserve/) | void reserve (size_type n);                               | 增容，当增容n小于已有数据，不会有任何变化          |
| [**resize**](https://cplusplus.com/reference/vector/vector/resize/) | void resize (size_type n, value_type val = value_type()); | 增容+初始化，当n小于已有数据，会删除数据，容量不变 |

```c++
void test_vector3()
{
	vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	cout << v.max_size() << endl;//char42亿

	v.reserve(100);//只扩容 capacity = 100  size不变
	v.resize(100,5);//扩容后还 将有效数字加到100   capacity = 100 size = 100  
	v.resize(4);//还可以删除  但capacity不变，size = 4;
	//v[5];//断言越界
	//v.at(5);//抛异常
}
```

#### 删查改：

- erase 删除

- find 查找

- insert 插入修改

```c++
void test_vector4()
{
	vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	//v.assign(10, 5);//10个5 覆盖原来的数据，或者给区间

	//在区间中查找3 ，找到返回3，没找到返回end()//类型可以auto
	vector<int>::iterator ret = find(v.begin(), v.end(),3);
	if (ret != v.end())
	{
		cout << "找到了！"<<endl;
		v.insert(ret, 30);//在ret的前面位置插入30
		//v.erase(ret);//不能在这删除，因为ret被insert使用后会失效，会报错
	}
	//插入 insert
	v.insert(v.begin(), -1);//在头部插入-1
	//删除 erase
					//在begin - end 区间找到3 赋值给 pos迭代器
	vector<int>::iterator pos = find(v.begin(), v.end(), 3);
	if (pos != v.end())
	{
		v.erase(pos);//删除pos
	}
	//打印删除后的数据
	for (auto e : v)
	{
		cout << e << ' ';
	}

	//string 为什么有独立的find? 因为 sting还要查找子串，不仅仅查某个字符
}
```



### 4.套娃

- 二维数组 **vector<**`vector < type >` **>** vv

```c++
void test_vector5()
{
	vector<vector<int>> vv;
	//开空间+初始化，默认0
	vv.resize(5);
	for (size_t i = 0; i < 5; ++i)
	{
		//先开空间
		vv[i].resize(i + 1);
		//每行第一个和最后一个置1
		vv[i][0] = vv[i][vv[i].size() - 1] = 1;
	}
	//sort(vv.begin(), vv.end());
}
```

### 5.其他补充

#### const 

**修饰的匿名对象，生命周期会延长**

当没有构造函数，只有析构函数，对象出了这一行会直接析构，程序结束后 也可能再次调用析构函数。

当构造、析构函数同时存在，对象出了这一行则不会析构，直到出了当前函数作用域，才会析构。

#### swap

`sawp(v1,v3)` 3个深拷贝

`v1.swap(v3)` 仅交换成员变量指针 



## 1.3 习题



### [118.杨辉三角](https://leetcode.cn/problems/pascals-triangle/submissions/)

```
class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        //定义vv
        vector<vector<int>> vv;
        //开空间+初始化，默认0
        vv.resize(numRows);
        for(size_t i = 0;i<numRows;++i)
        {
            //先开空间
            vv[i].resize(i+1);
            //每行第一个和最后一个置1
            vv[i][0] = vv[i][vv[i].size()-1] = 1;
        }
        //访问第一层vector
        for(size_t i = 0;i<vv.size();++i)
        {
            //访问第一层vector里的vector
            for(size_t j = 0;j<vv[i].size();++j)
            {
                if(vv[i][j] == 0)
                {
                    //这个值等于，上列的对应数，和上一列对应数的前一个
                    vv[i][j] = vv[i-1][j] + vv[i-1][j-1];
                }
            }
        }
        //返回vv
        return vv;
    }
};
```

> <img src="https://picgo-1311604203.cos.ap-beijing.myqcloud.com/image/202206261102984.png" alt="image-20220626110221900" style="zoom: 50%;" />

### [17. 电话号码的字母组合](https://leetcode.cn/problems/letter-combinations-of-a-phone-number/)

```
class Solution {
    string arr[10] = {"","","abc","def","ghi","jkl","mno","pqrs","tuv","wxyz"};

public:
    void _letterCombinations(const string& digits,size_t i,string combinStr,vector<string>& strV)
    {                       //数字字符串      //标识数字字符串  //取到的字母组合 // 返回的 string类型的vector
        if(i == digits.size())
        {
            strV.push_back(combinStr);// i = 3 后，将 "akt" 存进strV里，
                                    //然后回到 k的那一层(j = 0),这层循环完成，j++，则取到"aku"
            return;
        }
        //例如 digits = "258"
        //取2对应的位置 ,绝对映射 arr的2的校标
        //i 标识 数字字符串
        string str = arr[digits[i] - '0'];//i = 0(0:2)取到"abc" //i+1 = 1 (1:5)后取到"kjl"// i:1+1 = 2 (2:8)后取到"tuv"
        //j标识数字对应的字符串  取到的字符串多长，就递归多少次
        for(size_t j = 0; j<str.size();++j)
        {
            _letterCombinations(digits,i+1,combinStr + str[j],strV);
                                        //取到的"a"因为j是0 // 下一层进来取到 "k" j是0 // 再下一层是 "t" j是0
        }
    }
    vector<string> letterCombinations(string digits) {
        string combinStr;
        vector<string> strV;

        if(digits.empty())
        {
            return strV;
        }
        _letterCombinations(digits,0,combinStr,strV);

        return strV;
    }
};
```

#### ！！！画一下递归展开图，总结后写题解！！！

？？？





## 2.0 💒vector 模拟实现

### 🧸练习

#### 💜写一个简单的vector

```c++
namespace uaena
{
	template<class T>
	class vector
	{
	public:
		typedef T* iterator;
		typedef const T* const_iterator;
		//构造函数
		vector()
			:_start(nullptr)
			, _finish(nullptr)
			, _endofstorage(nullptr)
		{}
        //析构函数
		~vector()
		{
			if (_start)
			{
				delete[] _start;
				_start = _finish = _endofstorage = nullptr;
			}
		}
private:
		iterator _start;//指向起始位置
		iterator _finish;//指向数据个数的下一个
		iterator _endofstorage;//指向空间的最后位置的下一个
	};
}
```

### 🧸vector类实现

#### 💜构造函数

##### 🌸s2(v1)

**深拷贝_传统写法**

```c++
v2(v1)
vector(const vector<T>& v)
{
    //给v2开辟和v1相同的空间
    _start = new T[v.capacity()];
    _finish = _start + v.size();
    _endofstorage = _start + v.capacity();

    memcpy(_start, v._start, v.size() * sizeof(T));
 //这里也要 更改浅拷贝  跟reserve一样。
    size_t sz = v.size();
    T* tmp = new T[n];
    if (_start)
    {
        //memcpy(tmp, _start, sizeof(T) * size());//浅拷贝，test6测试中会出错。
        for (size_t i = 0; i < sz; i++)
        {
            //T是int，一个一个拷贝没问题
            //T是string，一个一个调用的是T的深拷贝赋值，也没问题
            tmp[i] = _start[i];
        }
        delete[] _start;
    }
    _start = tmp;
    _finish = _start + sz;
    _endofstorage = _start + n;
}
```

**现代写法**

```c++
//一个类模板的成员函数，又可以是一个杉树模板
//构造
template <class InputIterator>//迭代器模板，自动推 迭代器类型
vector(InputIterator first, InputIterator last)
    :_start(nullptr)
    ,_finish(nullptr)
    ,_endofstorage(nullptr)
{
    while (_finish != last)
    {
        push_back(*_finish);
        ++first;
    }
}
void swap(vector<T>& v)
{
    std::swap(_start, v._start);
    std::swap(_finish, v._finish);
    std::swap(_endofstorage, v._endofstorage);
}
//深拷贝_现代写法
//v2(v1)
vector(const vector<T>& v)
{
    vector<T> tmp(v.begin(),v.end());
    //this->swap(tmp)
    swap(tmp);
}
```

##### 🌸v2 = v1

```c++
//v2 = v1
vector<T>& operator=(vector<T> v)
{
    swap(v);
    return *this;
}
```

#### 💜析构函数

##### 🌸~vector()

```c++
~vector()
{
    if (_start)
    {
        delete[] _start;
        _start = _finish = _endofstorage = nullptr;
    }
}
```

#### 💜迭代器

##### 🌸[begin()](https://cplusplus.com/reference/vector/vector/begin/)

返回指向[向量](https://cplusplus.com/vector)中第一个元素的迭代器。

迭代器返回的是 迭代器(iterator)类型

```c++
//迭代器
iterator begin()
{
    return _start;
}
const_iterator begin() const
{
    return _start;
}
```

##### 🌸[end()](https://cplusplus.com/reference/vector/vector/end/)

指向序列末尾之后的元素的迭代器

```c++
//迭代器
iterator end()
{
    return _finish;
}
const_iterator end() const
{
    return _finish;
}
```

#### 💜成员函数

##### 🌸[swap](https://cplusplus.com/reference/vector/vector/swap/)

迭代器、引用和指针的交换

```c++
void swap(vector<T>& v)
{
    std::swap(_start, v._start);
    std::swap(_finish, v._finish);
    std::swap(_endofstorage, v._endofstorage);
}
```



##### 🌸[size()](https://cplusplus.com/reference/vector/vector/size/)

返回元素个数

```c++
size_t size() const
{
    return _finish - _start;
}
```

##### 🌸[capacity()](https://cplusplus.com/reference/vector/vector/capacity/)

返回当前为[vector](https://cplusplus.com/vector)分配的存储空间的大小

```c++
size_t capacity() const
{
    return _endofstorage - _start;
}
```

##### 🌸[reserve()](https://cplusplus.com/reference/vector/vector/reserve/)

扩容，当n小于原来的容量，没有任何效果

```c++
void reserve(size_t n)
{
    if (n > capacity())
    {
        size_t sz = size();
        T* tmp = new T[n];
        if (_start)
        {
            //memcpy(tmp, _start, sizeof(T) * size());//浅拷贝，test6测试中会出错。
            for (size_t i = 0; i < sz; i++)
            {
                //T是int，一个一个拷贝没问题
                //T是string，一个一个调用的是T的深拷贝赋值，也没问题
                tmp[i] = _start[i];
            }
            delete[] _start;
        }
        _start = tmp;
        _finish = _start + sz;
        _endofstorage = _start + n;
    }
}
```

##### 🌸[resize()](https://cplusplus.com/reference/vector/vector/resize/)

扩容+初始化+删除数据

当n大于已有空间，则扩容，如果设置初始化值，则原来的数据保留，扩容的数据初始化为val，未给val则默认赋值0；

当n小于原来空间，会删除多余数据，空间不变。

```c++
resize(100,5);//初始化100个5
void resize(size_t n, const T& val =T())
{
    //删除数据直接挪动_finish
    if (n<size())
    {
        _finish = _start + n;
    }
    else
    {
        //其他两种情况 是空间够，直接填数据，空间不够扩容，再填数据
        if (n > capacity)
        {
            //扩容
            reserve(n);
        }
        while (_finish != _start + n)
        {
            //填数据
            *_finish = val;
            ++_finish;
        }
    }
}
```

##### 🌸[insert()](https://cplusplus.com/reference/vector/vector/insert/)

在pos前插入，可指定迭代器范围，但是可能会导致迭代器失效。

```c++
//在pos位置插入数据
void insert(iterator pos, const T& x)
{
    assert(pos >= _start);
    assert(pos <= _finish);//可以等于_finish ,pos是这个位置就可以尾插
    //满了就扩容
    if (_finish == _endofstorage)//如果已存数据 == 已有空间
    {
        //扩容会导致pos失效，扩容后更新pos
        size_t len = pos - _start;//记录位置
        //扩容
        reserve(capacity() == 0 ? 4 : capacity() * 2);
        pos = _start + len;//更新
    }
    //插入数据 从后往前挪动

    iterator end = _finish - 1;
    while (end >= pos)
    {
        *(end + 1) = *(end);
        --end;
    }
    *pos = x;
    ++_finish;
}
```

##### [🌸erase()]()

删除pos指向的数据，其他数据向前挪动！

```
//删除pos位置的数据 
iterator erase(iterator pos)
{
    assert(pos >= _start);
    assert(pos < _finish);

    iterator begin = pos + 1;
    while (begin < _finish)
    {
        *(begin - 1) = *(begin);
        ++begin;
    }
    --_finish;
    return pos;
}
```

##### 🌸[push_back()](https://cplusplus.com/reference/vector/vector/push_back/)

尾插

```c++
//尾插
void push_back(const T& x)
{
    if (_finish == _endofstorage)//如果已存数据 == 已有空间
    {
        //扩容
        //size_t newCapacity = capacity() == 0 ? 4 : capacity() * 2;//算出要开辟空间的大小
        //size_t sz = size();//先记录原有数据个数
        //T* tmp = new T[newCapacity];
        ////旧数据拷贝到新空间
        //if (_start) //如果_start 不为空则转移数据
        //{
        //	memcpy(tmp, _start, sizeof(T) * size()); 
        //	//void * memcpy ( void * 目的地, const void * 源, size_t num );
        //	//将 源 的num个拷贝到目的地
        //	delete[] _start; //释放原来的空间
        //}
        //_start = tmp; //扩容，_start 等于 新开辟的空间
        //_finish = _start + sz;//起始位置+加原来的数据个数 = 已有数据
        //_endofstorage = _start + newCapacity;//空间大小等于 起始位置+新开辟空间的大小
        reserve(capacity() == 0 ? 4 : capacity() * 2);
    }
    *_finish = x;
    ++_finish;
}
```

##### 🌸[pop_back()](https://cplusplus.com/reference/vector/vector/pop_back/)

尾删

```c++
void pop_back()
{
    //检查是否有数据
    assert(_finish > _start);
    --_finish;
}
```

#### 💜赋值函数

##### 🌸[operator[]](https://cplusplus.com/reference/vector/vector/operator[]/)

返回对[向量](https://cplusplus.com/vector)容器 中位置*n处元素的引用*

```c++
      reference operator[] (size_type n);
const_reference operator[] (size_type n) const;
```

```
T& operator[](size_t i)
{
    assert(i < size());
    return _start[i];
}
const T& operator[](size_t i)const
{
    assert(i < size());
    return _start[i];
}
```

##### 🌸[operator=](https://cplusplus.com/reference/vector/vector/operator=/)

将新内容分配给容器，替换其当前内容，并相应地修改其[大小](https://cplusplus.com/vector::size)。

```c++
 vector& operator= (const vector& x);
```

```c++
vector<T>& operator=(vector<T> v)
{
    swap(v);
    return *this;
}
```

