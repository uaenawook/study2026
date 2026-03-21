## 安装
安装tree：yum install -y tree
        yum install -y epel-release
安装man：yum install -y man-pages
## vim
退出：shift + ； 输入q！
删除报错：rm ./.name.txt.swp
## 登录
ssh root@43.138.46.248
## 操作系统
:帮助我们操作的系统
## 查看磁盘
df -h
top 查看cpu资源使用状态
netstat 查看网络连接状态
free 查看内存资源状态
df 查看磁盘分区资源状态
uname -r 查看linux内核版本信息
vmstat   报告关于内核线程、虚拟内存、磁盘、陷阱和 CPU 活动的统计信
sar 主要帮助我们掌握系统资源的使用情况，特别是内存和CPU的使用情况
stat 用于显示文件的状态信息
## 用户管理
1.新增：adduser name
2.密码：passwd name
3.删除用户：userdel -r name
4.显示当前用户: whoami

## 基本操作
1.显示路径：pwd
2.显示文件：ls
3.新建文件：touch name.c
4.编辑文件：nano name.c
5.显示文本文件：cat name.c
6.编译文件：gcc name.c
7.运行：./a.out

### ls
-l：以list（列表）形式显示更多文件属性
-a：显示隐藏文件
. ：当前路径
..：上级路径
cd：选择路径  cd .  ，  cd ..
-d：显示当前路径的信息
wgich ls :显示指令的地址
alias ls='ls --color=auto'
	/usr/bin/ls
alias : 给命令起别名
        alias 别名='cd..'
        只在当前程序生效
### pwd
显示当前命令
### cd
cd-：记录最近来的路径
~ :进入当前用户的家

### touch
创建文本文件
更新文件的创建时间、修改时间
### mkdir
创建目录
-p：可以跟一串目录
-p 在创建多层级目录的时候若上级目录不存在则创建
mkdir -p class_102/linux/lesson1
### rmdir
删除目录 
### rm
删除目录/文件
-r:递归删除
-f：强制删除
rm -rf /home :注意 你知道你自己在干什么
### man
安装man：yum install -y man-pages
手册：1、默认命令 2、系统函数 3、库函数
q：退出
回车/空格：下翻
### cp
cp test.c ../ 赋值到上层目录 不改名
cp test.c ../name.c 改名
cp test.c name.c 复制到当前目录改名
### mv
mv ../name.c .  将上层目录的nam.c  赋值到当前目录
cp -r lesson1 lesson2 递归拷贝 并重命名  -rf 强制不看提示的拷贝
mv name.c test2.c  重命名文件
mv lesson2 lesson3 重命名目录

### 查看
##### cat 
cat test1.c 正序查看文本
tac test1.c 逆序查看文本
-n ：带行号查看
##### more 查看不打开 下翻
-5： 查看5行内容注释
q：退出
/100 ：查看100的位置
##### less 查看不打开 上下翻
上下翻
-N ：显示行号
##### head 查看头10行
-3 ：查看前三行
##### tail 查看尾10行
-5 ：查看倒数5行
### echo
echo "hello linux"   显示文本到屏幕上
echo "hello linux" > log.txt 输出重定向 文件不存在，自动创建
&emsp;&emsp;输出重定向 会清空原始内容 重新写入
&emsp;&emsp;追加重定向 需要写两个>
&emsp;&emsp;&emsp;&emsp;echo "AAAAAAAAAAAAAA" >> log.txt

![image-20230405110334062](C:\Users\uaena\AppData\Roaming\Typora\typora-user-images\image-20230405110334062.png)

### cat
cat < log.txt :输入重定向
ctrl+d 退出

cat -n ：显示行数

### wc

wc -l mylog.txt

显示文本行数

### more

查看文件从第一行看，只能回车向下看

### less

查看文件  可以搜索 能上下键翻阅

/ 能搜索

### head

head mylog.txt

默认显示10行

-5  显示5行

### tail

显示末尾10行

可以- 行



### 查看文件的 100-120行
1.head -120 file.txt > temp.txt
&emsp;tail -20 temp.txt
2.head -120 file.txt | tail -20
|：管道

### date
获取时间：date +%Y-%m-%d_%H:%M:%S
获取时间戳：date +%s
显示时间戳对应的时间：+%Y-%m-%d_%H:%M:%S -d @1651212489
默认时间 1970.1.1_0:0:0 
对应的北京时间1970.1.1_8:0:0

```c
[wx@VM-16-12-centos lesson3]$ date +%Y-$m-%d
2023--05
[wx@VM-16-12-centos lesson3]$ date +%Y-%m-%d
2023-04-05
[wx@VM-16-12-centos lesson3]$ date +%Y-%m-%d_%H:%M:%S
2023-04-05_10:09:12
[wx@VM-16-12-centos lesson3]$ date +%Y-%m-%d/%H:%M:%S
2023-04-05/10:09:31
[wx@VM-16-12-centos lesson3]$ date +%s
1680660646
[wx@VM-16-12-centos lesson3]$ date +%s
1680660650
[wx@VM-16-12-centos lesson3]$ date +%s
1680660827
[wx@VM-16-12-centos lesson3]$ date -d @1680660827
Wed Apr  5 10:13:47 CST 2023
[wx@VM-16-12-centos lesson3]$ date -d @1680660827 | +%Y-%m-%d/%H:%M:%S-bash: +%Y-%m-%d/%H:%M:%S: No such file or directory
[wx@VM-16-12-centos lesson3]$ date -d @1680660827 +%Y-%m-%d/%H:%M:%S
2023-04-05/10:13:47
[wx@VM-16-12-centos lesson3]$ date -d @0 +%Y-%m-%d/%H:%M:%S
1970-01-01/08:00:00
[wx@VM-16-12-centos lesson3]$ 

```

时间戳起始时间是1970.1.1   0时:0分:0秒

为什么我们显示的是 8：00？   因为“格林威治” 是英国0:00就是中国北京的8:00

### sort

对文本可以排序

sort my.txt  升序

-r 降序

### uniq

文本去重

sort my.txt | uniq

### cal 显示日历
cal 显示当月日历
cal 2022 显示整年日历
cal -3 显示前中后月

### find
find /home/wx/ -name test1.c 
find 路径 -name 文件名 

~ 当前工作路径 /home/wx

### which

which ls

查看指令的路径

```c
[wx@VM-16-12-centos lesson3]$ which ls
alias ls='ls --color=auto'
	/usr/bin/ls
[wx@VM-16-12-centos lesson3]$ which pwd
/usr/bin/pwd
[wx@VM-16-12-centos lesson3]$ which which
alias which='alias | /usr/bin/which --tty-only --read-alias --show-dot --show-tilde'
	/usr/bin/alias
	/usr/bin/which
[wx@VM-16-12-centos lesson3]$ which clear
/usr/bin/clear

```

### whereis

查找命令的文件

```c
[wx@VM-16-12-centos lesson3]$ whereis my
my: /etc/my.cnf
[wx@VM-16-12-centos lesson3]$ whereis ls
ls: /usr/bin/ls /usr/share/man/man1/ls.1.gz /usr/share/man/man1p/ls.1p.gz
[wx@VM-16-12-centos lesson3]$ 

```



### grep
grep选项中，-E选项可以用来扩展选项为正则表达式；
  $表示匹配文件末尾，字符需要在$之前表示以字符结尾  a$表示以a结尾
^表示匹配文件起始，字符需要在 ^ 之后表示以字符起始  ^a表示以a起始

```c
cat file.txt | grep '99' 过滤带99的数字
grep '99' file.txt 效果同上
cat file.txt | grep -v '9' 排除带9的
[root@VM-16-12-centos lesson3]# grep 'bit' file.txt 
Hello bit
[root@VM-16-12-centos lesson3]# grep -i 'bit' file.txt 
Hello bit
Hello BIT
[root@VM-16-12-centos lesson3]# grep -in 'bit' file.txt 
3:Hello bit
4:Hello BIT
[root@VM-16-12-centos lesson3]# grep -E 'hello 99[0-5]' file.txt 
hello 990
hello 991
hello 992
hello 993
hello 994
hello 995
grep -i '^h' file.txt 查找h开头的
```
```c
//查找aaa
[wx@VM-16-12-centos lesson3]$ grep 'aaa' my.txt 
aaaaa
//查找 -i 不区分大小写
[wx@VM-16-12-centos lesson3]$ grep 'aaa' my.txt -i
aaaaa
AAAAA
// -v反向查找
[wx@VM-16-12-centos lesson3]$ grep 'aaa' my.txt -v
AAAAA
bbbbbb
cccccccccc
dddddd
eeeeee
BBBB
CCCC
DDDDDD
FFFFF
// -iv 查找不带有 aaa不区分大小写 的
[wx@VM-16-12-centos lesson3]$ grep 'aaa' my.txt -iv
bbbbbb
cccccccccc
dddddd
eeeeee
BBBB
CCCC
DDDDDD
FFFFF
// 显示行号
[wx@VM-16-12-centos lesson3]$ grep 'aaa' my.txt -ivn
3:bbbbbb
4:cccccccccc
5:dddddd
6:eeeeee
7:BBBB
8:CCCC
9:DDDDDD
10:FFFFF
[wx@VM-16-12-centos lesson3]$ grep 'aaa' my.txt -in
1:aaaaa
2:AAAAA
```



### zip

压缩：zip -r code.zip lesson3
解压：unzip code.zip
解压到tmp目录： unzip test2.zip -d /tmp
### tar
tar czf lesson3.tgz lesson3 压缩lesson3成lesson3.tgz
c ：新建压缩文件
z ：压缩成gzip
f ：新的文档名
v ：显示压缩过程
x ：解压
tar xzvf lesson3.tgz 
-C ：解压到指定目录
tar xzf lesson3.tgz -C test/

czf 压缩

xzf 解压

ztvf 查看

### 打包vs压缩
打包是放在一起
压缩是减少空间
### cd 计算器
quit 退出
echo "1+2+3" | bc

### uname -a
[wx@VM-16-12-centos linux]$ uname -a
Linux VM-16-12-centos 3.10.0-1160.45.1.el7.x86_64 #1 SMP Wed Oct 13 17:20:51 UTC 2021 x86_64 x86_64 x86_64 GNU/Linux
VM-16-12-centos：主机名称 hostname
3.10 ：内核版本，主次版本 次版本偶数稳定  奇数测试
.0-1160.45.1.：修正信息
el7 ：发行版本 CentOS-7
x86_64：计算机体系结构 cup平台型号 没64 就是32位
SMP：cup处理...
```c
[wx@VM-16-12-centos linux]$ cat /etc/redhat-release 
CentOS Linux release 7.6.1810 (Core) 
```
### 热键
ctrl + c  退出 
history   历史命令
tab 补全 和查找
file name.c 查看文件信息

### bc

计算器

quit退出

echo "1+2+3+4+5+6" |bc

计算结果



### 关机 云服务器永远不用关机
语法： shutdown [选项] ** 常见选项： **
-h ： 将系统的服务停掉后，立即关机。
-r ： 在将系统的服务停掉之后就重新启动
-t sec ： -t 后面加秒数，亦即『过几秒后关机』的意思
### ps
ps axj 
ps axj | grep bash 查看进程
### su - 
切换root用户  输入root的密码
变成普通用户 su - wx  /  enit  /ctrl+d
### sudo
临时提升用户权限

ctrl +r 查询历史命令   左右键选择

###   history

查看所有命令

### 文件属性
```
[wx@VM-16-12-centos lesson3]$ ll
total 16
-rw-r--r-- 1 wx wx   10 Apr 29 17:43 file1
-rw-r--r-- 1 wx wx    0 Apr 29 17:42 file2
-rw-r--r-- 1 wx wx    0 Apr 29 17:42 file3
-rw-r--r-- 1 wx wx    0 Apr 29 17:42 file4
-rw-rw-r-- 1 wx wx 9921 Apr 29 17:30 file.txt
-rw-rw-r-- 1 wx wx    0 Apr 29 22:01 wx.txt
```



#### 第一个字符 ：文件类型

-：普通文件[指令，文本，动静态库，可执行程序，源程序]
d：目录文件
c: 字符设备文件 ：键盘与显示器
b: 块设备文件   ：块设备，block，磁盘
p：管道文件     ：通信
l：链接文件     ：软连接 link

s：网络socke文件

#### 三个 rw-rw-r--

wx wx ：拥有者 所属组 
0 Apr 29 22:01 wx.txt ： 大小  日期  文件名
-rw-rw-r-- ： 

rw-  rw-  r-- ： 拥有者  所属组  其他人
r(是否具有读)w(是否具有写)-(是否具有可执行) ：读、写、执行
r是-否   
w是-否 
x是-否

### 修改权限

#### 给指定人改权限

给u拥有者 g所属组 o其他人 +权限

```c
chmod u+rwx,g+rwx,o+rwx file.txt  
```

#### 给所有人改权限：a

给a所有人+或减权限

```c
chmod a+rwx file.txt 
```

r读 w写 x执行
权限有两种：r是 -否 可以用10代替

#### 计算权限的数字

```
rw-rw-r-- ：110110100 ：8进制->664
```

110 110 100  对应的8进制就是664

所以改权限可以是

```
chmod 000 file.txt
```

7 rwx
6 rw-
5 r-x
4 r--
3 -wx
2 -w-
1 --x

#### 修改权限代码

```
chmod u+x,g+x,o+x file.txt

```



### 修改 拥有者 所属组

把文件拥有者给root  文件给别人要征求其他人

但是sudo不用因为sudo是root，root是超级用户

```
sudo chown root file.txt  
```

把文件所属组给root 

```
 sudo chgrp root file.txt    
```

 如果文件是我的 修改组不需要sudo

```
chgrp wx file.txt         
```

改拥有者和所属组

```
sudo chown root:root file.txt
```

### 权限对目录的作用
rwx  读写执行
rw-  只能看目录里的文件名，也可以写进去 ，cd 进不去 也看不到文件信息
-wx  能进去 ，能写，看不到里面的东西
### 默认权限
普通文件，起始权限（666）
目录文件，起始权限（777）

但是这里是664和775 为什么？
```c
-rw-rw-r-- 1 wx wx    0 Apr 30 23:14 file.c
drwxrwxr-x 2 wx wx 4096 Apr 30 23:14 test
因为
[wx@VM-16-12-centos lesson4]$ umask
0002 权限掩码
default = default & ~(mask)
权限计算是
文件：
110 110 110 文件起始权限
000 000 010 权限掩码
取反再与
110 110 110
111 111 101 &
------------
110 110 100
  6   6   4
目录：
111 111 111      目录起始权限
111 111 101 &    权限掩码取反
-----------
111 111 101
  7   7   5
所以默认权限是这样 ！！！
```
### 自定义默认权限 - 本次登录有效
umask 0333
[wx@VM-16-12-centos lesson4]$ umask 0333
[wx@VM-16-12-centos lesson4]$ umask
0333
### 粘滞位
chmod o+t dir :只能对目录设置，限制other -可读可写，可删自己的 不能删别人的
---x--x--t 1 wx wx 9 Apr 30 13:50 file.txt
### 临时文件
会放在 /tmp文件夹下                                           

### 更改用户

#### 身份切换

su

输入root密码

ctrl+d退回原来的用户

#### 重新登陆

su -

#### 切换身份

在root用户下

`su wx` 则会切换到wx用户，访问不了其他用户的文件了

