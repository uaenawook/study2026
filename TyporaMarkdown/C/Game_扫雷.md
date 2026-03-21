# 【C语言】扫雷
> ### 整体来说比较简单  
> 适合初学C语言的小白 
> 需要你掌握以下知识：


    掌握——分支switch、循环for、while语句
    掌握——函数（传参，声明，创建）
    掌握——数组（创建，传参）

> ### 阅读文章须知  
> #### 此代码在VS2019软件中编写  (Visual Studio 2019)

    文章顺序
    
    1.先说整体思路
    2.写出部分代码
    3.解析上述代码


#### 布局

```c   
    1.打印菜单
    2.接收变量
    3.打印雷区
    4.接收坐标
    5.判断雷区周围包括坐标本身在内的 9个坐标内有几个雷
    6.  *为显示可排查区域
    7.  1为雷
    8.踩到雷结束游戏
    9.全部排查则游戏胜利
    
    ************************
    *******  1.play  *******
    *******  0.exly  *******
    ************************
    请选择输入开始游戏：> 1
    共有30个雷
    0 1 2 3 4 5 6 7 8 9
    1 * * * * * * * * *
    2 * * * * * * * * *
    3 * * * * * * * * *
    4 * * * * * * * * *
    5 * * * * * * * * *
    6 * * * * * * * * *
    7 * * * * * * * * *
    8 * * * * * * * * *
    9 * * * * * * * * *
    
    //作弊 看到雷的布局
    0 1 2 3 4 5 6 7 8 9
    1 0 0 1 1 1 0 0 1 0
    2 1 0 0 1 1 0 0 0 1
    3 0 0 0 1 1 0 0 1 0
    4 1 1 0 1 1 0 0 0 0
    5 0 0 1 1 0 1 1 1 1
    6 0 0 0 1 0 0 0 0 0
    7 1 1 0 1 0 0 1 0 0
    8 0 0 0 0 0 0 0 0 0
    9 0 0 1 1 1 0 0 0 1
    
    请输入坐标：5 5
    0 1 2 3 4 5 6 7 8 9
    1 * * * * * * * * *
    2 * * * * * * * * *
    3 * * * * * * * * *
    4 * * * * * * * * *
    5 * * * * 5 * * * *    显示周围雷的数量
    6 * * * * * * * * *
    7 * * * * * * * * *
    8 * * * * * * * * *
    9 * * * * * * * * *
```
#### 游戏分为——两部分
- 开始游戏
- 结束游戏

#### 开始游戏分为——四部分
- 创建雷区
- 初始化并打印
- 生成雷
- 排查雷

> #### 简单看一下整体布局 不至于从一开始就劝退初学者  
> #### **全文共217行代码  整体代码在文章最后**
> 下面跟随我的思路一起完成扫雷游戏吧！

#### 首先创建三个文件

> .c     文件是C语言文件    
> .h     文件是头文件

- test.c      ：写主程序的.c文件  
- game.c      : 写游戏主要代码的.c文件  
- game.h      ：引用 头文件 和 声明的.h头文件
#### 在test.c文件中
> 创建main函数主体  
> 主要思路是：  
> - ##### 先打印菜单：  1开始 /  0结束
- ##### 选择并开始游戏

> 如在手机中观看 可左右滑动查看查处部分代码

```c
    void emnu()
    {
    	printf("************************\n");
    	printf("*******  1.play  *******\n");
    	printf("*******  0.exly  *******\n");
    	printf("************************\n");
    
    }
    int main()
    {
    	int input = 0;
    	srand((unsigned int)time(NULL)); //后面创建随机数的函数
    	do {
    		//打印菜单
    		emnu();
    		printf("请选择输入开始游戏：> ");
    		scanf("%d", &input);
    		switch (input)
    		{
    		case 1:
    			game();
    			//printf("游戏开始\n");
    			break;
    		case 0:
    			printf("游戏结束\n");
    			break;
    		default:
    			printf("输入错误，请重新选择！\n");
    			break;
    		}
    
    	} while (input);
    	return 0;
    }
```

> srand((unsigned int)time(NULL)); 对于这句话后面会讲到
> - ##### 上述代码分为 ——— 三部分  
>   1.打印菜单  
>   2.接收字符  
>   3.判断状态  


    为了一打开程序就进入游戏状态
    所以用了 **do{}while{}** 循环 

1.打印菜单调用 emnu()函数

```c   
        void emnu()
        {
        	printf("************************\n");
        	printf("*******  1.play  *******\n");
        	printf("*******  0.exly  *******\n");
        	printf("************************\n");
        }
```
2.接收字符
```c   
        我们在循环外部定义 
            int input = 0;  接收指令的变量
        
            scanf("%d",&input);  接收键盘输入的函数
                注意：
                    %d后面不要加空格 
                     & 符号不要忘记写
```
3.判断接收字符的状态
```c
        switch(整形表达式) 
        {
            case 整形常量表达式:
                break; //跳出switch 去下面的while中判断是否继续循环
            case 0:
                break;
            default://相当于if语句中的else的作用
                    //当上面的语句都不满足时 执行此语句
                break;
        }while(input); //input为0时结束游戏
        
    输入1       继续游戏
    输入0       结束游戏
    输入错误    给出提示并从新输入
```
- ##### 当你想验证一下现在写的代码时 
    - 可以在game.h中引入头文件
    - 并且在test.c中引入game.h头文件
    - 这样所有头文件都放在game.h中就可以了

    
    game.h
    ```c
        #pragma once
        #include <stdio.h>
    ```
        在头文件中  第一行  写入#pragma once
        在其他文件中不管包含几次<stdio.h>都只拷贝一次
        是为了防止头文件重复 做无用功
    
    test.c
    ```c
        #include "game.h"
	```

##### 经过上面的代码 可以在case 1: 中调用函数game()
### ganme()分为——五部分
- 1.创建雷区
- 2.初始化
- 3.打印初始化
- 4.生成雷
- 5.排查雷

#### 1.创建雷区
> test.c

```c
	void game()
	{
    	char LQu[ROWS][COLS]; 存放雷的信息
    	char PCha[ROWS][COLS]; 排查雷的信息
    }
```
##### so easy 有没有  雷区创建好了
#### 2.初始化雷区

```c
    void game()
    {
    	//创建雷区
    	char LQu[ROWS][COLS]; //存放雷的信息
    	char PCha[ROWS][COLS];//排查雷的信息
    
    	//初始化
    	CShi(LQu, ROWS, COLS,'0');//雷区
    	CShi(PCha,ROWS, COLS,'*');//排查区
    
    	//打印初始化
    	//DY(LQu, ROW, COL);//雷区
    	printf("共有%d个雷\n",LEI);
    
    	DY(PCha, ROW, COL);//排查区
    
    	//生成雷
    	S_L(LQu, ROW, COL,LEI);
    	printf("\n");
    	//DY(LQu, ROW, COL);//雷区
    
    	//排查雷
    	P_C(LQu,PCha, ROW, COL);
    	DY(PCha, ROW, COL);//排查区
    }
```
##### 可以看到创建雷区 用到了两个数组 LQu PCha
##### 先看下game.h中的代码
> game.h

```c
    #pragma once

    #include <stdio.h>
    #include <stdlib.h>
    #include <time.h>
    #include <string.h>
    
    
    #define ROW 9
    #define COL 9
    
    #define ROWS ROW+2  //ROW+2
    #define COLS COL+2  //COL+2
    
    #define LEI 10
    
    
    //初始化
    void CShi(char CShi[ROWS][COLS], int rows, int cols,char ret);//雷区
```
##### 上述数组用到了两个 常量ROWS、COLS 怎么来的？

```c
    这里用到5个变量，用#define定义
    #define 定义全局变量
    
    ROW 为用户可见区域 横坐标
    COL 为用户可见区域 纵坐标 
    ROWS  为底层排雷区域 横坐标
    COLS  为底层排雷区域 纵坐标
    LEI  为雷的个数
    
    为什么分为 ROW 和 ROWS 呢
    我们开头说到 比如是9*9 的格子
    在扫描雷的时候要扫描坐标在内的周围的9个格子
    如下：
        * * * 
        * n *
        * * *
    整体的布局：(ROW,COL)
    0 1 2 3 4 5 6 7 8 9
    1 * * * * * * * * *
    2 * * * * * * * * *
    3 * * * * * * * * *
    4 * * * * * * * * *
    5 * * * * * * * * *
    6 * * * * * * * * *
    7 * * * * * * * * *
    8 * * * * * * * * *
    9 * * * * * * * * *
    
    但是：
        左上(1,1)，左下(1,9)，右上(9,1)，右下(9,9).....
        这几个坐标访问时就越界了
    所以：
        我们在底层代码扫描时 把上下左右都加上一行
        这时访问数组时就不会出现越界了
        也就有了ROWS、COLS 这两个变量
            #define ROW 9
            #define COL 9
    
            #define ROWS ROW+2  //ROW+2
            #define COLS COL+2  //COL+2

```
##### game.h 中下方还有一行代码——初始化 （下）
> 左右滑动查看代码

> test.c

```c
    char LQu[ROWS][COLS]; //存放雷的信息 定义数组
	char PCha[ROWS][COLS];//排查雷的信息 定义数组
```
```c
//需要初始化的代码：
	CShi(LQu, ROWS, COLS,'0');//雷区
	CShi(PCha,ROWS, COLS,'*');//排查区
	    这样设计用一个函数传参 就能给不同数组 初始化成不同的 字符
```
> game.h

```c
	//初始化
    void CShi(char CShi[ROWS][COLS], int rows, int cols,char ret);//雷区
```
```c
        函数返回类型 不需要返回值 所以为 void
        数组传参 接收一个数组 用char CShi[][]数组接收
        ROWS COLS 是整形 用int 类型变量接收
        后面的 '0' '*' 用char 字符类型接收  

        
    因为排查雷需要更大的数组 所以用到了 ROWS COLS
    test.c      中定义函数
    game.h      声明函数
    game.c      实现代码
```
> game.c
```c
    #include "game.h"
    
    //初始化雷区
    void CShi (char CShi[ROWS][COLS], int rows, int cols,char ret)
    {
    	int i = 0;
    	for (i = 0; i < rows; i++)
    	{
    		int j = 0;
    		for (j = 0; j < cols; j++)
    		{
    			CShi[i][j] = ret;
    		}
    	}
    }
```
```c
    用for循环将两个数组初始化成全0  全*
    CShi(LQu, ROWS, COLS,'0');
    0 1 2 3 4 5 6 7 8 9 a b
    1 0 0 0 0 0 0 0 0 0 0 0
    2 0 0 0 0 0 0 0 0 0 0 0
    3 0 0 0 0 0 0 0 0 0 0 0
    4 0 0 0 0 0 0 0 0 0 0 0
    5 0 0 0 0 0 0 0 0 0 0 0
    6 0 0 0 0 0 0 0 0 0 0 0
    7 0 0 0 0 0 0 0 0 0 0 0
    8 0 0 0 0 0 0 0 0 0 0 0
    9 0 0 0 0 0 0 0 0 0 0 0
    a 0 0 0 0 0 0 0 0 0 0 0
    b 0 0 0 0 0 0 0 0 0 0 0
    这一层布置雷 扫雷
    
    CShi(PCha,ROWS, COLS,'*');
    0 1 2 3 4 5 6 7 8 9 a b
    1 * * * * * * * * * * *
    2 * * * * * * * * * * *
    3 * * * * * * * * * * *
    4 * * * * * * * * * * *
    5 * * * * * * * * * * *
    6 * * * * * * * * * * *
    7 * * * * * * * * * * * 
    8 * * * * * * * * * * *
    9 * * * * * * * * * * *
    a * * * * * * * * * * *
    b * * * * * * * * * * *
    这一层打印出来给用户看 当然不是打印11*11  是打印9*9 后面会说到
    (16进制  a=10 b=11 c=12 d=13 e=14 f=15)
```
#### 3.打印初始化

> test.c

```c
    //打印初始化
	DY(PCha, ROW, COL);//排查区
	printf("共有%d个雷\n",LEI); //告诉用户有几个雷
```
> game.h
```c
    //打印初始化
    void DY(char LQu[ROWS][COLS],int rows,int cols);//雷区
```
    传参上面讲了 同理
##### 这里要强调的是传参的时候用的是ROW COL

```c   
    因为打印出来的是要给用户观察的
    ROW COL 定义的为9
    所以要打印9*9 的个格子 
    
    聪明的你要问了：怎么才能在11*11 的数组中打印9*9 的格子呢？
    
    你： 我才没问呢  我都知道！
    
    你： 只要在数组下标为1 的地方打印到下标10就可以啦
    
    你真是个机灵鬼！！！
```
> game.c

```c
    //打印
    void DY(char LQu[ROWS][COLS], int row, int col)
    {
    	int i = 0;
    	for (i = 0; i <= row; i++)
    	{
    		printf("%d ", i);
    	}
    	printf("\n");
    
    	for (i = 1; i <= row; i++)
    	{
    		int j = 0;
    		printf("%d ", i);
    		for (j = 1; j <= col; j++)
    		{
    			printf("%c ", LQu[i][j]);
    		}
    		printf("\n");
    	}
    	printf("\n");
    }
```
```c
    上述代码 第一个循环 是打印出了每行的编号 为了方便观察
    下面的代码 也在每一行的首元素打印了编号
    最后for循环打印的数组初始化的内容
    
    打印结果如下：DY(PCha, ROW, COL);
            共有10个雷
            0 1 2 3 4 5 6 7 8 9
            1 * * * * * * * * *
            2 * * * * * * * * *
            3 * * * * * * * * *
            4 * * * * * * * * *
            5 * * * * * * * * *
            6 * * * * * * * * *
            7 * * * * * * * * *
            8 * * * * * * * * *
            9 * * * * * * * * *
```
### 4.生成雷
> test.c
```c
    //生成雷
	S_L(LQu, ROW, COL,LEI); 
	printf("\n");
```
> game.h
```c
    //生成雷
    void S_L(char LQu[ROWS][COLS], int row, int col,int lei);
```
> game.c
```c
    //生成雷
    void S_L(char LQu[ROWS][COLS], int row, int col,int lei)
    {
    
    	int i = lei;
    	while(i)
    	{
    		int x = rand() % row+1;
    		int y = rand() % col+1;
    
    		if (LQu[x][y] != '1')
    		{
    			LQu[x][y] = '1';
    			i--;
    		}
    	}
    }
```
```c
    思路：
        1.x y在规定坐标内 生成随机数
        一个随机数%10 则得到的结果不会大于10 也就是最大得到9
        2.在随机产生的坐标中放入字符'1'
```
##### 产生随机数rand()

```c
    在主函数中调用srand()
    srand((unsigned int)time(NULL));
    接收time系统时间 强制准换成无符号整型(unsigned int)
    
    srand() 的头文件    <stdlib.h>
    time()  的头文件    <time.h>
    
    此时就可以在已经声明的范围内 使用rand()
```
> ### 还差一步就完成啦 ٩(๑>◡<๑)۶  加油！
### 5.排查雷
##### 败北：坐标 = '1'
##### 胜利：输入坐标 = 坐标 - 雷

> test.c
```c
    //排查雷
	P_C(LQu,PCha, ROW, COL);
	DY(PCha, ROW, COL);//打印排查区
```
> game.h
```c
    //排查雷
    char P_C(char LQu[ROWS][COLS], char PCha[ROWS][COLS], int row, int col);
```
> game.c
```c
    //判断周围的雷数
    int LS(char LQu[ROWS][COLS], int x,int y)
    {
    	return (LQu[x-1][y]
    		+ LQu[x - 1][y - 1]
    		+ LQu[x][y - 1]
    		+ LQu[x + 1][y - 1]
    		+ LQu[x + 1][y]
    		+ LQu[x + 1][y + 1]
    		+ LQu[x][y + 1]
    		+ LQu[x - 1][y + 1]
    		- 8 * '0');
    }

    //排查
    char P_C(char LQu[ROWS][COLS], char PCha[ROWS][COLS], int row, int col)
    {
    	int x = 0;//横坐标
    	int y = 0;//纵坐标
    	int win = 0; //输入坐标次数
    	//判断坐标合法
    	while (win<row*col-LEI)
    	{
    		printf("请输入坐标：");
    		scanf("%d %d", &x, &y);
    
    		//排查雷
    		if ((x > 0 && x <=row) && (y > 0 && y <=col))
    		{
    			if (LQu[x][y] != '1')
    			{
    				//判断周围有几个雷
    				int L = LS(LQu, x, y);
    				PCha[x][y] = (L+'0');
    				DY(PCha, ROW, COL);//打印排查区
    
    				win++;
    			}
    			else
    			{
    				printf("很遗憾，你输了\n\n");
    				DY(LQu, ROW, COL);//打印雷区
    
    				break;
    			}
    		}
    
    		else
    		{
    			printf("坐标非法，请重新输入！\n\n");
    		}
    	}
    	if (win == ROW * COL - LEI)
    	{
    		printf("恭喜你胜利了\n\n");
    	}
    }
```
解释说明：
```c
    x       横坐标
    y       纵坐标
    win     输入坐标数
    
    当输入坐标次数 < 雷区-雷
        接收坐标;
        如果： x y 符合要求
            如果：底层坐标xy != '1'
                则判断周雷数
                函数() - 下面单独讲
                假如返回数字 3
                打印时需要打印字符'3' - 下面单独讲
                打印雷区；
                win++；
            否则：
                游戏败北
                打印雷区
                跳出
        否则：
            重新输入
    
    当输入坐标次数 = 雷区-雷
        恭喜胜利！
```
##### 首先是函数
```c
    int LS(char LQu[ROWS][COLS], int x,int y)
    {
    	return (LQu[x-1][y]
    		+ LQu[x - 1][y - 1]
    		+ LQu[x][y - 1]
    		+ LQu[x + 1][y - 1]
    		+ LQu[x + 1][y]
    		+ LQu[x + 1][y + 1]
    		+ LQu[x][y + 1]
    		+ LQu[x - 1][y + 1]
    		- 8 * '0');
    }
```
```c
    在ASCII码表中
    '0' = 48
    '1' = 49
    '2' = 50
    '3' = 51
    所以在字符'1' - 字符'0' = （59-48 = 1）
    用%d打印就能打印出数字1；
    
    计算雷的个数 因为雷用'1'表示
    所以将字符'1'转换为 数字1相加即可
    
    先把8个'1'相加  再减去(8个'0') 得到雷的个数
    
    传过来用int 接收加上'0' 转换成字符'3' 打印到屏幕上即可；
    int L = LS(LQu, x, y);
    PCha[x][y] = (L+'0');
```
> ### 恭喜你呀！٩(๑>◡<๑)۶  完成了一个大项目  
> ### 快来瓶快乐水庆祝一下！

## 完整代码如下
> test.c

```c
    #define _CRT_SECURE_NO_WARNINGS 1
    #include "game.h"
    
    void game()
    {
    	//创建雷区
    	char LQu[ROWS][COLS]; //存放雷的信息
    	char PCha[ROWS][COLS];//排查雷的信息
    
    	//初始化
    	CShi(LQu, ROWS, COLS,'0');//雷区
    	CShi(PCha,ROWS, COLS,'*');//排查区
    
    	//打印初始化
    	//DY(LQu, ROW, COL);//雷区
    	printf("共有%d个雷\n",LEI);
    
    	DY(PCha, ROW, COL);//排查区
    
    	//生成雷
    	S_L(LQu, ROW, COL,LEI);
    	printf("\n");
    	//DY(LQu, ROW, COL);//雷区
    
    	//排查雷
    	P_C(LQu,PCha, ROW, COL);
    	DY(PCha, ROW, COL);//排查区
    
    }
    
    
    void emnu()
    {
    	printf("************************\n");
    	printf("*******  1.play  *******\n");
    	printf("*******  0.exly  *******\n");
    	printf("************************\n");
    
    }
    int main()
    {
    	int input = 0;
    	srand((unsigned int)time(NULL));
    	do {
    		//打印菜单
    		emnu();
    		printf("请选择输入开始游戏：> ");
    		scanf("%d", &input);
    		switch (input)
    		{
    		case 1:
    			game();
    			//printf("游戏开始\n");
    			break;
    		case 0:
    			printf("游戏结束\n");
    			break;
    		default:
    			printf("输入错误，请重新选择！\n");
    			break;
    		}
    
    	} while (input);
    	return 0;
    }
```
> game.h
```c
    #pragma once
    
    #include <stdio.h>
    #include <stdlib.h>
    #include <time.h>
    #include <string.h>
    
    
    #define ROW 9
    #define COL 9
    
    #define ROWS ROW+2
    #define COLS COL+2
    
    #define LEI 10
    
    
    //初始化
    void CShi(char CShi[ROWS][COLS], int rows, int cols,char ret);//雷区
    
    
    //打印初始化
    void DY(char LQu[ROWS][COLS],int rows,int cols);//雷区
    
    
    
    //生成雷
    void S_L(char LQu[ROWS][COLS], int row, int col,int lei);
    
    
    //排查雷
    char P_C(char LQu[ROWS][COLS], char PCha[ROWS][COLS], int row, int col);
```
> game.c
```c
    #define _CRT_SECURE_NO_WARNINGS 1
    
    #include "game.h"
    
    //初始化雷区
    void CShi (char CShi[ROWS][COLS], int rows, int cols,char ret)
    {
    	int i = 0;
    	for (i = 0; i < rows; i++)
    	{
    		int j = 0;
    		for (j = 0; j < cols; j++)
    		{
    			CShi[i][j] = ret;
    		}
    	}
    }
    
    
    //打印
    void DY(char LQu[ROWS][COLS], int row, int col)
    {
    	int i = 0;
    	for (i = 0; i <= row; i++)
    	{
    		printf("%d ", i);
    	}
    	printf("\n");
    
    	for (i = 1; i <= row; i++)
    	{
    		int j = 0;
    		printf("%d ", i);
    		for (j = 1; j <= col; j++)
    		{
    			printf("%c ", LQu[i][j]);
    		}
    		printf("\n");
    	}
    	printf("\n");
    }
    
    
    //生成雷
    void S_L(char LQu[ROWS][COLS], int row, int col,int lei)
    {
    
    	int i = lei;
    	while(i)
    	{
    		int x = rand() % row+1;
    		int y = rand() % col+1;
    
    		if (LQu[x][y] != '1')
    		{
    			LQu[x][y] = '1';
    			i--;
    		}
    
    	}
    }
    
    //判断周围的雷数
    int LS(char LQu[ROWS][COLS], int x,int y)
    {
    	return (LQu[x-1][y]
    		+ LQu[x - 1][y - 1]
    		+ LQu[x][y - 1]
    		+ LQu[x + 1][y - 1]
    		+ LQu[x + 1][y]
    		+ LQu[x + 1][y + 1]
    		+ LQu[x][y + 1]
    		+ LQu[x - 1][y + 1]
    		- 8 * '0');
    }
    
    
    //排查
    char P_C(char LQu[ROWS][COLS], char PCha[ROWS][COLS], int row, int col)
    {
    	int x = 0;
    	int y = 0;
    	int win = 0;
    	//判断坐标合法
    	while (win<row*col-LEI)
    	{
    		printf("请输入坐标：");
    		scanf("%d %d", &x, &y);
    
    		//排查雷
    		if ((x > 0 && x <=row) && (y > 0 && y <=col))
    		{
    			if (LQu[x][y] != '1')
    			{
    				//判断周围有几个雷
    				int L = LS(LQu, x, y);
    				PCha[x][y] = (L+'0');
    				DY(PCha, ROW, COL);//排查区
    
    				win++;
    			}
    			else
    			{
    				printf("很遗憾，你输了\n\n");
    				DY(LQu, ROW, COL);//雷区
    
    				break;
    			}
    		}
    
    		else
    		{
    			printf("坐标非法，请重新输入！\n\n");
    		}
    	}
    	if (win == ROW * COL - LEI)
    	{
    		printf("恭喜你胜利了\n\n");
    	}
    }
```



> # 如果与任何疑问 欢迎留言  我看到后随时为你 解答疑问
# 希望这篇文章对初学C语言的你有所帮助
# 如果喜欢的话 记得点赞收藏哦！
# 下次再见٩(๑>◡<๑)۶