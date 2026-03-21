# GZIP压缩文件实现

## 做此项目需要掌握的知识

C：文件操作相关，例如：文件指针、打开文件、写入文件等

C++：模板、类、vector、string、C++11仿函数

数据结构：Huffman树、priority_queue(优先级队列)、堆

## 项目进行环境

vs2019 + Windows10

## 为什么要进行文件压缩？

目的是让文件变小，在传输和存储时都可以减少占用。

# 原理

此项目是基于LZ77和Huffman编码的文件压缩，LZ77算法(下面详细讲)是将重复的字段替换成<长度、距离>对，从而达到减少字符所占的空间，LZ77算法的最大问题时编码和字符不好区分，而且小于等于2字节的字符不值得用<长度、距离>对替换，此时利用Huffman树得到的编码，可以解决LZ77的缺陷，项目中的实现方式是：统计所有字符的出现次数，将出现次数越多的放在树靠上的位置，编码也就越短，反之放在树靠下的位置，编码越长。这样的编码在压缩时大多数情况会比等长编码更优，占用空间会更少。

压缩的时候首要根据每个字符出现的次数构造N个节点的二叉树森林，根据Huffman树的特点(下面详细讲)将森林构建成Huffman树，此时也就能得到Huffman编码，我们要存储这个编码，方便解压，同时还要保存源文件的格式、编码所占用的行数、编码后的数据。

## LZ77原型(**<长度、距离>**对)

**将重复出现的内容 替换成更短的<长度，距离>对**

>  **对重复出现的文字压缩**
>
>  mno==abc==zxyuvw==abc==123456==abc==zxydefgh
>
>  用**<长度、距离>**对的方式来替换
>
>  **长度**：重复文件所占的字节
>
>  **距离**：后文中重复出现词语首字节 与 前文中的重复词语的 **字节差**
>
>  **压缩**：monabczxyuvw==(3,9)==123456==(6,18)==defgh  （真实存储时没有括号和逗号，这里是方便观看）
>
>  **解压**：用长度距离 去替换回来 

**缺点**：

1. 无法区分字符是替换后的编码还是原有的字符

2. 字符<= 2字节 时 不值得去替换，因为替换完还是占用2字节

## 编码替换

根据LZ77的缺陷，我们想到了编码替换

### 等长编码

一个字节是8比特位

给每个字节找一个小于8比特位的编码，来替换文件中的字节。

**文件**：DDAB DDBC DBCD CDCC	（16字节）

**编码**：A：00	B：01	C：10	D：11

**压缩**：11110001 11110110 11011011 10111010	（4字节）

**解压**：DDAB DDBC DBCD CDCC		(查表解压)

==优化==：让出现次数少的编码长一点，让出现次数多的编码少一些

### 动态不等长编码

**文件**：DDAB DDBC DBCD CDCC DDD	(19字节)

**编码**：A：100	B：101	C：11	D：0

**解压**：00100101 00101110 10111011 01111000	（4字节）

**==编码==**：此时编码从何而来？ —— **Huffman树**

## Huffman树

### 特点

带权路径长度：二叉树的根节点到二叉树所有叶子节点的路径长度与相应权值乘积之和，

而huffman树的带权路径是最小的。

**发现**：权值大的靠近根，带权路径就越小。

### 如何创建Huffman树

先创建N个数的森林   例如：10 5 3 1 

先在森林中获取两个权值最小的两个树  3、1   **新节点的权值是这两个权值之和**

将新的二叉树放回二叉树森林中  10  5   4

4 、5    = 9

9 、10 = 19

此时森林创建完成

![image-20220903104549289](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/imageimage-20220903104549289.png)

### Huffman编码如何获得

编码：从根节点到叶子经过的边。

假设：左边为0，右边为1，那么遍历边到叶子，也就得到了这个字符的编码

权值：字符对应节点内的数字是该节点的权值，也是该字符在文件中出现的次数

![image-20220907075824657](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/imageimage-20220907075824657.png)



# 代码实现

**文件**

`Common.h` ：放头文件的 头文件

`FileComperssHuffman.h`：定义Huffman压缩文件的 头文件

`HuffmanTree.hpp`：定义和实现Huffman树

`FileComperssHuffman.cpp`：实现Huffman压缩

`UaenaZioTest.cpp`：main函数执行文件

## 1.实现Huffman树

### a.定义树的每一个节点

> 首先要定义树的每个节点，节点中要记录（左孩子、右孩子、双亲、权值(出现的次数)）

HuffmanTree.hpp

```c++
#pragma once
#include <iostream>
#include <vector>
#include <queue>

template<class W>
struct HuffmanTreeNode
{
	HuffmanTreeNode<W>* _left;
	HuffmanTreeNode<W>* _right;
	HuffmanTreeNode<W>* _parent;
	W _weight;
	HuffmanTreeNode(const W& weight = W())
		:_left(nullptr)
		,_right(nullptr)
		,_parent(nullptr)
		,_weight(weight)
	{}
};
```

构造函数 `weight` 给匿名对象`W()`，是为了在创建节点的时候可以使用无参构造，无参构造会调用初始化列表，来初始化无参构造的对象。

**举例：**

```c++
template<class W>
struct HuffmanTreeNode
{
	HuffmanTreeNode<W>* _left;
	HuffmanTreeNode<W>* _right;
	HuffmanTreeNode<W>* _parent;
	W _weight;
	①：HuffmanTreeNode(const W& weight)
	②：HuffmanTreeNode(const W& weight = W())
		:_left(nullptr)
		, _right(nullptr)
		, _parent(nullptr)
		, _weight(weight)
	{}
};

int main()
{
	HuffmanTreeNode<int>* p = new HuffmanTreeNode<int>(); 
	//①：如果上面weight没有默认参数W()，则会报错，必须传入值才能构造。
	//②：给了默认的匿名对象，则会调用初始化列表，初始化p指向的节点。
	return 0;
}

```

`template<class W>`是类模板，W是模板参数，这样定义，在构造时，可以随意指定类型，而不用创建多个类型的 struct(结构体)。

### b.定义树

HuffmanTree.hpp

```c++
template<class W>
class HuffmanTree
{
	typedef HuffmanTreeNode<W> Node;
    //仿函数——用来比较两个节点的权值，作为优先级队列的比较方法
    //仿函数是C++11中出现的新规，大概意思是重载operator() 来实现这个类能像函数一样调用 。
    class Compare
	{
	public:
		bool operator()(const Node* x, const Node* y)
		{
            //大于号需要重载 下面会讲
			return x->_weight > y->_weight;
		}

	};
public:
	HuffmanTree()
		: _root(nullptr)
	{}
	//vw是每个字符的权值,invalid是无效值，为了比较vw出现次数为0 的无效字符
	HuffmanTree(const std::vector<W>& vw,const W& invalid)
	{
		//1.用所有的权值构造只有根节点的二叉树森林
		//森林中二叉树应该使用堆(优先级队列)来保存
		//小堆——优先级队列默认是大堆
		//q是优先级队列，存储的是每一个字符组成的(struct)节点
        //三个参数<函数指针、存储方式、比较方式>
        //vector存储的是节点的地址，而比较的方法是Compare 是要用权值weight比较
		std::priority_queue < Node*, std::vector<Node*>, Compare > q;
		//遍历是为了拿到 每个权值，来构造Huffman数的每个节点，插入优先级队列，组成N个节点的二叉树森林
        
		for (auto& e : vw)
		{
            //如果e和无效的权值比较，不想的的话 说明有效
            //此时！=号需要重载
			if (invalid != e)
			{
				q.push(new Node(e));
			}
		}
        
        //如果q里只剩下一个节点，那么说明树构建完成，因为q里是个森林
        while (q.size() > 1)
		{
            //优先级队列通过刚才的比较，堆顶是最小的。
            //取两个最小的节点 ，取完弹出，再取下一个
			Node* left = q.top();
			q.pop();

			Node* right = q.top();
			q.pop();

			//新节点的权值是，刚才两个树的权值之和
            //此时left和right的_weight是自定义类型，想要相加需要重载
            //在谁里重载呢？
            // left是node类型  node是 HuffmanTreeNode类型
            //HuffmanTreeNode<W>* _left  W是ByteInfo类型
            //所以在ByteInfo中重载
			Node* parent = new Node(left->_weight + right->_weight);
            //新节点的左右子树是 刚才的两个节点
			parent->_left = left;
			left->_parent = parent;

			parent->_right = right;
			right->_parent = parent;

			//最后将parent放入到二叉树森林中
			q.push(parent);
		}
        //当队列中只剩下最后一个节点，那么这个节点就是Huffman树的根节点
        _root = q.top();
	}
    //析构Huffman树
    ~HuffmanTree()
	{
		Destroy(_root);
	}
	//获取Huffman树的根节点
	Node* GetRoot()
	{
		return _root;
	}
private:
	void Destroy(Node*& root)
	{
        //析构 root
		if (root)
		{
            //递归析构左右子树
			Destroy(root->_left);
			Destroy(root->_right);
            //然后delete根节点root，并且置空
			delete root;
			root = nullptr;
		}
	}
private:
	Node* _root;//二叉树的根节点
};
```

此时Huffman树构造完成

测试Huffman树是否正确

```c++
void TestHuffmanTree()
{
	std::vector<int> v{ 7,5,3,1 };
	HuffmanTree<int> ht(v);
}
```

## 2.Huffman编码压缩过程

> 1.统计源文件中每个字节出现的次数
>
> 2.字节频次 来创建Huffman树
>
> 3.获取每个字节的Huffman编码
>
> 4.用得到的编码，对源文件的每一个字节来改写。



### a. 定义节点声明

节点包括 字符、字符频次信息、字符编码

FileComperssHuffman.h

```c++
#pragma once

#include "HuffmanTree.hpp"
#include "Common.h"
#include <string>
#include <iostream>
using std::string;
//记录字符频次信息，通过字符频次构造 树，频次也就是每个树节点的权值
struct ByteInfo
{
	uch _ch;//字节
	size_t _appearCount;//字节的次数
	std::string _chCode;//字符的编码
	ByteInfo(size_t appearCount = 0)
		:_appearCount(appearCount)
	{}
    
    //重载+号 
    //因为Node* parent = new Node(left->_weight + right->_weight);
    ByteInfo operator+(const ByteInfo& other)const
	{
		return ByteInfo(_appearCount + other._appearCount);
	}
    
    //重载>号
    //因为return x->_weight > y->_weight;
    bool operator>(const ByteInfo& other)const
	{
        //只需要比较权值就可以了
		return _appearCount > other._appearCount;
	}
    
    //重载！=号
    //因为 if (invalid != e)
    
	bool operator!=(const ByteInfo& other)const
	{
		return _appearCount != other._appearCount;
	}
	bool operator==(const ByteInfo& other)const
	{
		return _appearCount == other._appearCount;
	}
    
}
```

### b. 定义压缩类声明

FileComperssHuffman.h

```c++
//声明 ，定义在cpp中
class FileComperssHM
{
public:
    //构造函数
    FileComperssHM();
	//压缩(文件路径)
	void CompressFile(const string& filePath);
	//解压缩(文件路径)
	void UNCompressFile(const string& filePath);
    
    //ByteInfo类型的数组 存储字节信息
    std::vector<ByteInfo> _fileInfo;
};
```

### c.构造函数实现

FileComperssHuffman.cpp

```c++
#include "FileComperssHuffman.h"

FileComperssHM::FileComperssHM()
{
    //因为ByteInfo字节频次信息中的ch有
    //_fileInfo是FCHM中定义的 ByteInfo类型的数组
    //resize 扩容+初始化 扩容比已有数据少则会删除，不会改变空间大小
    //reserve 扩容 只开空间
    _fileInfo.resize(256);
	for (int i = 0; i < 256; ++i)
	{
        //256个字符对应的ch赋值成对应的ASCII码 
        //根据ASCII码找到对应的字符，然后增加_appearCount（字符出现的次数）
		_fileInfo[i]._ch = i;
	}
}
```

### d.压缩实现

#### 1.统计字符出现次数

用数组记录一个char的大小，比并且将下标赋值成对应的ASCII码

再用读取到的字节 将 FileInfo[256] 中对应的字符(ASCII)的次数增加

因为fileinfo的类型是ByteInfo ，ByteInfo中存储的有字符、字符出现的次数、字符的编码



FileComperssHuffman.cpp

```c++

void FileComperssHM::CompressFile(const string& filePath)
{
	//1.统计源文件中每个字符出现的次数
    //fopen（文件路径，读取方式） 
    //c_str()将字符串以C的形式返回一个指向数组的指针，数组包含\0
    //r是只读，文件必须存在， b是二进制读取
	FILE* fIn = fopen(filePath.c_str(), "rb");
	if (nullptr == fIn)
	{
		cout << "待压缩文件不存在" << endl;
		return;
	}

	//一次读取1024字节
	uch rdBuff[1024];
	while (true)
	{
        //实际读取的大小size = 存储位置ptr，每个元素的大小size，一次读取1024大小count，从输入流的FILE中读取
		size_t rdSize = fread(rdBuff, 1, 1024, fIn);
        //循环读取，如果rdSize读取的是0，那说明文件读完了。
		if (0 == rdSize)
			break;
		//统计次数
		for (size_t i = 0; i < rdSize; ++i)
		{
            //rdBuff读取的第i个字符 的ASCII码 作为下标
            //将刚才256个字符的数组对相应的 字符 的 字符出现次数进行++
			_fileInfo[rdBuff[i]]._appearCount++;
		}
	}
```

#### 2.用统计的结构创建Huffman树

FileComperssHuffman.cpp

```c++
	//2.用统计的结果创建Huffman树
	//树的类型是 ByteInfo 类型节点 参数是（_fileInfo(ByteInfo类型数组) ，匿名对象，用作无效的对比）
	HuffmanTree<ByteInfo> ht(_fileInfo, ByteInfo());
```

