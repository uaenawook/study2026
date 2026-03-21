## 安装yum 
yum list 显示应用
yum list | grep 'sl \ .x86_64' 搜索应用
yum -y install sl.x86.64  安装软件 -y直接安装
yum -y remove sl.x86_64 卸载 -y不询问直接干掉
**yum install -y man-pages.noarch**安装手册
**yum install -y epel-release.noarch**安装应用商店
**yum -y install lrzsz.x86_64** 安装Windows和Linux 互相传文件的应用
**sudo yum install glibc-static**安装c的静态库

epel  非官方，新的，不太稳定
Centos-Base.repo 官方的稳定的老的
1.yum工作需要联网
2.centos 只能有一个yum运行

## vim
输入：i 
会退至命令模式：esc
退出：shift + ：
        退出：q
        保存：w
        退出保存：wq
        强制：！

### 命令模式 - 核心
光标移动：h(左) j(下) k(上) l(右) 
光标位置锚点：shift+^(行首) shift+$(行尾)
定位起始行：gg 
结束行：shift+g   或大写G
指定行：n+shift+g
快速移动光标：b/w
复制一行：yy  向下复制好几行：n+yy 
粘贴：p   粘贴好几行：n+p
删除：dd
剪切：dd+p
撤回：u
反撤回：ctrl+r
快速大小写切换：shift + ~
删除光标后字符：x  /  n+x
删除光标前字符：shift + x  或大写X
替换一个光标所在字符：r  / n+r   或shift+r /R  多个内容替换
### 底行模式
shift +：
行号显示/关闭：set nu / set nonu
打开分屏：vs name.c
分屏切换：ctrl+ww
退出：q
保存：w
退出保存：wq
强制：!（w!,q!,wq!）
### 插入模式
a:光标向后移动一下
i:光标不动
o:另起一行
### vim配置
配置只在当前用户生效

## gcc
gcc -E test.c -o test.i 预处理->test.i

gcc -S test.i -o test.s 编译->test.s

gcc -c test.s -o test.o 汇编：转2进制->test.o

gcc test.o -o test 链接：形成可执行文件->a.out/test

## gcc的编译
ldd test查看test使用的库
&emsp;/lib64/libc.so.6 c.so证明是c的动态库
file test 查看gcc用的是什么链接
dynamically linked (uses shared libs)动态链接（使用共享库） 

##### 静态链接
.a 静态链接 体积大   可移植 库一直在
.os动态链接 体积小   但是库没了 程序就没了
[wx@VM-16-12-centos lesson6]$ gcc test.c -o test_static -static
[wx@VM-16-12-centos lesson6]$ ll
total 860
-rwxrwxr-x 1 wx wx   8408 May  7 21:29 test
-rw-rw-r-- 1 wx wx    257 May  5 11:18 test.c
-rwxrwxr-x 1 wx wx 861384 May  7 21:40 test_static
[wx@VM-16-12-centos lesson6]$ ./test
hello bit!
hello bit!
NUM=100
[wx@VM-16-12-centos lesson6]$ ./test_static 
hello bit!
hello bit!
NUM=100
[wx@VM-16-12-centos lesson6]$ 

## g++
g++ -v 查看g++安装情况
## gdb
默认是 release
gcc test.c -o test_debug -g  加debug
gdb a.out 
readelf -S test 段构成查看
gcc test1.c -o test1 -std=c99 定义并初始化int = i 是c99的

run 执行不调试
list 显示代码   l1 从第一行显示 +l显示剩余的
breakpoint 打断点 b 16 在16行打断点   info 查看断点
s 逐语句   n逐过程

## make / makefile  命令/文件
```c
  1 mycode:mycode.c
  2     gcc -o $@ $^
  3 .PHONY:clean
  4 clean:
  5     rm -f mycode 
```
自上向下扫描，  可执行文件 mycode 如果没有，则调用mycode.c，然后执行gcc -o $@(mycode目标文件) $^(mycode.c依赖文件) 
```c
mycode:mycode.o
    gcc -o mycode mycode.o
mycode.o:mycode.s
    gcc -c mycode.s -o mycode.o
mycode.s:mycode.i
    gcc -S mycode.i -o mycode.s
mycode.i:mycode.c
    gcc -E mycode.c -o mycode.i
.PHONY:clean
clean:
    rm -f mycode mycode.i mycode.s mycode.o
```
上述代码自动生成iso所有过程的文件
## Linux第一个小程序－进度条
- **回车换行概念**
**回车**：回到当前行的最开始
**换行**：列不变，新起一行
- **printf**
```c
  1 #include <stdio.h>
  2 #include <unistd.h>
  3 int main()
  4 {
  5 
  6   // printf("hello bit!\n");
  7   printf("hello bit!");                                                            
  8   sleep(5);
  9   return 0;
 10 }
 
 当程序带 \n 则先显示 hello bit!  再暂停5秒结束
 当程序不带 \n 则先暂停5秒   再显示hello bit!
 
 程序是按顺序执行的， printf已经执行但是没显示
 因为字符串暂时被 放在缓冲区保存起来没刷新   当5秒后程序结束 才刷新显示
 
 有\n直接显示 是因为，显示器设备的刷新策略是 \n 就刷新
 
```
- **c程序默认打开三个输入输出流**
**键&emsp;盘**：stdin
**显示器**：stdout
**显示器**：stderr

**让上述程序 直接刷新 不加\n**
**fflush(stdout)**
```c
  1 #include <stdio.h>
  2 #include <unistd.h>
  3 int main()
  4 {
  5 
  6   // printf("hello bit!\n");
  7   printf("hello bit!");
  8   fflush(stdout);                                                      
  9   sleep(5);
 10 
 11   return 0;
 12 }
```
**进度条程序**
```c
  1 #include <stdio.h>
  2 #include <string.h>
  3 #include <unistd.h>
  4 
  5 int main()
  6 {
  7 #define NUM 100
  8   char bar[NUM+1];
  9   memset(bar,'\0',sizeof(bar));  //初始化成\0
 10 
 11   const char *lable = "|/-\\";//定义执行状态的字符串
 12   int i = 0;
 13   while(i<=100)//循环执行进度条
 14   {
 15     //printf("\033[31m[%-100s][%3d%%] %c\r",bar,i,lable[i%4]);
 16     printf("[%-100s][%3d%%] %c\r",bar,i,lable[i%4]);
 //[%100s]空出100个字符的位置  打印字符串
 //[%3d%%]空出3个位置 打印进度百分比  %% 是格式转换
 //%c打印进度  \r 回车
 17 
 18     fflush(stdout);  //立即刷新到屏幕
 19     bar[i] = '#'; //让bar不断变化
 20     //bar[i+1] = '>';
 21     i++;
 22     usleep(50000);   //usleep 毫秒格式
 23   }
 24   printf("\n");
 25 }
```

## git
**查询安装git**：git --version
**显示**：git version 1.8.3.1
**安装git**：yum install git
### 一、在云端创建仓库
### 二、拷贝远程仓库到本地
git clone https:
输入用户名&密码
### 三、上传代码到云端
#### 1.add
**git add 路径/文件**
```c
git add Class_102_linux/lesson1
```
**可以看到new上去的文件**
```c
git status 
```
```c
[wx@VM-16-12-centos GiteeLinux]$ git status
# On branch master
# Changes to be committed://要提交的更改
#   (use "git reset HEAD <file>..." to unstage)//回滚命令
#
#	new file:   Class_102_linux/lesson1/.test1.c.swp
#	new file:   Class_102_linux/lesson1/test1.c
#	new file:   Class_102_linux/lesson1/test2.c
#
# Untracked files://未跟踪文件
#   (use "git add <file>..." to include in what will be committed)
#
#	Class_102_linux/lesson2/
#	Class_102_linux/lesson3/
#	Class_102_linux/lesson4/
#	Class_102_linux/lesson5/
#	Class_102_linux/lesson6/
#	Class_102_linux/lesson7/
```
#### 2.commit
```c
git commit -m "第一天认识linux"
```
**出现错误后**,意思是git不知道你是谁 ，执行Run下面的两条命令
**邮箱**：gitee绑定的邮箱
**name**：giett的名字    不是@后面的账号
```c
*** Please tell me who you are.

Run

  git config --global user.email "you@example.com"
  git config --global user.name "Your Name"

to set your account's default identity.
Omit --global to set the identity only in this repository.
```
**执行完 再次执行 commit**
**必须写日志**
#### 3.push
```c
git push
push 要在最里层文件夹中
输入 账号(手机号)密码上传完成
```
### 四、查看日志
```c
git log
```

### 批量注释
ctrl + v   j选中后   大写i   //  esc
ctrl + v   l选中后   d

 