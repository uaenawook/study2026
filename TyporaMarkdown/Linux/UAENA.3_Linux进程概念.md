# BIT.3_Linux进程概念

## 冯诺依曼体系结构

**1.输入设备**(外设)：(毫秒，秒)键盘、磁盘、网卡、显卡、话筒、摄像头等
**2.输出设备**(外设)：(毫秒，秒)显示器、磁盘、网卡、显卡、音响等
**3.存储器(内存)**：(微妙) 这里 计算机的速度由内存决定
**4.运算器&控制器(CPU)**：(纳秒)
**木桶效应**：木桶能盛多少水由最短的板子决定

```c
输入设备  -input->  存储器  -output->  输出设备

```

> ![image-20220705160238245](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/imageimage-20220705160238245.png)

**任何外设，在数据层面，基本有限和内存打交道！ CPU，在数据层面上，也直接和内存打交道**
解释QQ聊天
我：键盘输入(外设)-> 内存接收(qq软件控制) -> CPU处理(加密或添加网络传输条件)->内存接收->网卡输出-> {网络} -> 
朋友： {网络}-> 网卡接收 -> 输入给内存 -> CPU处理 -> 内存接收 -> 输出到显示器(外设)

## 操作系统

**启动操作系统**才有意义 ：将软件数据与代码，加载到内存
### 1.操作系统OS 是什么？
> 是一款软件，专门针对于软硬件资源进行管理工作的软件

### 2.操作系统OS 为什么？
> 对下(方式)：管理好软硬件资源。 对上(目的)：给用户提供稳定的，高效的，安全的运行环境。

### 3.操作系统OS 怎么办？
> 管理！ ->  决策 、执行 
> 对被管理对象：先描述 再组织
### 4.如何管理进程？
> 先描述：描述进程的结构体 - PCB进程控制块 (描述进程的结构体) 
> 再组织：



## OS组成

(Operator System)

用户&emsp;&emsp;&emsp;&emsp;：操作指令、开发操作、操作管理
用户接口&emsp;&emsp;：shell外壳、lib库、不分指令
系统调用接口：
操作系统&emsp;&emsp;：内存管理、进程管理、文件管理、驱动管理
驱动程序&emsp;&emsp;：网卡驱动、硬盘驱动、其他驱动
底层硬件&emsp;&emsp;：网卡、硬盘、其他

## 进程概念
书上：加载到内存的程序，叫进程

**内核关于进程的相关数据结构+当前进程的代码和数据**

## 描述进程-PCB

### 为什么要有PCB ？因为要管理 
系统中存在大量的进程！
操作系统要管理进程！：杀掉进程
如何管理进程？：先描述，再组织

先描述：任何进程在形成之时，操作系要为该进程创建`PCB` `进程控制块` -> `struct PCB{//进程的所有属性}`



### OS上 什么是PCB ？ 就是一个结构体类型
在linux系统中 ，PCB -> struct task_struct{//进程的所有的属性}
总称是PCB  在linux上叫 struct task_struct
媒婆是总称 ，王婆是媒婆中的一个

### task_struct里面有什么属性字段？
##### 查看进程
```c
显示进程ps axj | grep "myproc"
18857 20701 20701 18857 pts/0    20701 S+    1001   0:00 ./myproc
显示头部名称+进程ps ajx | head -1 && ps axj | grep "myproc"
 PPID   PID  PGID   SID TTY      TPGID STAT   UID   TIME COMMAND
18857 20701 20701 18857 pts/0    20701 S+    1001   0:00 ./myproc
```
曾经我们所有的启动程序需的过程，本质都是在系统上面创建进程

### 进程 VS 程序
程序是：文件 xxx.exe(可执行文件)
进程 = 程序(文件内容) + 与进程相关的数据结构(PCB(sask_struct{})) pcb由系统自动创建

### task_struct内容分类
#### 一、标识符：
##### 获取进程
printf("hello bit!:pid: %d\n",getpid()); 
##### 获取父进程
printf("hello bit!:pid: %d ，ppid:%d\n",getpid(),getppid()); 
```c
hello bit!:pid: 3929,ppid:18857

[wx@VM-16-12-centos lesson8]$ ps ajx | grep 18857
18857  3929  3929 18857 pts/0     3929 S+    1001   0:00 ./myproc
20942  4441  4440 20942 pts/1     4440 S+    1001   0:00 grep --color=auto 18857
18856 18857 18857 18857 pts/0     3929 Ss    1001   0:00 -bash

ppid 是-bash
```
**在命令行上运行的命令，基本上父进程都是bash**

##### 干掉进程
kill -9 2543(pid)
#### 二、状态：
##### return 0; 是什么？
是进程退出码，返回给操作系统后  让父进程拿到
`echo $?` 可以查看最近一次命令的退出码

#### 三、优先级：
决定先后的问题 vs 权限
权限：能&不能
优先级：先&后  (已经能了)
#### 四、程序计数器
指向 程序中下一条指令的地址
(函数栈帧)
#### 五、内存指针
可以通过内存指针  找到进程的代码和数据
#### 六、上下文数据
固定每个进程单词运行的时间片：每次运行10ms
完成10ms  之后从在`队列中`新排队
这样用户就感觉 多个进程在同时运行，本质是通过cpu的快速切换完成的
**进程在运行期间是有切换，进程可能存在大量的临时数据，->这哪是在CPU的寄存器中保存**
==但是CPU只有一套`寄存器`==

**当兵：保护上下文**：走的时候要告诉学校，我先去当兵了，帮我把学籍保留一下
**上学：恢复上下文**：回来的时候告诉学校，我回来了，帮我把学籍恢复 我要继续学习。
为了让你做其他事，不耽误当前，硬切当你想回来继续学时，可以接着你之前的学习内容继续学习
##### A的保护上下文
保护上下文：A-PCB 保存好自己的临时数据 再去排队
回来的时候 ：先恢复临时数据 

##### 上下文信息
进程执行时所形成的处理器 寄存器形成的 与进程墙相关的临时数据 就叫做`**上下文信息**`

#### 七、I/O状态信息
进程的输入输出信息
#### 八、记账信息
包括 处理器时间总和，使用的时钟数总和，时间限制，记账号等
进程被调度的记账信息   进程使用了多少秒 用来分配使用进程
#### 九、其他信息

##### 查看进程
```c
[wx@VM-16-12-centos lesson8]$ ls /proc
1      17859  23616  2729   30110  644        consoles     mounts
10     18     24     273    30165  646        cpuinfo      mtrr
10030  18189  24209  2731   30168  647        crypto       net
106    18423  24466  2733   30853  65         devices      pagetypeinfo
11     18680  24594  27566  31170  651        diskstats    partitions
1191   18720  24702  27575  35     653        dma          sched_debug
12     18824  25     27900  36     663        driver       schedstat
1212   18856  25041  27971  37     7          execdomains  scsi
1240   18857  25519  28     38     8          fb           self
1269   18870  25659  280    387    8867       filesystems  slabinfo
12718  18885  257    28358  3919   8868       fs           softirqs
12881  18908  26     28362  4      8869       interrupts   stat
13     19     26059  28363  408    8870       iomem        swaps
14     1912   262    28366  409    8872       ioports      sys
1466   2      263    28368  46     8874       irq          sysrq-trigger
1467   20     264    28868  48     8876       kallsyms     sysvipc
15604  208    265    28900  49     9          kcore        timer_list
15607  20939  26774  28901  51     9088       keys         timer_stats
15614  20941  269    28988  515    9089       key-users    tty
15619  20942  26932  29     52     9090       kmsg         uptime
15627  20957  26951  291    5410   923        kpagecount   version
15628  20973  26957  292    5413   987        kpageflags   vmallocinfo
15634  20992  26958  29923  5415   989        loadavg      vmstat
15696  21     27     30089  5417   acpi       locks        zoneinfo
1589   21298  27004  30096  5419   buddyinfo  mdstat
16     22     2724   30097  5421   bus        meminfo
1676   22882  2725   30104  566    cgroups    misc
1764   23     2727   30105  6      cmdline    modules
[wx@VM-16-12-centos lesson8]$ ls -d /proc -l
dr-xr-xr-x 175 root root 0 Apr 28 21:57 /proc
[wx@VM-16-12-centos lesson8]$ ls /proc/26932
attr             cwd       map_files   oom_adj        schedstat  task
autogroup        environ   maps        oom_score      sessionid  timers
auxv             exe       mem         oom_score_adj  setgroups  uid_map
cgroup           fd        mountinfo   pagemap        smaps      wchan
clear_refs       fdinfo    mounts      patch_state    stack
cmdline          gid_map   mountstats  personality    stat
comm             io        net         projid_map     statm
coredump_filter  limits    ns          root           status
cpuset           loginuid  numa_maps   sched          syscall
[wx@VM-16-12-centos lesson8]$ ls /proc/26932 -al
total 0
dr-xr-xr-x   9 wx   wx   0 Jun  8 19:31 .
dr-xr-xr-x 174 root root 0 Apr 28 21:57 ..
dr-xr-xr-x   2 wx   wx   0 Jun  8 19:33 attr
-rw-r--r--   1 wx   wx   0 Jun  8 19:33 autogroup
-r--------   1 wx   wx   0 Jun  8 19:33 auxv
-r--r--r--   1 wx   wx   0 Jun  8 19:33 cgroup
--w-------   1 wx   wx   0 Jun  8 19:33 clear_refs
-r--r--r--   1 wx   wx   0 Jun  8 19:31 cmdline
-rw-r--r--   1 wx   wx   0 Jun  8 19:32 comm
-rw-r--r--   1 wx   wx   0 Jun  8 19:33 coredump_filter
-r--r--r--   1 wx   wx   0 Jun  8 19:33 cpuset
lrwxrwxrwx   1 wx   wx   0 Jun  8 19:31 cwd -> /home/wx/Class_102_linux/lesson8
-r--------   1 wx   wx   0 Jun  8 19:33 environ
lrwxrwxrwx   1 wx   wx   0 Jun  8 19:31 exe -> /home/wx/Class_102_linux/lesson8/myproc
dr-x------   2 wx   wx   0 Jun  8 19:31 fd
dr-x------   2 wx   wx   0 Jun  8 19:33 fdinfo
-rw-r--r--   1 wx   wx   0 Jun  8 19:33 gid_map
-r--------   1 wx   wx   0 Jun  8 19:33 io
-r--r--r--   1 wx   wx   0 Jun  8 19:33 limits
-rw-r--r--   1 wx   wx   0 Jun  8 19:33 loginuid
dr-x------   2 wx   wx   0 Jun  8 19:33 map_files
-r--r--r--   1 wx   wx   0 Jun  8 19:33 maps
-rw-------   1 wx   wx   0 Jun  8 19:33 mem
-r--r--r--   1 wx   wx   0 Jun  8 19:33 mountinfo
-r--r--r--   1 wx   wx   0 Jun  8 19:33 mounts
-r--------   1 wx   wx   0 Jun  8 19:33 mountstats
dr-xr-xr-x   5 wx   wx   0 Jun  8 19:33 net
dr-x--x--x   2 wx   wx   0 Jun  8 19:33 ns
-r--r--r--   1 wx   wx   0 Jun  8 19:33 numa_maps
-rw-r--r--   1 wx   wx   0 Jun  8 19:33 oom_adj
-r--r--r--   1 wx   wx   0 Jun  8 19:33 oom_score
-rw-r--r--   1 wx   wx   0 Jun  8 19:33 oom_score_adj
-r--r--r--   1 wx   wx   0 Jun  8 19:33 pagemap
-r--------   1 wx   wx   0 Jun  8 19:33 patch_state
-r--r--r--   1 wx   wx   0 Jun  8 19:33 personality
-rw-r--r--   1 wx   wx   0 Jun  8 19:33 projid_map
lrwxrwxrwx   1 wx   wx   0 Jun  8 19:31 root -> /
-rw-r--r--   1 wx   wx   0 Jun  8 19:33 sched
-r--r--r--   1 wx   wx   0 Jun  8 19:33 schedstat
-r--r--r--   1 wx   wx   0 Jun  8 19:33 sessionid
-rw-r--r--   1 wx   wx   0 Jun  8 19:33 setgroups
-r--r--r--   1 wx   wx   0 Jun  8 19:33 smaps
-r--r--r--   1 wx   wx   0 Jun  8 19:33 stack
-r--r--r--   1 wx   wx   0 Jun  8 19:31 stat
-r--r--r--   1 wx   wx   0 Jun  8 19:32 statm
-r--r--r--   1 wx   wx   0 Jun  8 19:31 status
-r--r--r--   1 wx   wx   0 Jun  8 19:33 syscall
dr-xr-xr-x   3 wx   wx   0 Jun  8 19:33 task
-r--r--r--   1 wx   wx   0 Jun  8 19:33 timers
-rw-r--r--   1 wx   wx   0 Jun  8 19:33 uid_map
-r--r--r--   1 wx   wx   0 Jun  8 19:33 wchan
[wx@VM-16-12-centos lesson8]$ 
```
```c
lrwxrwxrwx   1 wx   wx   0 Jun  8 19:31 cwd -> /home/wx/Class_102_linux/lesson8
-r--------   1 wx   wx   0 Jun  8 19:33 environ
lrwxrwxrwx   1 wx   wx   0 Jun  8 19:31 exe -> /home/wx/Class_102_linux/lesson8/myproc

```
exe 程序文件
cwd 当前工作目录



## vim指令

### vim报错：E325: ATTENTION

![QQ截图20220616231248](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/image/202206170058633.jpg)

### 1. 不退出vim查看man手册

```c++
!man fork
```

### 2. 不退出vim 编译运行代码

```
!make
./myproc
```

## 理解fork创建子进程

fork是创建子进程的函数

### 1. 理解

fork本身是创建进程 -> 系统多了一个进程 -> 子进程用父进程的代码，数据时写时拷贝的

**因为进程之间不会会想影响**

**不管是fork前后的代码 fork都汇继承**

### 2. fork之后，父子谁先运行？？ 

不确定，调度器决定

### 3.fork的返回值



## Linux进程状态

### 1. 进程的状态信息在哪里？

`task_struct(PCB)`

### 2. 进程状态的意义：

方便OS 快速判断进程，完成特定的功能，比如调度，本只是一种分类！

### 3. 具体状态：

进程，在运行的时候，有可能因为运行需要，可以会在不同的队列里

在不同的队列里，所处的状态是不一样的！

例如：

​			运行时在`run_queue`

​			等待时在`wait_queue`

> ​			![image-20220617134756856](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/image/202206171347909.png)

- #### R(running)：运行状态

  一定占有`CPU`吗？ 不一定！！！ 只要在`PCB`中的队列中，都是`R`状态

  

- #### S、D:等待状态

  当我们完成某种任务的时候，任务条件不具备，需要进程进行某种等待，`S`、`D`

  这些进程也存在 等待`wait_queue`队列中

  - ##### S(sleeping)：休眠睡眠

    可中断睡眠

  - ##### D(disk sleep)：深度睡眠

    进程处于D状态，不可被杀掉，OS也不行
  
    - ###### 如何结束
  
      进程运行完成、重启OS
  
  - ##### 程序为什么会出现卡死?，卡死后`Windows`提示是否等待或关闭是为什么？
  
    > >  因为：程序可能在等待某种资源，例如网易云音乐正在播放音乐，拔掉网线后，网易云音乐进程一直在等待网卡中的数据，由于没网，进程处于等待状态，而进程等待时不能能一直占用`CPU`，所以出现了卡死的现象，其实就是进程在`S`、`D`（等待）状态！
    >>
  
  - ##### **结论：**
  
     		我们把，从运行状态的`task_struct(run_queue)`,放到等待队列中，就叫做`挂起等待`(阻塞)
    		从等待队列，放到运行队列，被`CPU`调度就叫做`唤醒程序`

- #### T(stopped)：暂停

- #### t(tracing stop)：追踪状态(暂停) 

  打断点就是最终状态，代码被暂停

- #### X(dead)：死亡状态(基本查不到 很少见 瞬间就没了)

  回收进程资源 = 进程相关的内核数据结构 + 你的代码和数据

- #### Z(zombie)：僵尸状态(先进入Z状态 -> 由Z转为X)

  - ##### 为什么要有僵尸状态？

    为了辨别退出死亡原因 -> 进程退出的信息 -> 数据 -> task_struct

### 4. 验证状态：

#### R

> 死循环运行时 ，进程就是`R`运行状态   没有`IO`就不会等待所以 一直`R`

> ![image-20220617115928693](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/image/202206171159763.png)

#### S

> 当程序在死循环打印时，进程是s状态 ，也会有R状态

> ![image-20220617120457864](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/image/202206171204923.png)

##### 为什么呢？

> ![image-20220617121122827](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/image/202206171211861.png)

因为`cout`是在进行打印，显示器和外设都很慢，`IO`等待外设就绪是需要花费时间的！所以基本都是 因为外设慢 (在cpu看来) ，所以等待外设就绪 就是`S`状态  但是外设不一定都在等待，也有可能在运行`R`！

#### T

可以看到第一次查询时`S`后有`+`号  意思是在前台运行

`fg`可以将后台进程 转移到前台

暂停 STOP(暂停后`T`后面没有`+`号)

> ![image-20220617122228107](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/image/202206171222182.png)

继续CONT(此时`S`后面的`+`号也没有了，这时进程就变成了后天运行，左面的死循环用`ctrl+c`不能结束了)

> ![image-20220617122430501](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/image/202206171224578.png)

干掉进程KILL(此时后台进程只能用命令杀死)

> ![image-20220617122854666](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/image/202206171228736.png)

#### 前台运行

```c++
./myproc
```

前台运行时，可以用`ctrl+c`结束进程，但是不能输入其他命令了

#### 后台运行

```c++
./myproc &
```

后天运行是，可以继续输入命令，但是`ctrl+c`不能杀掉进程，可以选择`kill`杀掉进程

#### 杀掉进程

```c++
kill -9 pid
```

```c
killall 进程名称
```



#### 查看pid

```c++
ps axj | grep myproc 
```

第二列是pid

```
显示头部名称+进程ps ajx | head -1 && ps axj | grep "myproc"
 PPID   PID  PGID   SID TTY      TPGID STAT   UID   TIME COMMAND
18857 20701 20701 18857 pts/0    20701 S+    1001   0:00 ./myproc
```

- #### Z

  如果没有人`检测或者回收`进程(父进程)，该进程进入`Z`状态，

  如何检测和回收？ 后面讲

  如何看到这种状态？

  - 检测状态代码

    ```c++
    [wx@VM-16-12-centos lesson9]$ while :; do ps axj | head -1 && ps ajx | grep myproc | grep -v grep; sleep 1; echo "#####################"; done
     PPID   PID  PGID   SID TTY      TPGID STAT   UID   TIME COMMAND
    #####################
    ```

  - 查看`Z`状态

    让父子同时运行 ，杀掉子进程，父进程进行`sleep`，此时子进程状态就是`Z`

    > ![image-20220617131108909](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/image/202206171311992.png)

  - 进程代码

    ```c++
    #include <iostream>
    #include <unistd.h>
    
    using namespace std;
    int main()
    {
        pid_t id = fork();
        if(id ==0 ) {
          //child
          while(true){
            cout << "I am chile,running!"<<endl;
            sleep(2);
          }
        }
        else{
          //parent
          cout << "father do nothing!" << endl;
          sleep(50);
        }
    }
    ```

  - 结束命令

    ```c++
    kill -9 pid
    ```

### 5. 僵尸进程：
  - 进程演示

    父子同时运行 ，杀掉子进程，父进程进行`sleep`，此时子进程状态就是`Z`，子进程是`僵尸进程`

    > ![image-20220617131108909](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/image/202206171311992.png)

  - 进程代码

    ```c++
    #include <iostream>
    #include <unistd.h>
    
    using namespace std;
    int main()
    {
        pid_t id = fork();
        if(id ==0 ) {
          //child
          while(true){
            cout << "I am chile,running!"<<endl;
            sleep(2);
          }
        }
        else{
          //parent
          cout << "father do nothing!" << endl;
          sleep(50);
        }
    }
### 6. 孤儿进程：

- 进程演示

  父子同时运行，父亲挂了，子还活着，此时子是`孤儿进程`

  由1号进程领养，1号是操作系统`OS`

> ![image-20220617132851510](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/image/202206171331411.png)

- 进程代码

    ```c++
    #include <iostream>
    #include <unistd.h>
    #include <cstdlib>
    using namespace std;
    int main()
    {
        pid_t id = fork();
        if(id ==0 ) {
          //child
          while(true){
            cout << "I am chile,running!"<<endl;
            sleep(2);
          }
        }
        else{
          //parent
          cout << "father do nothing!" << endl;
          sleep(10);
          exit(1);
        }
    }
    ```

## 进程优先级

### 为什么会有优先级？

1. 资源太少，所以优先级是分配资源的一种方式。

### PRI and NI

linux中优先级数据，**值越小 级别越高**

- **PRI** 优先级 ，初始值80

- **NI** （nice）修正数据  **取值(-20 ~19)**  40个级别
- **PRI+NI = 修改优先级**，由NI的加减控制PRI的优先级
- PRI(new) = PRI(old) + nice

> ![image-20220624104724036](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/image/202206241047088.png)

#### nice值为什么是相对比较小的范围呢？

优先级在怎么设置，也只能是一种相对的优先级，不能出现绝对的优先级，否则会出现很严重的进程“**饥饿问题**”(进程长时间的不到资源)

调度器：较为均衡的让每个进城享受到CPU的资源

### top

修改优先级

> ![image-20220624110217295](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/image/202206241102341.png)

top 显示优先级，r 开始输入，输入pid回车，输入要修改的NI 回车

> ![image-20220624110254850](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/image/202206241102892.png)

PRI每次都是80 NI调整 也是从80开始 加或减

## 其它概念

| 竞争性: | 系统进程数目众多，而CPU资源只有少量，甚至1个，所以进程之间是具有竞争属性的。为了高效完成任务，更合理竞争相关资源，便具有了优先级 |
| ------- | ------------------------------------------------------------ |
| 独立性: | 多进程运行，需要独享各种资源，多进程运行期间互不干扰         |
| 并行:   | 多个进程在多个CPU下分别，同时进行运行，这称之为并行          |
| 并发:   | 多个进程在一个CPU下采用进程切换的方式，在一段时间之内，让多个进程都得以推进，称之为并发 |

## 环境变量

### 环境变量概念(重点)

- 命令，程序，工具...本质都是可执行**文件**

- 我们运行程序 为什么要加 ./ 呢？是为了帮助系统确认程序在哪！

- 那为什么系统命令不用带路径呢？ 因为环境变量 -> PATH

- 查看 环境变量 echo $PATH

  > <img src="https://picgo-1311604203.cos.ap-beijing.myqcloud.com/image/202206241139263.png"/>

  以 `:`作为分隔符 进行查找命令的路径

- 可以将自己的./ 拷贝到 PATH里

### 环境变量组成

```c++
echo $PATH
```

> ![image-20220624115107891](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/image/202206241151935.png)

可以看到此时修改后，系统里的没了，ls也不好用了 ，重新打开xshell就好了

```c++
env 查看所有变量
```

包括，pwd，home，编码，id，用户等等等等！

> ![image-20220624122356022](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/image/202206241223100.png)

### 修改环境变量

```c++
export PATH=$PATH:/home/
```

> <img src="https://picgo-1311604203.cos.ap-beijing.myqcloud.com/image/202206241159930.png" alt="image-20220624115939884" style="zoom:100%;" />

语言上定义变量本质是在内存中开辟空间(有名字)

不要去质疑OS开辟空间的能力！！

环境变量本质是 OS在内存/磁盘文件中**开辟的空间**，用来保存系统相关的属性！

**变量名(a) + 变量内容(10)**

### 获取环境变量(了解)

**系统上还存在一中变量，是与本次登录(session)有关的变量，只在本次登录有效（本地变量）**

1. echo显示某个环境变量值

2. export设置一个新的环境变量/**将本地变量导成环境变量**
2. env: 显示所有环境变量
2. unset: 清除环境变量
2. set: 显示本地定义的shell变量和环境变量  

> 具体操作

```c++
[wx@VM-16-12-centos lesson10]$ mycal=12345
[wx@VM-16-12-centos lesson10]$ set | grep mycal
mycal=12345
[wx@VM-16-12-centos lesson10]$ env | grep mycal
[wx@VM-16-12-centos lesson10]$ export mycal
[wx@VM-16-12-centos lesson10]$ env | grep mycal
mycal=12345
[wx@VM-16-12-centos lesson10]$ unset mycal
[wx@VM-16-12-centos lesson10]$ env | grep mycal
[wx@VM-16-12-centos lesson10]$ 
```

> ![image-20220624124618825](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/image/202206241246871.png)

#### argc argv

##### argc

代表argv[]的字符串的个数

##### argv[]

指针数组：一张表 

存放环境变量的 参数 

例如：ls  -a  -b  -c  -d  中的-a

argv的0号下标是可执行程序 从[1]开始是-a





**指令有很多选项，来完成同一个命令的不同子功能**

选项底层使用的就是我们的命令行参数！！

```c++
int main(int argc,char* argv[])
{
  if(argc != 2) {
    printf("Usage:%s -[a|h]\n",argv[0]);
    return 1;
  }
  //定制多样的命令，显示不同的内容
  if(strcmp(argv[1],"-h") == 0)
  {
    printf("hello linux\n");
  }
  else if(strcmp(argv[1],"-a") == 0)
  {
    printf("hello all!\n");
  }
  else{
    printf("hello world!\n");
  }
}
```



> ![image-20220624234236344](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/image/202206242342758.png)

#### 系统：env:char*

系统层面获取环境变量

```c++
int main(int argc,char* argv[],char* env[])
{
  for(int i = 0;env[i];++i)
  {
    printf("%d -> %s\n",i,env[i]);
  }
}
```



> ![image-20220625001448018](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/image/202206250014095.png)

#### C语言：environ:char**

C语言方式获取环境变量

与上述代码效果相同，因为`environ`是二级指针，可以指向`env`

```c++
int main()
{
  extern char **environ;
    for(int i =0;environ[i];i++){

    printf("%d -> %s\n",i,environ[i]);
    }
}
```

#### 函数没有参数 ，系统可以传参吗？可以

#### 函数：getenv(常用)

函数获取环境变量

<stdlib.h>

getenv 接收参数后在系统变量中查找对应字符串，返回后面的路径

例如：strstr(target,"PATH=");(查找环境变量，getenv实现的方式)

```c++
int main()
{
      printf("PATH:%s\n",getenv("PATH"));
      printf("HOME:%s\n",getenv("HOME"));
}
```

> ![image-20220625003213656](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/image/202206250032694.png)

**命令行上启动的进程，父进程都是`bash`**

导出环境变量
export MYENV="hello world 

环境变量具有“全局属性 ” 本质：**环境变量可以被子进程继承下去**

export是将变量 添加到环境变量表里

## 安装软件

本质上就是 将这个软件**拷贝到系统环境变量**的特定命令路径下，安装的过程是拷贝的过程

## 程序地址空间

程序地址空间图

><img src="https://picgo-1311604203.cos.ap-beijing.myqcloud.com/imageimage-20220705160334824.png" alt="image-20220705160334824" style="zoom: 67%;" /><img src="https://picgo-1311604203.cos.ap-beijing.myqcloud.com/imageimage-20220708193703082.png" alt="image-20220708193703082" style="zoom: 80%;" />

> 

程序地址空间 - 不是内存

### 程序地址空间是什么？

**是进程虚拟地址空间**



> ![image-20220705102709451](C:\Users\uaena\AppData\Roaming\Typora\typora-user-images\image-20220705102709451.png)

堆区向上增长

> ![image-20220705103225756](C:\Users\uaena\AppData\Roaming\Typora\typora-user-images\image-20220705103225756.png)

> ![image-20220705154309520](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/imageimage-20220705154309520.png)

#### 虚拟地址：父子同地址，不同数据

子进程 更改数据，父进程数据没变，是写时拷贝，但是 这两个数据的地址经验是一样的

如果C/C++打印出来的地址是物理内存的地址，可能出现这种情况吗？ 绝对不可能！

所以，这个我们是用的地址，绝对不能是物理地址！是虚拟地址！

> ![image-20220705155104855](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/imageimage-20220705155104855.png)

> ![image-20220708203019166](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/imageimage-20220708203019166.png)

共享代码 不共享数据，就是数据分开映射，代码映射到一起

> ![image-20220708203228572](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/imageimage-20220708203228572.png)

```c++
char* str = "hello world";
char* p = "hello world";

cout << p << str ;的值是一样的 ，地址是一样的，
```

也就是两个指针 映射到了同一块物理空间！

### 进程地址空间：

在内核中是一个**数据结构类型** —— `struct mm_struct`

具体进程的地址空间变量

进程创建时，不但要创建`PCB`，还要创建`mm_struct`结构体 ,还有`页表`

`tssk_struct(PCB)` -> `struct mm_struct`

`struct mm_struct` 大小`32`位`4GB`

```c++
struct mm_struct{
	int size();//大小 
	//什么时候给我
	//如何分配
	//...
}
```

#### 划分区域：

如何使用struct 结构体进行各种划分？

```c++
struck desttop
{
	int start_girl();
	int end_girl();
    int start_boy();
	int end_boy();
}
desktop t(0,500,501,1000);
```

将铅笔放在 600 - 603 (虚拟地址)的位置，但是还没放呢，先划分出来，
例如这块空间我要放栈区，那块我要放堆区

#### 虚拟地址：

>  **地址空间上进行区域划分时，对应的线性位置虚拟地址！**
>
> ![image-20220708205626541](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/imageimage-20220708205626541.png)

##### 证明虚拟地址这样排布

> ![image-20220708205457218](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/imageimage-20220708205457218.png)

**每个进程**

1. 都认为地址空间的划分，是按照`4GB`空间划分的，

2. 都认为自己拥有`4GB`(`0x00000000`到`0xffffffff`),但是在物理空间不一定是多大

3. 都会有一个`mm_struct`

```c++
struct mm_struct
{
    //代码区域
    unsingned int code_start;
    unsingned int code_end;
    //已初始化
    unsingned int init_data_start;
    unsingned int init_data_end;
    //未初始化
    unsingned int uninit_data_start;
    unsingned int uninit_data_end;
    //堆区
    unsingned int heap_start;
    unsingned int heap_end;
    
    ......
    //栈区
    unsingned int stack_start;
    unsingned int stack_end;
}
```

虽然这里只有`start`和`end`，但是每个进程都可以认为`mm_struct`代表`整个内存`且所有地址为`0x00000000`到`0xffffffff`

#### 虚拟地址(线性地址)：

> 在Linux中是等价的

`0x00000000`到`0xffffffff`  一段连续的虚拟地址，叫做线性地址

【4 * 1024 * 1024 *  1024】 =  4GB (2的32次方)

#### 页表：

> 由OS控制页表 + MMU 

>  页表 + MMU

**MMU(CPU中)：**一种硬件，用来查页表的，

> ![image-20220708174138560](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/imageimage-20220708174138560.png)

#### 映射关系：

虚拟地址，通过页表 映射到对应的物理空间

> ![image-20220708175736730](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/imageimage-20220708175736730.png)



#### 为什么用页表映射？

1. 如果PCB直接访问物理空间，没有中间的OS管理(页表)，可能会出现危险，万一代码出现了bug，那么可能会将其他进程的数据修改，这是不对的

   > ![image-20220708181400894](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/imageimage-20220708181400894.png)

2. ```c++
   const char* str = "hello world!";
   *str = "H";
   ```

   此操作是不可能执行的，因为`str`存的是字符常量，不许修改，那么为什么不能修改？

   本质是因为`OS`给你的权限只有`r`(只读)权限

   > ![image-20220708181704050](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/imageimage-20220708181704050.png)

#### 1.为什么有地址空间？

1. 通过添加一层软件层，完成有效的对进城操作内存进行风险管理(权限管理)，本质是为了，保护物理内存以及各个进程的数据安全。

#### 分配物理空间(写时拷贝)：

什么时间分配物理空间？当你用的时候再给你分配 物理空间

当你申请1000字节，那么只是在程序地址空间(虚拟地址)申请成功，当你读写的时候再进行分配。

也就是说，申请成功不代表，物理空间已经有1000字节归你了，只是虚拟空间开辟成功，

```c++
heap_start;
heap_end+=1000;
```

#### 缺页中断：

当你申请1000空间，想读写时，OS说你等等，我先给你申请空间，把映射关系建立起来，你在用，这个过程叫做——缺页重点。

#### **2.为什么有地址空间？**

2. 将内存申请和内存使用的概念在时间上划分清楚，通过虚拟地址空间，来屏蔽底层申请内存的过程，达到进程读写内存和OS进行内存管理操作，进行软件上面的分离！

#### 内存管理算法

当物理内存满了，还能申请空间吗？可以

内存管理算法会，查看当前物理内存的数据，如果有数据长时间闲置，则会将它转换到磁盘上，然后再将物理空间申请出来，映射到你的页表上。



#### main函数映射：

CUP在找main函数的时候，是怎么知道其实代码在哪里的？

通过相同的虚拟地址，映射到不同的物理地址空间找到。则cup每次取固定位置找main函数就可以

**但是`main`函数的地址也不是不变的，会根据代码不同而轻微改变！**

> ![image-20220708190439475](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/imageimage-20220708190439475.png)

#### **3.为什么有地址空间？**

站在CPU和应用层的角度，进程统一使用4GB空间，而且每个空间区域的相对位置，是比较确定的！

代码在物理空间可以随便存，只要映射到对应位置就可以啦！

#### 三个问题的结论

OS最终这样设计的目的，达到一个目标：每个进程都认为自己是独占系统资源的！

## 重新认识进程

进程 = 数据结构（描述进程的PCB + 进程地址空间(mm_struct) + 页表） + 数据 + 代码





## 推荐书籍

《操作系统精髓设计与原理》 《现在操作系统》

## Makefile

myproc : myproc.c

​		gcc -o `$@` `$ ?`  -std=c99

.PGONT:clean

clean:

​	rm -f myproc

$@  冒号左边   依赖文件

$?  冒号右边  依赖文件
