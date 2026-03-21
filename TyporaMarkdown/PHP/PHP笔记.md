# PHP笔记

## PHP规范

### 格式

`<?php     ?>`

### 注释

多行注释：`/*   */`

单行注释：`//`

## 常量和变量

### 变量

#### 格式

代码结束符：`;`

定义变量：`$anme;`

存储int：`$name = 123;`

存储字符串：`$name = 'holle world';`

#### 全局变量

必须用globa声明才可以变成全局的

但是globa之能是把外面的局部变量，在内部声明成全局

内部才能使用

#### 静态变量

**php中静态变量并不能再全局使用**

**C中静态变量可以在全局使用**

static关键字定义静态变量

静态变量出作用域不会销毁，也不能被改变

```
static $a = 123;
```

错误示范

```php
function test3()
{
    static $jing = 123;
    echo $jing;//true
}
test3();

echo $jing;//error
```

静态变量不能再函数内使用

```php
static $jing = 123;
function test3()
{
    echo $jing;//error
}
test3();
```

静态变量不能用globa声明成全局的

```php
static $jing = 123;
function test3()
{
    globa $jing;//error
    echo $jing;
}
test3();
```

C中可以

```c

	static a = 10;
	
	for (int i = 0; i <= 5; i++)
	{
		printf("%d\n", a);
	}
```



#### 引用&

`$b = &$a;` `$b`就是`$a`的别名

##### 引用传参

与C++的引用传参一样

```php
function test4(&$a)
{
    $a++;
}
$b = 1;
test4($b);
echo $b;//2
```



### 常量

#### 定义关键字

单双引号都行，变量名一般大写，不能重复，后面是内容

```
define('常量名称','内容');
define('常量名称','内容');

define('MY_NAME1','name1');
echo '<br/>';
define("MY_NAME2","name2");
echo MY_NAME1,"<br/>",MY_NAME2;
输出：
	name1
	name2
```

#### 预定义常量

**预定义常量使用的时候不区分大小写**

php规范定义了一些常量

例如：

```
__FUNCTION__
```

##### 魔术常量

**有九个魔术常量它们的值随着它们在代码中的位置改变而改变**

https://www.php.net/manual/zh/language.constants.magic.php

| 名字                   | 说明                                                         |
| :--------------------- | :----------------------------------------------------------- |
| **`__LINE__`**         | 文件中的当前行号。                                           |
| **`__FILE__`**         | 文件的完整路径和文件名。如果用在被包含文件中，则返回被包含的文件名。 |
| **`__DIR__`**          | 文件所在的目录。如果用在被包括文件中，则返回被包括的文件所在的目录。它等价于 `dirname(__FILE__)`。除非是根目录，否则目录中名不包括末尾的斜杠。 |
| **`__FUNCTION__`**     | 当前函数的名称。匿名函数则为 `{closure}`。                   |
| **`__CLASS__`**        | 当前类的名称。类名包括其被声明的作用域（例如 `Foo\Bar`）。当用在 trait 方法中时，__CLASS__ 是调用 trait 方法的类的名字。 |
| **`__TRAIT__`**        | Trait 的名字。Trait 名包括其被声明的作用域（例如 `Foo\Bar`）。 |
| **`__METHOD__`**       | 类的方法名。                                                 |
| **`__NAMESPACE__`**    | 当前命名空间的名称。                                         |
| **`ClassName::class`** | 完整的类名。                                                 |

##### 使用一下

```php
echo __file__;echo '<br/>';
echo __FILE__;echo '<br/>';
echo __line__;echo '<br/>';
echo __LINE__;echo '<br/>';

输出：
D:\phpStudy\WWW\myphp\index.php
D:\phpStudy\WWW\myphp\index.php
133
134
```



### 区别

1. 常量前面没有$
2. 常量只能用define()函数定义
3. 作用域在全局
4. 定义后不能变
5. 常量的值之能是 bool，int，float，string类型

## 运算符

### 算数运算符

`+` `-` `*` `/` `%` `++` `--`

| 列句      | 名称   | 结果               |
| --------- | ------ | ------------------ |
| `-$a`     | 取反   | $a的负值           |
| `$a + $b` | 加     | 和                 |
| `$a - $b` | 减     | 差/商              |
| `$a * $b` | 乘     | 乘积               |
| `$a / $b` | 除     | 获取商，会保留小数 |
| `$a % $b` | 取模   | 获取余数           |
| `++$a`    | 前置++ | 先加加，后使用     |
| `$a++`    | 后置++ | 先使用，后加加     |
| `--$a`    | 前置-- | 先减减，后使用     |
| `$a--`    | 后置-- | 先使用，后减减     |

#### 后置++ 演示

```php
$sum = 10;
echo ++$sum;//11
echo $sum;//11

echo '<br/>';

$sum2 = 10;
echo $sum2++;//10
echo $sum;//11
```

### 字符串运算符

`.`连接运算符

```php
$str1 = "你好";
$str2 = "世界";
echo $str1.$str2;
echo '<br/>';
echo $str1."PHP";
输出：
你好世界
你好PHP
```

### 负值运算符

`=` `+=` `-=` `*=` `/=` `%=` `.=`

说一下`.=`主要用于链接字符串

```php
$str1 = "你好";
$str2 = "世界";
$str1 .= $str2;//你好世界
$str1 += $str2;//0

$str1 = 2;
$str2 = 3;
$str1 .= $str2;//23

$str1 = 2;
$str2 = 3;
$str1 += $str2;//5
```

结论：
    .=用于字符串相加
    .=加**整数**时 会将整数看成 **字符串**

### 比较运算符

等于：`==`

全等： `===`

不等于： `!=` `<>`    (两个符号都是!=的意思)

不全等：`!==` （判断类型和内容，`$a = 11`，`$b = '11'`，也就是a不全等于b，成立

小于：`<`

小于等于：`<=`

大于：`>`

大于等于：`>=`

```php
`===`
值相等，类型也要相等
$num1 = 11;
$num2 = '11';
var_dump((int)$num2);//int(11)
var_dump($num1 == $num2);//bool(true) 自动转换类型，把$num2的字符串转换成了整数
var_dump($num1 === $num2);//bool(false)
```

### 逻辑运算符

与：and 、&&

或：or 、||

非：!

异或：xor (规则 左右不一样就是true)

逻辑运算符有截断（短路）的情况！

例如 a || b   a成立 b则不执行

例如a && b  a不成立 b也不执行

| 例子       | 名称            | 结果                                                      |
| :--------- | :-------------- | :-------------------------------------------------------- |
| $a and $b  | And（逻辑与）   | **`true`**，如果 $a 和 $b 都为 **`true`**。               |
| $a or $b   | Or（逻辑或）    | **`true`**，如果 $a 或 $b 任一为 **`true`**。             |
| $a xor $b  | Xor（逻辑异或） | **`true`**，如果 $a 或 $b 任一为 **`true`**，但不同时是。 |
| ! $a       | Not（逻辑非）   | **`true`**，如果 $a 不为 **`true`**。                     |
| `$a && $b` | And（逻辑与）   | **`true`**，如果 $a 和 $b 都为 **`true`**。               |
| $a || $b   | Or（逻辑或）    | **`true`**，如果 $a 或 $b 任一为 **`true`**。             |

### 位运算符

| 例子           | 名称                | 结果                                                     |
| :------------- | :------------------ | :------------------------------------------------------- |
| **`$a & $b`**  | And（按位与）       | 将把 $a 和 $b 中都为 1 的位设为 1。                      |
| **`$a | $b`**  | Or（按位或）        | 将把 $a 和 $b 中任何一个为 1 的位设为 1。                |
| **`$a ^ $b`**  | Xor（按位异或）     | 将把 $a 和 $b 中一个为 1 另一个为 0 的位设为 1。         |
| **`~ $a`**     | Not（按位取反）     | 将 $a 中为 0 的位设为 1，反之亦然。                      |
| **`$a << $b`** | Shift left（左移）  | 将 $a 中的位向左移动 $b 次（每一次移动都表示“乘以 2”）。 |
| **`$a >> $b`** | Shift right（右移） | 将 $a 中的位向右移动 $b 次（每一次移动都表示“除以 2”）。 |

### 其他运算符

#### 三元运算符：`？:`

```php
表达式1 ？ 表达式2 ： 表达式3
1成立执行2 ，不成立执行3
```

#### ``

 可以放系统命令 ，涉及到跨平台

```
$str = `ipconfig`;
var_dump($str);

输出：

string(802) " Windows IP 配置 以太网适配器 以太网: 媒体状态 . . . . . . . . . . . . : 媒体已断开连接 连接特定的 DNS 后缀 . . . . . . . : 无线局域网适配器 本地连接* 1: 媒体状态 . . . . . . . . . . . . : 媒体已断开连接 连接特定的 DNS 后缀 . . . . . . . : 无线局域网适配器 本地连接* 2: 媒体状态 . . . . . . . . . . . . : 媒体已断开连接 连接特定的 DNS 后缀 . . . . . . . : 无线局域网适配器 WLAN: 连接特定的 DNS 后缀 . . . . . . . : 本地链接 IPv6 地址. . . . . . . . : fe80::8538:d7f6:846f:8103%20 IPv4 地址 . . . . . . . . . . . . : 192.168.31.198 子网掩码 . . . . . . . . . . . . : 255.255.255.0 默认网关. . . . . . . . . . . . . : 192.168.31.1 以太网适配器 蓝牙网络连接: 媒体状态 . . . . . . . . . . . . : 媒体已断开连接 连接特定的 DNS 后缀 . . . . . . . : "
```

#### 屏蔽错误@

当这个代码出错时，屏蔽掉错误，什么也不打印

```php
打印一个没有的变量
echo @$a;
输出：
    Notice: Undefined variable: a in D:\phpStudy\WWW\myphp\index.php on line 2

echo @$xxx;
echo @$xxx;
输出：
    啥也不输出
```

#### =>

#### ->

#### instanceof

### 运算符的优先级





## 类型

### bool

### int

### float

### string



### 整体输出

```php
//类型
$a1 = true;
$b1 = false;
$a2 = 123;
$a3 = 123.123;
$a4 = 'holle world';
echo '<br/>';
echo 'a1是：',$a1,' 类型是：',var_dump($a1),'<br/>';
echo 'a2是：',$a2,' 类型是：',var_dump($a2),'<br/>';
echo 'a3是：',$a3,' 类型是：',var_dump($a3),'<br/>';
echo 'a4是：',$a4,' 类型是：',var_dump($a4),'<br/>';
echo 'b1是：',$b1,' 类型是：',var_dump($b1),'<br/>';

输出：
a1是： 类型是：bool(true)
a2是：123 类型是：int(123)
a3是：123.123 类型是：float(123.123)
a4是：holle world 类型是：string(11) "holle world"
b1是： 类型是：bool(false)
```

### 数组array



### 对象object



### 资源resource



### NULL



### 强转类型

```php
$aa10 = (int)'ada';
var_dump($aa10);
var_dump((float)$aa10);
$bb10 = (int)$aa10;
var_dump($aa10);
输出：
int(0) float(0) int(0)
```

字符串转整形

```php
$num = '11';
var_dump((int)$num);//int(11)
```

## 流程控制

### 判断语句

#### if语句

与C/C++同理

不带括号只执行if后一条语句

```php
if(表达式) 执行语句；
-----------------------
if(表达式) 
	执行语句；
else
	执行语句；
-----------------------
if(表达式) 
	执行语句；
else if(表达式)
	执行语句；
```



#### switch

不带break 会继续执行后面的case

case后没有语句，直接执行后面的

```php
switch(表达式){
	case 1：
		语句块1;
		break;
	case 2:
		语句块2;
		break;
	......
	default:
		语句块n;	
}
```



### 循环语句

#### for

```php
for(表达式1;表达式2;表达式3)
{
	语句块;
}
表达式1：初始化，可以多个
表达式2：逻辑判断，可以多个
表达式3：加减语句，可以多个

```



#### while

```php
while(表达式)
{
	语句;
}
```



#### do...while

```php
do
{
	语句;
}while(表达式);
```

### 特殊的控制语句

#### break

跳出当前所在循环语句

break后面可以跟数字，表示跳出第几层，默认是1**（C语言不支持）**

php支持break跳出多层

```php
for($i = 0;$i<5;$i++)
{
    echo "\$i执行到了第{$i}遍啦啦啦啦啦<br />";
    for($j = 0;$j<5;$j++)
    {
        if($i == 2)
            break 2;
        echo "\$j执行到了第{$j}遍<br />";
    }
}
```

C语言break跟数字会报错

```c
int main()
{
	for (int i = 0; i <= 5; i++)
	{
		printf("%d打印到了%d层lalalaalalala\n", i, i);
		for (int j = 0; j <= 5; j++)
		{
			if (j == 2)
				break 2;
			printf("%d打印到了%d层\n", i, i);
		}
	}
	return 0;
}
```

#### contine

跳过本次循环后的语句

#### exit()

退出程序

```php
//可以直接写
exit;
//可以跟输出语句
exit('程序退出啦');
```

#### die()

与exit()一样

## 函数

### 格式

```php
function 函数名（参数...）
{
	函数体
	return 表达式; 可以返回 也可以不返回，不写默认返回null
}
```

### 关键字是：**function**

```php
function test()
{
    echo '你好';
}
test();
```

### 传参

```php
function test($a,$b)
{
    echo $a+$b;
}
test(1,2);
```

#### 引用传参

与C++的引用传参一样

```php
function test4(&$a)
{
    $a++;
}
$b = 1;
test4($b);
echo $b;//2
```

#### 参数默认值

**默认参数从右往左加**

```php
function test5($a = 222)
{
    echo $a;//222
}
test5();
```

#### 可变传参

##### func_get_args();

以**数组**的形式获取参数

返回值是数组

```php
function test6()
{
    $arr = func_get_args();
    var_dump(func_get_args());
    //array(7) { [0]=> int(1) [1]=> int(2) [2]=> int(3) [3]=> int(4) [4]=> int(5) [5]=> int(6) [6]=> string(4) "ssss" }
    var_dump($arr);
    //array(7) { [0]=> int(1) [1]=> int(2) [2]=> int(3) [3]=> int(4) [4]=> int(5) [5]=> int(6) [6]=> string(4) "ssss" }
}
test6(1,2,3,4,5,6,'ssss');

```

##### func_get_arg();

以数**组的下标**形式获取参数

```php
function test6()
{
    var_dump(func_get_arg(6));
    //string(4) "ssss"
}
test6(1,2,3,4,5,6,'ssss');
```

##### func_num_args();

返回传入参数的个数

```php
function test6()
{
    var_dump(func_num_args());// int(7)
}
test6(1,2,3,4,5,6,'ssss');
```

### 可变函数

**把函数赋值给变量**

也就是说a变量成了 test6()  直接可以当函数用

**这是test6的别名？**

```
function test6()
{
    var_dump(func_num_args());//
}
$a = 'test6';
$a(1,2,3,4,5,6,'ssss');
```

### 递归函数

```
{
    echo $n.' ';
    if($n > 0)
        test($n-1);
    else
        echo '<-->';
    echo $n,' ';
}
test(3);//3 2 1 0 <-->0 1 2 3

```



### 返回值

```php
function test($a,$b)
{
    $c =  $a+$b;
    return $c; 
}
$d = test(1,2);

echo "\$d等于",$d;
```

### 函数的路径

函数内写的绝对路径 是盘的根目录

而html中绝对路径是 网站的根目录

## 数组

不写下标直默认0开始

可以写键值对



```php

//方式一
$struct[0] = 20;
$struct[1] = '张三';
$struct[2] = '男';
$struct[3] = '70.5kg';
print_r($struct);

$struct[] = 20;
$struct[] = '张三';
$struct[] = '男';
$struct[] = '70.5kg';
print_r($struct);

var_dump($struct);
//方式二
$struct[] = 20;
$struct[] = '张三';
$struct[] = '男';
$struct[] = '70.5kg';

//方式三
$struct[0] = array(20,'张三','娜娜');
$struct[0] =  20,'张三','娜娜';

//方式四
$struct[0] = array('年龄'=>20,'name'=>'张三');
echo '<br />';

echo $struct['name'];//20
//方式五
$struct['num'] = 20;
$struct['name'] = '张三';
$struct['sex'] = '男';
echo '<br />';

echo $struct['num'];//20
echo $struct[1];//张三
```

### 数组的函数

#### [array_count_values](https://www.php.net/manual/zh/function.array-count-values.php) 

— 统计数组中所有的值

返回值是一个数组

```php
<?php
$array = array(1, "hello", 1, "world", "hello");
print_r(array_count_values($array));
?>
```

![image-20230506145452393](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/imageimageimage-20230506145452393.png)

#### [array_key_exists](https://www.php.net/manual/zh/function.array-key-exists.php) 

- — 检查数组里是否有指定的键名或索引

  ### 

array_key_exists(string|int `$key`, array `$array`): bool

成功时返回 **`true`**， 或者在失败时返回 **`false`**。

```
$array = array(1, "hello", 1, "world", "hello");
//print_r(array_count_values($array));
var_dump(array_key_exists("zhangsan",$array));
var_dump(array_key_exists("hello",$array));
```

![image-20230506150229466](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/imageimage-20230506150229466.png)

#### [array_search](https://www.php.net/manual/zh/function.array-search.php) 

- — 在数组中搜索给定的值，如果成功则返回首个相应的键名

  array_search([mixed](https://www.php.net/manual/zh/language.types.declarations.php#language.types.declarations.mixed) `$needle`, array `$haystack`, bool `$strict` = **`false`**):

  (值，所在数组，判断类型（true）)

  写true就是要判断所找到的值的类型是否相等

```php
<?php
$array = array('name'=> "zhangsan",'sex' => "男");

var_dump(array_search("name",$array));//false
var_dump(array_search("zhangsan",$array));//true 返回key的值
var_dump(array_search("hello",$array));//false
```

![image-20230506152536417](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/imageimage-20230506152536417.png)

#### [in_array](https://www.php.net/manual/zh/function.in-array.php) 

- — 检查数组中是否存在某个值

如果找到 `needle` 则返回 **`true`**，否则返回 **`false`**。

```php
<?php
$os = array("Mac", "NT", "Irix", "Linux");
if (in_array("Irix", $os)) {
    echo "Got Irix";
}
if (in_array("mac", $os)) {
    echo "Got mac";
}
?>
```

#### [list](https://www.php.net/manual/zh/function.list.php) 

- — 把数组中的值赋给一组变量

```php
<?php

$info = array('coffee', 'brown', 'caffeine');

// 列出所有变量
list($drink, $color, $power) = $info;
echo "$drink is $color and $power makes it special.\n";

// 列出他们的其中一个
list($drink, , $power) = $info;
echo "$drink has $power.\n";

// 或者让我们跳到仅第三个
list( , , $power) = $info;
echo "I need $power!\n";

// list() 不能对字符串起作用
list($bar) = "abcde";
var_dump($bar); // NULL
?>
```

#### [arsort](https://www.php.net/manual/zh/function.arsort.php) 

— 对数组进行降向排序并保持索引关系

#### [asort](https://www.php.net/manual/zh/function.asort.php) 

— 对数组进行升序排序并保持索引关系

第二个参数可选

> - **`SORT_REGULAR`** - 正常比较单元 详细描述参见 [比较运算符](https://www.php.net/manual/zh/language.operators.comparison.php) 章节
> - **`SORT_NUMERIC`** - 单元被作为数字来比较
> - **`SORT_STRING`** - 单元被作为字符串来比较
> - **`SORT_LOCALE_STRING`** - 根据当前的区域（locale）设置来把单元当作字符串比较，可以用 [setlocale()](https://www.php.net/manual/zh/function.setlocale.php) 来改变。
> - **`SORT_NATURAL`** - 和 [natsort()](https://www.php.net/manual/zh/function.natsort.php) 类似对每个单元以“自然的顺序”对字符串进行排序。
> - **`SORT_FLAG_CASE`** - 能够与 **`SORT_STRING`** 或 **`SORT_NATURAL`** 合并（OR 位运算），不区分大小写排序字符串。

```php
<?php
$fruits = array("d" => 70, "a" => 60, "b" => 80, "c" => 30);
asort($fruits);
print_r($fruits);
?>
```

![image-20230508202253030](C:\Users\uaena\AppData\Roaming\Typora\typora-user-images\image-20230508202253030.png)



#### [array_filter](https://www.php.net/manual/zh/function.array-filter.php)

 — 使用回调函数过滤数组的元素

```php
<?php
echo '<br />';

function odd($var)
{
    // 返回输入整数是否为奇数（单数）
    return $var & 1;
}
function even($var)
{
    // 返回输入整数是否为偶数
    return !($var & 1);
}
$array1 = ['a' => 1, 'b' => 2, 'c' => 3, 'd' => 4, 'e' => 5];
$array2 = [6, 7, 8, 9, 10, 11, 12];
echo "Odd :\n";
print_r(array_filter($array1, "odd"));
echo "Even:\n";
print_r(array_filter($array2, "even"));
echo '<br />';

?>
```

## 字符串函数

### [trim](https://www.php.net/manual/zh/function.trim.php)

trim — 去除字符串首尾处的空白字符（或者其他字符）

返回过滤后的字符串。

> - " " (ASCII `32` (`0x20`))，普通空格符。
> - "\t" (ASCII `9` (`0x09`))，制表符。
> - "\n" (ASCII `10` (`0x0A`))，换行符。
> - "\r" (ASCII `13` (`0x0D`))，回车符。
> - "\0" (ASCII `0` (`0x00`))，空字节符。
> - "\v" (ASCII `11` (`0x0B`))，垂直制表符。

可以在第二个参数添加要删除的字符、字符串

### [strtoupper](https://www.php.net/manual/zh/function.strtoupper.php)

 — 将字符串转化为大写

返回转换后的大写字符串。

```php
<?php
$str = "Mary Had A Little Lamb and She LOVED It So";
$str = strtoupper($str);
echo $str; // 打印 MARY HAD A LITTLE LAMB AND SHE LOVED IT SO
?>
```

### [strtolower](https://www.php.net/manual/zh/function.strtolower.php)

strtolower — 将字符串转化为小写

### [substr_count](https://www.php.net/manual/zh/function.substr-count.php)

substr_count — 计算字串出现的次数

该函数返回 int。

参数（字符串，要搜索的字符串，开始计数的偏移下标，有偏移下标后最大搜索长度）

```php
$str = "testtest"
substr_count(str,'te');//2

// 输出 1，因为该函数不计算重叠字符串
$text2 = 'gcdgcdgcd';
echo substr_count($text2, 'gcdgcd');//1
```

### [stripos](https://www.php.net/manual/zh/function.stripos.php)

stripos — 查找字符串首次出现的位置（不区分大小写）

#### 参数

```php
$str = "testtest"
strpos($str,'t');
strpos($str,'t',1,2);
```

#### 返回值

找到了返回下标(从0开始)

如果未发现将返回 **`false`**。



### [strstr](https://www.php.net/manual/zh/function.stristr.php)

查找子串

返回匹配的子字符串。如果 `needle` 未找到，返回 **`false`**。





### [str_replace](https://www.php.net/manual/zh/function.str-replace.php)

str_replace — 子字符串替换

参数(原字符，换成的字符，在那个串里,$count（如果更改成功，则会置换成更改次数，）)

第一二个参数可以是数组

```php
<?php
$str = 'testtest';
$STR = str_replace('te','TE',$str);

echo $str;//testtest
echo $STR;//TEstTEst
?>
$STR = str_replace(array('t','e'),array('T','E'),$str);
    
```

### 字符串截取函数

#### [substr](https://www.php.net/manual/zh/function.substr.php)

substr — 返回字符串的子串

##### 参数

参数（字符串，开始截取的位置（下标），截取长度）

第二个参数是负数的话，从后往前截取

##### 返回值

返回提取的 `string` 部分或者空字符串。

### 字符串分割函数

#### [explode](https://www.php.net/manual/zh/function.explode.php)

explode — 使用一个字符串分割另一个字符串

```php
$str = 'test,test1|test2,test3';
var_dump(explode(',',$str));//3串
echo "\n";
var_dump(explode(',',$str,2));//2串
echo "\n";
var_dump(explode('|',$str));//2串
echo "\n";
//看图
```

![image-20230509155026979](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/imageimage-20230509155026979.png)

#### [str_split](https://www.php.net/manual/zh/function.str-split.php)

 — 将字符串转换为数组

返回值：数组

参数（字符串，分割的字符长度）

## 与HTM标签相关函数

### [hemlspecialchars](https://www.php.net/manual/zh/function.htmlspecialchars.php)

htmlspecialchars — 将特殊字符转换为 HTML 实体

用户输入html代码，不按照代码执行，而是把代码转换成字符串显示出来

### [strip_tags](https://www.php.net/manual/zh/function.strip-tags.php)

strip_tags — 从字符串中去除 HTML 和 PHP 标签

第二个参数可以是被忽略的标签 如：“<div><p>"

用户输入html代码，不按照代码执行，干掉代码，只显示要输出的文本



## 预定义超全局数组变量

### 说明

PHP 中的许多预定义变量都是“超全局的”，这意味着它们在一个脚本的全部作用域中都可用。在函数或方法中无需执行 **global $variable;** 就可以访问它们。

### 变量是

- [$GLOBALS](https://www.php.net/manual/zh/reserved.variables.globals.php)

- [$_SERVER](https://www.php.net/manual/zh/reserved.variables.server.php)
- [$_GET](https://www.php.net/manual/zh/reserved.variables.get.php)

传递数据

- [$_POST](https://www.php.net/manual/zh/reserved.variables.post.php) 

传递数据

- [$_FILES](https://www.php.net/manual/zh/reserved.variables.files.php)
- [$_COOKIE](https://www.php.net/manual/zh/reserved.variables.cookies.php)
- [$_SESSION](https://www.php.net/manual/zh/reserved.variables.session.php)
- [$_REQUEST](https://www.php.net/manual/zh/reserved.variables.request.php)
- [$_ENV](https://www.php.net/manual/zh/reserved.variables.environment.php)







## 关键字

### 输出echo

输出变量：`echo $a;`

多种输出：`echo 'abc','<br/>',123,$a;`



### 输出类型var_dump

```php
$a = 123;
var_dump($a);
输出int
```

### 转义字符\

```php
echo '单引号：\' , 斜杠\\';
输出：
    单引号：'，双引号："，斜杠\,
```

### 引号"" ''

#### 单引号''

不会直接解析 变量，双引号会

```php
$a2 = 123;
echo '$a2';
echo "$a2";
输出：
$a2
123
```

另一种方式给变量加`{}`

```php
echo "这是：$a2","这是：{$a2}";
echo '<br/>';
echo '这是：$a2','这是：{$a2}';
echo '<br/>';
输出：
这是：123这是：123
这是：$a2这是：{$a2}
```



#### 双引号""

单引号双引号 可以嵌套

#### 嵌套

引号可以互相嵌套

```php
echo '她说："你是好人"';
输出：
她说："你是好人"
```

### 定界符<<<

格式：name之能是字母，数字，下划线

```php
<<<name
content（内容）
name；
```



```
$delimiter=<<<aaa
hello world！ 21212_{$a2}_32121"""'''''\
aaa;
echo '<br/>';

var_dump($delimiter);
```

### 销毁变量unset()

```php
$a = 123;
unset($a);
此时$a就是null
```

### 定义函数function

```php
function test()
{
    echo '你好';
}
test();
```

### 全局变量globa

声明$xxa为全局变量，只能在当前作用域声明

```php
$xxa = 10;
define('XXA',10);
function test2()
{
    global $xxa;//声明$xxa为全局变量，只能在当前作用域声明
    echo $xxa;
    echo XXA;
}
test2();
```

### 数组个数count()

返回数组实际个数

```php
//方式一
$struct[0] = 20;
$struct[1] = '张三';
$struct[2] = '男';
$struct[3] = '70.5kg';
print_r($struct);
echo '<br />';

echo count($struct);//4
echo '<br />';

```

## 传递数据

### 1.get方式

例如：

```
http://localhost/myphp/index.php
http://localhost/myphp/index.php?name='zhangsan'&id=520

```

![image-20230506141709688](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/imageimage-20230506141709688.png)

### 2.post 方式

代码

```php
<?php
var_dump($_POST);
?>

<!DOCTYPE html>
<html>
<head>
    <meta charset = "utf-8" />
    <title>预定义超全局数据变量</title>
</head>
<body>
    <form method="post">
        姓名:<input type="text" name='username' /><br />
        性别:<input type="text" name='sex' /><br />
        <input type="submit" value='提交' />
    </form>
</body>
</html>
```

#### 运行

![image-20230506142954425](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/imageimage-20230506142954425.png)

#### 填入信息

![image-20230506143019323](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/imageimageimage-20230506143019323.png)

#### 提交

![image-20230506143045080](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/imageimage-20230506143045080.png)

### 将以上代码改成get方式

会将表单中填写的数据放在URL地址中

#### 改代码

![image-20230506143548289](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/imageimage-20230506143548289.png)

```php
<?php
//var_dump($_POST);
var_dump($_GET);
?>

<!DOCTYPE html>
<html>
<head>
    <meta charset = "utf-8" />
    <title>预定义超全局数据变量</title>
</head>
<body>
    <form method="get">//get
        姓名:<input type="text" name='username' /><br />
        性别:<input type="text" name='sex' /><br />
        <input type="submit" value='提交' />
    </form>
</body>
</html>
```

#### 填写+运行

![image-20230506143636103](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/imageimage-20230506143636103.png)

## 正则表达式

### 定界符

一般是`/`

还可以是除了字母、数字、反斜线以外的字符

比如 # ！ {} |  定界符放在正则表达式的其实位置，和结束位置

案例

```
/haha/
```



| \d         | 匹配任意一个十进制数字，等价于【0-9】                        |
| ---------- | ------------------------------------------------------------ |
| \D         | 匹配任意一个除十进制数字意外字符                             |
| \s         | 匹配任意一个空白字符，比如幻夜符、换行符、回车符、制表符、垂直制表符 |
| \S         | 匹配除空白字符意外的任何一个字符                             |
| \w         | 匹配任意一个数字或字母或下划线                               |
| \W         | 匹配除数字、字母、下划线以外的任意一个字符                   |
| .          | 匹配除换行符以外的任意一个字符                               |
| *          | 匹配0次，或1次，或多次前面的字符                             |
| +          | 匹配1次或多次前面的字符                                      |
| ？         | 匹配0次或1次前面的字符                                       |
| {n}        | 表示前面的字符恰好出现n次                                    |
| {n,}       | 表示线面的字符出现不少于n次                                  |
| {n,m}      | 表示前面的字符至少出现n次，最多出现m次                       |
| ^或\A      | 匹配字符串开始位置 比如 ^test 必须以t开头才能匹配            |
| $或\Z      | 匹配字符串的结束位置 比如 test$ 必须以t结尾才能匹配          |
| \|         | 匹配两个或多个模式                                           |
| []         | 匹配方括号中的任意一个字符                                   |
| ()         | 将圆括号作为一个整体以便将期中的内容获取到，可以使用 \\\\数字 表示括号的内容 比如 /t(e)st\\\1/ ，\\\\1代表第一个括号里的内容，匹配的时候 必须是 ’teste‘才能匹配成功 |
| .与{n}配合 | /t.{3}st/ 表示在t和st之间任意字符正好出现三次                |
| .与*配合   | /t.*st/ 表示在t和st之间任何字符出现任意次数<br />贪婪匹配，尽可能多的匹配所有字符  比如 testabst 匹配完是testabst<br />在.\*后加? 解决贪婪匹配——懒惰匹配 比如testabst 匹配完是test <br /> |





#### 相关函数

##### preg_match_all()

作用

用正则表达式在字符串中找字符串，存在二维数组里

参数(正则表达式的字符串；要查找的字符串；把查找的字符串放在数组里（二维）)

### 模式修正符

| i    | 在和模式进行匹配时不区分大小写 比如：/test/i 匹配时 TEST，Test，test 都能匹配上 |
| ---- | ------------------------------------------------------------ |
| m    | 多行匹配，条件1：目标字符串必须包含“\n” ，条件2：正则表达式必须出现^或$ |
| s    | . 匹配的所有字符将包括换行符号（\n） 原本不包含              |
| U    | 禁止贪婪匹配                                                 |

### 与正则表达式配合的函数

#### [preg_match](https://www.php.net/manual/zh/function.preg-match.php)

preg_match — 执行匹配正则表达式

只匹配一次 ，找到返回1，找不到返回0

#### [preg_maech_all](https://www.php.net/manual/zh/function.preg-match-all.php)



#### [preg_replace](https://www.php.net/manual/zh/function.preg-replace.php)

preg_replace — 执行一个正则表达式的搜索和替换

##### 参数

（正则表达式；要改变的字符串；被改变的字符串；默认-1 ，要替换的个数；存储改变的次数）

第一二个参数可以放数组

##### 返回值

返回一个字符串

```php
$pattern = '/<div>(.*?)<\/div>/';
$str1 = '<a>\\1</a>';//   \\1代表上一条找到的串
$str='abc<div>asddddd</div>ads';
//如果用正则表达式找到了这个串则返回1，内容存在$arr里
if(preg_match($pattern,$str,$arr)){
   // 将找到的串 替换成str1
    var_dump(preg_replace($pattern,$str1,$str));
}
else{
    echo 'error';
}
var_dump($str);

输出：
    
string(20) "abc<a>asddddd</a>ads"//被替换过的串
string(24) "abc<div>asddddd</div>ads"//原来的串
//只替换了标签
```

## 增强

### 设置时区

```
date_default_timezone_set('Asia/Shanghai');
```

### 获取当前Unix时间戳

```
time()
```

#### 获取指定函数时间戳

```
mktime()
```

#### 时间戳转换

date — 格式化 Unix 时间戳

参数：第一个参数是格式，第二个参数是时间戳，默认现在

返回值：返回格式化后的日期字符串。

```
date()
date("Y-m-d H:i:s");//2001-03-10 17:16:18（MySQL DATETIME 格式）
```

### 获取Unix时间戳和微秒数

```php
microtime()//返回微秒和时间戳
microtime()//返回浮点数的时间戳和微秒数
    
    date_default_timezone_set('Asia/Shanghai');
$STime=microtime(true);
for($i =0;$i<100000000;$i++)
{}
$ETime=microtime(true);
echo 'for循环花费了'.round(($ETime-$STime),4).'秒';

```

### 图像处理

#### 绘制图像

```php
<?php
header('Content-type:image/jpeg');//告诉浏览器 这是一个图片,必须在第一行之前不能输出内容
$img=imagecreatetruecolor(200,200);//新建一个长和高200像素的真彩色图像
$color1=imagecolorallocate($img,50,50,200);//新建颜色
$color1=imagecolorallocate($img,230,50,50);
$color1=imagecolorallocate($img,50,230,50);
imagefill($img,0,0,$color1);//把颜赋值给图片
imagejpeg($img);//以jpeg输出给浏览器
imagedestroy($img);//释放图片资源
```

```
imagejpeg($img,'green.jpeg');//生成图片，保存在相对路径
指定路径：
imagejpeg($img,'image/green.jpeg');

```

![image-20230509221334775](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/imageimageimage-20230509221334775.png)

#### 功能实现

##### 绘制验证码

```php
<?php
header('Content-type:image/jpeg');
$width =120;
$height = 40;
//验证码文字
$element=array('a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z');
$string="";
for($i = 0;$i<5;$i++){
    $string .= $element[rand(0,count($element)-1)];//随机出字母，拼接到字符串上
}
$img = imagecreatetruecolor($width,$height);//定义图像大小
                                    //R           G             B 颜色值
$colorBg=imagecolorallocate($img,rand(200,255),rand(200,255),rand(200,255));
$colorBorder=imagecolorallocate($img,rand(200,255),rand(200,255),rand(200,255));
$colorDian=imagecolorallocate($img,rand(100,200),rand(100,200),rand(100,200));
$colorXian=imagecolorallocate($img,rand(100,200),rand(100,200),rand(100,200));
$colorStr=imagecolorallocate($img,rand(10,100),rand(10,100),rand(10,100));

imagefill($img,0,0,$colorBg);//填充颜色
imagerectangle($img,0,0,$width-1,$height-1,$colorBorder);//边框
for($i = 0;$i<100;$i++){
    //                  横纵坐标
    imagesetpixel($img,rand(0,$width-1),rand(0,$height-1),$colorDian);//画一个像素的颜色块
}
for($i = 0;$i<3;$i++){//画随机线条
    //      图    ；起点横坐标      ；起点纵坐标        ；终点横坐标            ；终点纵坐标        ；颜色
    imageline($img,rand(0,$width/2),rand(0,$height/2),rand($width/2,$width),rand(0,$height/2),$colorXian);
}
//imagestring($img,5,0,0,"abcd",$colorStr);//写字
            //图；字符串角度；字左下角横坐标；纵坐标                ；颜色      ；字体路径           ；输出的字体
imagettftext($img,25,rand(-5,5),rand(5,15),rand($height-10,$height-5),$colorStr,'font/Quantum.otf',$string);//写字



imagejpeg($img);//输出图片


imagedestroy($img);//释放图片资源

?>
```

##### 图片加文字水印

```php
<?php
header('Content-type:image/jpeg');
$strrand = rand(1,6);//定义随机数
$imgPath="images/IU{$strrand}.jpg";//定义图片路径，图片右6张 随机出现
$img=imagecreatefromjpeg($imgPath);//以jpeg格式打开一张图片

$imgWaterMarkPath="images/watermark.png";
$imgWaterMark = imagecreatefrompng($imgWaterMarkPath);

//定义字体
$strFontSize=30;//大小
$strFont='font/SourceHanSansCN-Regular.otf';//路径
$strContent="IU李知恩";//内容
$strContent="www.iulzn.com";//内容
//获取图片宽高
$width=imagesx($img);
$height=imagesy($img);

$WaterMarkWidth=imagesx($imgWaterMark);
$WaterMarkHeight=imagesy($imgWaterMark);

//getimagesize('images/IU.jpg');//返回数组，长宽和其他值

//获取字体的区域
$position=imagettfbbox($strFontSize,0,$strFont,$strContent);
$stringWidth=$position[2]-$position[0];//字体坐标相减获得字体长度

$colorS=imagecolorallocate($img,255,255,255);
// imagettftext($img,100,0,100,100,$colorS,'font/Quantum.otf',"www.iulzn.com");
imagettftext($img,$strFontSize,0,$width-1-$stringWidth-($width/50),$height-1-($height/50),$colorS,$strFont,$strContent);

/*
参数：
$img:目标图像资源
$imgWaterMark:水印图像资源
100：所要拷贝到目标图像自愿上面的坐标（x轴位置
100：所要拷贝到目标图像自愿上面的坐标（y轴位置
0：从水印的图像资源的x坐标为0的位置开始拷贝
0：从水印的图像资源的y坐标为0的位置开始拷贝
$WaterMarkWidth：所要拷贝的水印图像的长度
$WaterMarkHeight：所要拷贝的水印图像的高度

最后一个参数是透明度 0-100 透明-不透明
*/
imagecopy($img,$imgWaterMark,100,100,0,0,$WaterMarkWidth,$WaterMarkHeight);
//放在左下角
//imagecopy($img,$imgWaterMark,$width-1-$WaterMarkWidth,$height-1-$WaterMarkHeight,0,0,$WaterMarkWidth,$WaterMarkHeight);
//调透明度，最后一个参数是透明度 0-100 透明-不透明
imagecopymerge($img,$imgWaterMark,$width-1-$WaterMarkWidth,$height-1-$WaterMarkHeight,0,0,$WaterMarkWidth,$WaterMarkHeight,50);




imagejpeg($img);//输出图片
imagedestroy($img);//释放图片资源

?>
```

### 文件处理

#### 判断函数

##### is_file()

//判断文件名是否是正常文件

```php
var_dump(is_file('index.php'));//true
```

##### is_dir()

//判断文件名是否是目录

```php
var_dump(is_file('../myphp'));//true
```



#### 文件属性

##### file_exists()

检查文件或目录是否存在 

##### filesize()

获取普通文件的大小

#####  is_readable

判断给定文件名是否可读

##### is_writable()

判定给定文件名时候可写

##### filectime()

获取文件名的创建时间

##### filemtime()

获取文件修改时间

##### fileatime()

获取文件上次访问时间

##### stat()

获取文件大部分属性

##### 演示

```php
<?php
date_default_timezone_set("Asia/Shanghai");
echo "is_file".var_dump(is_file('index.php'))."<br />";//bool(true) is_file
echo "file_exists".var_dump(file_exists('index.php'))."<br />";//bool(true) file_exists
echo "filesize".var_dump(filesize('index.php'))."<br />";//int(320) filesize
echo "is_readable".var_dump(is_readable('index.php'))."<br />";//bool(true) is_readable
echo "is_writable".var_dump(is_writable('index.php'))."<br />";//bool(true) is_writable
echo "filectime".var_dump(filectime('index.php'))."<br />";//int(1681234576) filectime
echo "filectime".date('Y-m-d G:i:s',filectime('index.php'))."<br />";//filectime2023-04-12 1:36:16
echo "filectime".var_dump(stat('index.php'))."<br />";//获取文件大部分属性
?>
```

#### 目录操作

##### basename()

返回路径中的文件名部分

##### dirname()

返回路径中目录部分

##### pathinfo()

返回文件路径的信息

##### opendir()

打开目录句柄

##### readdir()

从目录句柄中国读取条目，返回目录中下一个文件的文件名

##### rewinddir()

重置目录句柄

##### closedir()

关闭目录句柄

##### mkdir()

新建目录

##### rmdir()

删除指定的空目录

##### scandir()

列出指定路径中的文件和目录

##### 演示

```php

echo "File----".__FILE__."<br />";//File----D:\phpStudy\WWW\myphp\index.php
echo "basename----".basename(__FILE__)."<br />";//basename----index.php
echo "dirname----".dirname(__FILE__)."<br />";//dirname----D:\phpStudy\WWW\myphp
echo "pathinfo----".var_dump(pathinfo(__FILE__))."<br />\n";
/*
array(4) {
  ["dirname"]=>
  string(21) "D:\phpStudy\WWW\myphp"
  ["basename"]=>
  string(9) "index.php"
  ["extension"]=>
  string(3) "php"
  ["filename"]=>
  string(5) "index"
}
*/
$dir=opendir('../');//打开目录句柄
$newdir = "newdir";
var_dump(readdir($dir));//返回目录句柄中的下一个文件
var_dump(readdir($dir));
var_dump(readdir($dir));
var_dump(readdir($dir));
var_dump(readdir($dir));
var_dump(readdir($dir));

var_dump(rewinddir($dir));//重置目录句柄
var_dump(closedir($dir));//关闭目录句柄
var_dump(mkdir($newdir));//新建目录 true
/*
mkdir参数：
'newdir'：要创建的目录名
0777：目录权限参数
true：允许递归创建
*/
//var_dump(rmdir($newdir));//删除指定的空目录
var_dump(scandir('./images'));//列出指定路径中的文件和目录

```

#### 文件操作

##### fopen()

打开文件或URL

##### fread()

读取文件

##### fgets()

从文件指针中读取

##### 演示+函数

```php 
header("Content-type:text/html;charset=utf-8");
$file = fopen('./newdir/text.txt','r+');

var_dump(fread($file,1));

var_dump(fgets($file));//一次读一行
var_dump(fgets($file));//一次读一行
var_dump(fgets($file));//一次读一行

var_dump(feof($file));//读取文件是否读完了 读完了返回true

rewind($file);//重置文件指针
var_dump(fseek($file,0,SEEK_END));//定位文件指针，在第三个参数的位置上添加第二个参数的偏移量
var_dump(fwrite($file,"这是fwrite写入的文本"));//向文件写入，会覆盖已有的文本，返回写入的字节数 
//flock();//文件加锁
fclose($file);//关闭文件指针

//file_get_contents();//将整个文件读入一个字符串
//file_put_contents();//将字符串写入文件，覆盖
//rename();//重命名目录或文件
//readfile();//读入一个文件并写入到缓冲
```

#### 文件上传

```php
<?php
header('Content-type:text/html;charset=utf-8');
date_default_timezone_set('Asia/Shanghai');
//var_dump($_FILES);
/*
当用post方式上传文件时，全局变量$_FILES将会设置成一个数组，存储被上传文件的信息
array(1) {
  ["myfile"]=>
  array(5) {
    ["name"]=>
    string(88) "[IU TV] 【中字】'dlwlrma.' 音乐会 - 曼谷_190417_IU李知恩-Uaena_1920x1080.mp4"
    ["type"]=>
    string(9) "video/mp4"   //文件类型
    ["tmp_name"]=>
    string(45) "C:\Users\uaena\AppData\Local\Temp\php3E78.tmp"    //临时名字
    ["error"]=>
    int(0)      //有0个错误
    ["size"]=>
    int(316599039)
  }
}
*/
if(isset($_POST['submit'])){//检测变量是否已声明并且其值不为 null
    if(is_uploaded_file($_FILES['myfile']['tmp_name'])){//判断指定文件是否通过HTTP POST上传
        $arr=pathinfo($_FILES['myfile']['name']);//pathinfo返回文件路径信息，期中extension对应的是文件的后缀
        $newName=date('YmdGis').rand(1000,9999);
        //文件上传后，会先存储于服务器的临时目录中，可以使用该函数将上传的文件移动到新的位置
        //                        文件名                    ,新的名称
        if(move_uploaded_file($_FILES['myfile']['tmp_name'],"uploads/{$newName}.{$arr['extension']}")){
            echo '恭喜你上传成功！';
        }else{
            echo '对不起文件移动失败!';
        }
    }else{
      exit('可能有攻击，非法！');
    }
}
?>

<!DOCTYPE html>
<html lang="zg-CN">
<head>
<meta charset="utf-8" />
<title>上传页面</title>
</head>
<body>
<form action="" method="post" enctype="multipart/form-data">
    <input type="file" name="myfile" /><!-- type="file" 定义文件选择字段和 "浏览..." 按钮，供文件上传。-->
    <input type="submit" name="submit" value="开始上传" /><!--提交按钮 -->
</form>  
</body>
</html>
```

#### 文件下载

```php
<?php
date_default_timezone_set('Asia/Shanghai');

$file='images/IU1.7z';
$fileinfo=finfo_open(FILEINFO_MIME_TYPE);//打开文件，常量：返回mime类型
$mimeType=finfo_file($fileinfo,$file);//返回文件类型（
finfo_close($fileinfo);
//发送指定文件MIME类型的头信息
header("Content-type:{$mimeType};charset=utf-8");
//指定下载文件的描述
header('Content-Disposition:attachement;filename='.basename($file));
//指定文件的大小
header('Content-Length:'.filesize($file));
//读取文件内容输出到缓冲区，返回这个文件
readfile($file);

?>
```

## 会话控制cookie

### cookie

cookie是用来将网站的资料记录在客户端的技术，这种技术让web服务器能将一些资料，存放于客户端之中

#### 1.向客户端电脑设置Cookie

访问index.php

设置一维数组

```php
<?php
header('Content-type:text/html;charset=utf-8');
var_dump(setcookie('name','phpCookie',time()+3600));
var_dump(setcookie('email','123@qq.com',time()+3600));
?>


array(3) {
  ["name"]=>
  string(9) "phpCookie"
  ["email"]=>
  string(10) "123@qq.com"
}

```

#### 2.在服务器端读取Cookie内容

访问index1.php

```php
<?php
header('Content-type:text/html;charset=utf-8');
var_dump($_COOKIE);
?>
```



#### 3.将多维数组应用于Cookie

```php

var_dump(setcookie('member[name]','phpCookie',time()+3600));
var_dump(setcookie('member[email]','123@qq.com',time()+3600));

array(3) {
  ["name"]=>
  string(9) "phpCookie"
  ["email"]=>
  string(10) "123@qq.com"
  ["member"]=>
  array(2) {
    ["name"]=>
    string(9) "phpCookie"
    ["email"]=>
    string(10) "123@qq.com"
  }
}
```



#### 4.删除Cookie

```php
setcookie('username',$_POST['username'],time()-3600)
```

## 引用其他文件

### include

```php
index.php
{
#include "文件路径";
#include "./a.php";
}
index.php包含了a.php
```

此时在index.php文件的include后，可以使用a.php的所有变量或函数

此时在index.php文件的include前，a.php文件可以使用index.php中include前的一些变量和函数

### include_once

当被包含的文件被引用多次时，只会包含一次

### require

与include几乎 一致，但是出错后会直接终止程序，不会向下执行

include出错后会继续执行后面的语句

### require_once

同上
