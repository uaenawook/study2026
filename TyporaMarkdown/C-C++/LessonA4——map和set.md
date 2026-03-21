# lessonA4——map和set

## set

### 作用

排序+去重     不允许重复

### erase()

```c
	set<int>::iterator pos = s.find(30);
	if (pos != s.end())
	{
		//pos必须是一个有效位置的迭代器
		s.erase(pos);
	}

	cout << s.erase(30) << endl;//删除失败返回0
	cout << s.erase(3) << endl;//删除成功返回 1
```



## multiset

如许多种的set

### 作用

排序（允许重复）

### find（）

```c
// find的val有多个值时，返回中序第一个val值所在节点的迭代器
multiset<int>::iterator pos = s.find(8);
while(pos != s.end())
{
    cout << *pos << " ";
    ++pos;
}
```

### erase()

#### 1.迭代器查找删除

```c
pos = s.find(1);
while (pos != s.end() && *pos == 1)
{
    auto next = pos;
    ++next;
    //删除pos位置 就成了野指针，所以先用next记录下一个位置
    s.erase(pos);
    pos = next;
}
```

#### 2.直接删除数值

```c
cout << s.erase(1) << endl;//返回了4
```



## map

排序 搜索树,可以存放一对值     不允许存储重复数据

### 使用方法

```c

void test_map1()
{
	map<string, string> dict;
	pair<string, string> kv1("sort", "排序");
	dict.insert(kv1);
	dict.insert(pair<string, string>("string", "字符串"));
	
}
```

### pair

构造存放一对数据   需要自己写类型

```c
dict.insert(pair<string, string>("string", "字符串"));
```

#### 访问map

##### 方式一：迭代器

first是第一个参数，second是第二个参数

```c
	auto it = dict.begin();
	while (it != dict.end())
	{
		//cout << *it << " "; //*it 是pair   pair有两个值
		//cout << (*it).first << ":" << (*it).second << endl; //先解引用再取first
        cout << it->first << ":" << it->second << endl; //先解引用再取first

		++it;
	}
	cout << endl;

sort:排序
string:字符串
test:测试

```

##### 方式二：范围for

也是按照排序访问的

```c
for (auto& kv : dict)
{
    cout << kv.first << ":" << kv.second << endl; //先解引用再取first
}

sort:排序
string:字符串
test:测试

s s t 首字母是ASCII码的顺序
```



#### make_pair(更常用)

自动推导类型

```c
dict.insert(make_pair("test","测试"));//自动推导类型
```

### insert()

利用插入查找 一段string中水果出现的次数



插入 如果插入成功则直接插入  插入失败则加加map的第二个值

```c
string arr[] = { "苹果","苹果","香蕉","苹果", "香蕉","苹果", "桃子" };
map<string, int> countMap;
for (auto& str : arr)
{
    auto ret = countMap.find(str);
    if (ret == countMap.end())
    {
        countMap.insert(make_pair(str, 1));

    }
    else
    {
        ret->second++;//第二个数 是整数 可以++
    }
}

苹果:4
桃子:1
香蕉:2

```

#### 优化

因为 map的insert 返回值是pair{iterator，bool}，所以当插入时 第二个值为false   则加加map的第二个值(int)

```c
for (auto& str : arr)
{
    auto kv = countMap.insert(make_pair(str, 1));
    if (kv.second == false)
    {
        kv.first->second++;
    }
}
苹果:4
桃子:1
香蕉:2

```

### operator[]

#### 解释

operato[]返回的是map的val的引用， map<k,val>

```c
operator的返回值是： return(*((this->insert(make_pair(k,mapped_type()))).first)).second;)
表达式是
mapeed_type& operator[](const key_type& k)
{
    return (*((this->insert(make_pair(k,mapped_type()))).first)).second;
}
```

```c
insert(make_pair(k,mapped_type())  这一层是插入值  mapped_type()是T的别名
```

![image-20230105191155978](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/imageimage-20230105191155978.png)

```c
(this->insert(make_pair(k,T)))  这一层是this这个位置插入 返回值是pair<iterator,boll>
因为insert的返回值是pair
```

```c
(this->insert(make_pair(k,mapped_type()))).first)
相当于↓↓↓
(pair<iterator,boll>).first)   的first是 iterator
iterator是插入位置的迭代器，也就是这个位置，如果成功则是新插入的位置，不成功是查找到的位置
```

```c
*((this->insert(make_pair(k,mapped_type()))).first))
相当于↓↓↓
*(iterator) 迭代器解引用就是这个位置的pair   pair存储的是map的两个数据
相当于↓↓↓
pair<key_type,map_type>
```

```
(*((this->insert(make_pair(k,mapped_type()))).first)).second
相当于↓↓↓
(*iterator).second
相当于↓↓↓
pair<key_type,map_type> . second
相当于↓↓↓
map_type
```

**因为此函数的返回值是 `mapped_type&` 所以返回的是 val 也就是第二个参数的引用**

![image-20230105194400896](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/imageimage-20230105194400896.png)

#### 实践

返回值是val的引用

```
void test_map3()
{
	map<string, string> dict;
	dict.insert(make_pair("sort", "排序"));//插入
	dict.insert(make_pair("left", "左边"));//插入
	dict.insert(make_pair("left", "剩余"));//插不进去，不会修改

	dict["left"] = "剩余";//修改    因为方括号返回的是map数据val的引用
	dict["test"];//插入
	cout << dict["sort"] << endl;//查找

	dict["string"] = "字符串";//插入+修改
}
int main()
{
	test_map3();
	return 0;
```

![image-20230105185115344](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/imageimage-20230105185115344.png)

## multimap

跟map用法相同   允许存储重复数据

不支持operator[]

### count()

查找支持count()

![image-20230105221025077](C:\Users\uaena\AppData\Roaming\Typora\typora-user-images\image-20230105221025077.png)

