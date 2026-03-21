# lesson1——初识C语言

## 初识C语言

### 语言发展历史

机器语言(2进制) > 汇编语言(助记符) > B语言 > C语言 > ANSI C(C国际标准，C89，C90)

### 编译软件

VS -> MSVC

Linux -> gcc

### 第一个C程序

test.c -> 源文件

test.h -> 头文件

```c
#include <stdio.h>
//std io - 标准输入输出
int main()
{
	//库函数 - 输出函数 依赖<stdio.h>
	printf("hello world!\n");
	return 0;
}
```

> ![image-20220703093530012](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/imageimage-20220703093530012.png)

### 主函数

[C语言main()函数详解](http://c.biancheng.net/cpp/html/725.html)

**main（主要的，最大的）**

`mian`函数是主函数的入口，程序在`main`函数的第一行执行，

在`C`中函数不能重载，也就是不能有相同的函数名。

**main函数的形式**

在最新的 C99 标准中，只有以下两种定义方式是正确的：

```c
int main( void )  /* 无参数形式 */
{
    ...
    return 0;
}
int main( int argc, char *argv[] ) /* 带参数形式 */
{
    ...
    return 0;
}
```

不正确写法

```c
main()
这种形式开始。C90标准允许这种形式，但是C99标准不允许。

void main()
有些编译器允许这种形式，但是还没有任何标准考虑接受它。C++ 之父 Bjarne Stroustrup 在他的主页上的 FAQ 中明确地表示：void main( ) 的定义从来就不存在于 C++ 或者 C 。所以，编译器不必接受这种形式，并且很多编译器也不允许这么写。
```

### 返回函数

**return（回来，回去；归还，退还）**

`return 0` 代表程序正常退出

`return 1` 代表程序异常退出！

例如：现在我们有两个程序 `a.c` 和 `b.c`，当 `a.c` 正常结束后执行 `b.c` ，`main`如果 `a.c` 返回的是 `0` 代表正常结束，返回其他值为异常，此时如果`a.c`异常，则`b.c`不能被执行，上面的链接文档有详细说明。

### 数据类型

| 类型         | 名字         | 32位/64位<br />(byte/字节) | 范围值                          | 格式符 | 备注                          |
| ------------ | ------------ | -------------------------- | ------------------------------- | ------ | ----------------------------- |
| char         | 字符类型     | 1                          | -128 到 127 或 0 到 255         | %c     |                               |
| short        | 短整形       | 2                          | -32,768 到 32,767               | %hd    | short<int 就可以 取决编译器   |
| int          | 整型         | 4                          | -2,147,483,648 到 2,147,483,647 | %d     |                               |
| unsigned int | 无符号整形   | 4                          | 0 到 4,294,967,295              | %u     |                               |
| long         | 长整型       | 4/8                        | -2,147,483,648 到 2,147,483,647 | %ld    | long >= int就可以，取决编译器 |
| long long    | 长长整形     | 8                          |                                 | %lld   |                               |
| float        | 单精度浮点数 | 4                          | 1.2E-38 到 3.4E+38              | %f     | 6 位有效位                    |
| double       | 双精度浮点数 | 8                          | 2.3E-308 到 1.7E+308            | %lf    | 15 位有效位                   |

**字符** 用%`c`打印就是字符，用%`d`打印就时`ASCII`码对应的数字！

### ASCII表

ascii码

> ![ASCII表](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/imageASCII%E8%A1%A8.jpg)

### 变量

#### 定义

**类型**后面的叫**变量**

例如：a、b都叫变量

```c
int a;
char b;
```

#### 变量的类型

**变量**：可以修改值得叫变量

**常量**：不可以修改的值的叫常量

#### 定义变量的方法

```c
int age = 150;
float weight = 45.5f;
char ch = 'w';
```

#### 变量的分类

全局变量：不包含在任何函数内的变量

局部变量：在任意函数内定义的变量

**变量在查找的时候先在当前作用域找，找不到再去全局找！**

```c
int global = 2022; //全局变量
int main()
{
	int local = 2023; //局部变量
	return 0;
}
```

#### 变量的使用

`scanf`的使用

```C
#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
//std io - 标准输入输出
int main()
{
	int num1;
	int num2;
	scanf("%d%d", &num1, &num2);
	printf("%d %d", num1, num2);
	return 0;
}
```

**在`scanf`中`%d`和`%d`中间用什么隔开，输入时就要用什么。**

> ![image-20220703111321588](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/imageimage-20220703111321588.png)

#### VS下解决`scanf`的报错

**错误提示**

> ![image-20220703111552835](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/imageimage-20220703111552835.png)

**设置自动添加**

**路径：**`D:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\IDE\VC\VCProjectItems`

**添加：**在`newc++file.cpp`内添加`#define _CRT_SECURE_NO_WARNINGS 1`

**无权限修改**：将文件放在桌面上修改，再拷贝回去！

#### 变量的作用域

