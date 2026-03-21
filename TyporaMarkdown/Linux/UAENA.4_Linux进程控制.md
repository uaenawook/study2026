# UAENA.4_Linux进程控制

## 创建进程

### fork函数初识

```c++
#include <unistd.h>
pid_t fork(void);
返回值：自进程中返回0，父进程返回子进程id，出错返回-1
```

> ![image-20220708211937371](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/imageimage-20220708211937371.png)

**创建进程是有成本的(时间 + 空间)**

## 进程终止

### 进程退出场景

- 代码运行完毕，结果正确
- 代码运行完毕，结果不正确
- 代码异常终止  



#### **代码运行完毕，结果正确**

为什么main都要return 0;？

退出码：

0 表示success(成功)

!0 表示failed()  不能确定，有多种可能

```c++
return 0;
```

#### **代码运行完毕，结果不正确**

`echo $?` 输出最近一次进程退出时的退出码

```c++
-rw-rw-r-- 1 wx wx   64 Sep 10 09:46 Makefile
-rwxrwxr-x 1 wx wx 8360 Sep 10 09:48 myproc
-rw-rw-r-- 1 wx wx   74 Sep 10 09:48 myproc.c
[wx@VM-16-12-centos lesson12]$ ./myproc 
hell uaena
[wx@VM-16-12-centos lesson12]$ echo $?
23 //第一次错误的退出码是myproc.c的
[wx@VM-16-12-centos lesson12]$ echo $?
0  //第二次是myproc.c的父进程的
```

`ls`的进程退出码，2是错误 0是正确

```c++
[wx@VM-16-12-centos lesson12]$ ls -a -b -c -e
ls: invalid option -- 'e'
Try 'ls --help' for more information.
[wx@VM-16-12-centos lesson12]$ echo $?
2
[wx@VM-16-12-centos lesson12]$ ls
Makefile  myproc  myproc.c
[wx@VM-16-12-centos lesson12]$ echo $?
0
```

错误码

```c++
0: Success						//
1: Operation not permitted
2: No such file or directory
3: No such process
4: Interrupted system call
5: Input/output error
6: No such device or address
7: Argument list too long
8: Exec format error
9: Bad file descriptor
10: No child processes
...
133: Memory page has hardware error
134: Unknown error 134				//不认识了
```

#### **代码异常终止**  

程序崩溃！ 退出码也变没有意义了！

### 终止进程函数

#### exit函数

<stdlib.h>

**a.退出**

1.main函数return代表退出，非main函数呢？ ->> 函数返回

2.任意位置 覅用exit(退出码) ，则代表终止进程，参数是退出码！

`exit(EXIT_SUCCESS)`;可以代替 `return 0`退出程序

**b.刷新缓冲区**

缓冲区：用户级缓冲区

```c++
//数据时暂时被保存在缓冲区中，
// ‘\n’会刷新缓冲区，没有‘\n’则不会直接显示
printf("hello world");
sleep(4);
//exit or main return 本身就会要求系统进行，缓冲区刷新，
//所以结束时可以看到“hello world”
exit(EXIT_SUCCESS);
//return 0;
```

#### _exit函数

3._exit 终止进程，强制终止进程，不要进行进程的后续收尾工作，比如刷新缓冲区

![image-20220910104534934](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/imageimage-20220910104534934.png)

**进程退出，OS层面做了什么呢？**

系统层面，少了一个今后才能：free PCB，free，mm_struct，free也变和各种映射关系，代码+数据申请的空间也要给释放掉！

## 进程等待

wait

### 是什么？

fork() 子进程在为父进程干工作，为帮助如今后才能完成某种任务

让父进程fork之后，需要等待wait/waitpid等待子进程退出

### 为什么？

1.通过获取子进程退出的信息，能够得知子进程执行结果

2.可以保证：时序问题，子进程先退出，父进程后退出

3.子进程 退出的时候会先进入僵尸状态，会造成内存泄漏的问题，需要通过父进程wait，释放孩子进程占用的资源

### 怎么办？



### waitpid方法

waitpid(id,NULL,0); 	//等待指定一个子进程

waitpid(-1,NULL,0);	//等待任意一个子进程，等价于wait

返回值是 子进程的ID
