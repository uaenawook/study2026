# MySQL

```
chcp 65001
cd /d D:\phpStudy\MySQL\bin
mysql -uroot -p
root

```

chcp 65001

cd /d D:\phpStudy\MySQL\bin

mysql -uroot -p

### 中文不对齐

```
charset gbk;
```

### 中文错误

```
set names gbk;
```



## 主键key

主键有唯一标识，可以是一个，也可以是两个

主键可以配合自增使用，删除主键之前必须把自增属性删除

```
2、新建数据库（sql语句）
create database name;
name:数据库名（不能和已有的库重名）
3、查询和选择数据库
show databases; #查看当前连接下的所有数据库
use name; #进入数据库（name为 已建立的数据库名）
4、删除数据库
drop database name;
#删除数据库会删除库中所有数据，慎用
5、新建数据库指定编码
（windows下不指明编码保存中文容易出错）
create database name charset utf8mb4 collate utf8mb4_general_ci;
6、查看数据库创建语句
show create database name;
————————————————
 
 - show databases； 查看所有数据库
 - use 数据库名；使用某个数据库
 - show tables； 显示当前选中数据库中的所有表
 
 - show tables form 数据库名； 显示某数据库中的表（不改变所选中数据库）
 - select database() ；查看所选中的数据库
 - desc 表名； 查看某表的结构
 - select * from 表名； 查看某表的全部记录
 - select version()；查看数据库版本（登陆前：mysql --version/mysql -V）
 - create table 表名( 列名 列类型...)；创建表
create table 表名(列名 数据类型；新建表
drop table 表名;删除表语句：
insert into 表名(字段1，字段2，…字段n) values(值1，值2，…值n);插入
insert into 表名 values(字段1，字段2，…字段n);插入
```

## 数据类型

![image-20230513190338465](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/imageimage-20230513190338465.png)

## 

![image-20230513190455601](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/imageimage-20230513190455601.png)

![image-20230513202048540](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/imageimage-20230513202048540.png)

![image-20230513202544691](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/imageimage-20230513202544691.png)

## 字符编码

![image-20230514094519675](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/imageimage-20230514094519675.png)

![image-20230514095856448](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/imageimage-20230514095856448.png)

## 编码错误

首先看一下客户端的编码格式

![image-20230514102511974](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/imageimageimage-20230514102511974.png)

![image-20230514102528067](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/imageimage-20230514102528067.png)

![image-20230514102718067](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/imageimage-20230514102718067.png)

### 同时修改三个编码

set names gbk；

![image-20230514102939503](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/imageimage-20230514102939503.png)

重新插入即可成功

![image-20230514103058146](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/imageimage-20230514103058146.png)

此时database字符集可以是utf-8，因为从gbk转成utf-8是老版本转新版本，新版本包含老版本，不会出错

如果是gbk转gb2312则会出问题，因为新版本转老版本，有的东西老版本没有

utf-8>gbk>gb2312;

**尽量一样就好了**

### 修改客户端字符集

在cmd下执行

chcp 65001  ——转换成UTF-8

chcp 936 ——转换gbk

## 函数

![image-20230514114859330](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/imageimage-20230514114859330.png)

## php数据库操作

```php
<?php
header('Content-type:text/html;charset=utf-8');
//与数据库创立链接
$link=@mysqli_connect('localhost','root','root','',3306);
//链接错误提示
if(mysqli_connect_errno()){
    exit(mysqli_connect_error());
}
//设置默认字符编码
mysqli_set_charset($link,'utf8');
//选择指定的数据库
mysqli_select_db($link,'test');

//对数据库执行SQL语句
//$query='insert into t1(info) values("张三，男，www.bilibili.com")';//插入数据
//mysqli_query($link,$query);//成功true 失败false

$query='select * from t1';
$result=mysqli_query($link,$query);
//----------------------------------------------------------
//var_dump(mysqli_fetch_row($result));//每次输出一条语句
/*while($date=mysqli_fetch_row($result))
{
    var_dump($date);//循环输出所有语句
}*/
//var_dump(mysqli_fetch_assoc($result));//索引形式返回
//第二个参数可选值：MYSQLI_ASSOC,MYSQLI_NUM,MYSQLI_BOTH(默认)
//var_dump(mysqli_fetch_array($result,MYSQLI_NUM));//数组形式返回
//----------------------------------------------------------
//总结上面直接全部
//打印第二个参数可选值：MYSQLI_ASSOC,MYSQLI_NUM,MYSQLI_BOTH(默认)
//var_dump(mysqli_fetch_all($result,MYSQLI_BOTH));

//返回一个代表结果字段的对象数组
var_dump(mysqli_fetch_field($result));//获取一个
var_dump(mysqli_fetch_fields($result));//全部获取

//语句执行成功返回bool
mysqli_real_query($link,$query);
//上条语句配合以下语句获取结果集
$result1=mysqli_store_result($link);
mysqli_fetch_row($result);


//获取结果中行的数量
var_dump(mysqli_num_rows($result));
//释放结果集的内存
mysqli_free_result($result);

//执行错误返回
$query='select * from t2';
if(!mysqli_query($link,$query)){
    var_dump(mysqli_errno($link));//错误码
    var_dump(mysqli_error($link));//错误信息
}


//其他函数
//获取前一个MySQL操作受影响的行数
mysqli_affected_rows($link);
//返回最后一次操作自动生成并使用的ID
mysqli_insert_id($link);
//转义用于SQL语句中的特殊字符防止SQL语句出错
$str=<<<STRING
sajkdhdkahdasjk""""""""asdadasd'''''asddadas'''""""das
STRING;
$str=mysqli_real_escape_string($link,$str);//转义
$query="insert into t1(info) values('{$str}')";
if(mysqli_query($link,$query))
{
    var_dump(mysqli_insert_id($link));
}
else
{
    var_dump(mysqli_errno($link));//错误码
    var_dump(mysqli_error($link));//错误信息
}

echo '<br />-----------------------------------------------------<br />';

//一次执行多个sql语句
//$query='insert into t1(info) values("张三");insert into t1(info) values("李四");insert into t1(info) values("王五");';
//mysqli_multi_query($link,$query);

echo '<br />-----------------------------------------------------<br />';
//预处理语句机制
//准备的sql语句里面使用占位符号?，来代表要改变的参数
$query='insert into t1(id,info) values(?,?)';
//准备要执行的SQL语句
$stmt=mysqli_prepare($link,$query);
var_dump($stmt);
//为?绑定变量
mysqli_stmt_bind_param($stmt,'is',$val1,$val2);
/*
i:int       d:double/float
s:string    b:二进制
*/
$val1='21';
$val2="行不行呢？";
//执行准备好的SQL语句
var_dump(mysqli_stmt_execute($stmt));

echo '<br />-----------------------------------------------------<br />';
//演示获取结果
$query='select * from t1 where id=? or id=?';
$stmt=mysqli_prepare($link, $query);
mysqli_stmt_bind_param($stmt,'ii',$val1,$val2);

$val1=1;
$val2=2;
if(mysqli_stmt_execute($stmt)){//执行成功返回true
	mysqli_stmt_bind_result($stmt,$id,$info);//绑定返回结果存储到$id,$info里
	while(mysqli_stmt_fetch($stmt)){//抓取数据
		echo "{$id}->{$info}<br />";
	}
}

//释放$stmt所占内存
mysqli_stmt_free_result($stmt);

//关闭$stmt语句
mysqli_stmt_close($stmt);

//关闭mysql链接
mysqli_close($link);




?>
```

