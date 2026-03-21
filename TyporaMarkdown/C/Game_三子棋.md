# 思维导图
![在这里插入图片描述](https://img-blog.csdnimg.cn/0ad872d307a24ea8ab813a1f78f4b5bd.jpg?x-oss-process=image/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBAaWx1bzEy,size_20,color_FFFFFF,t_70,g_se,x_16#pic_center)

# 三子棋

---
####  创建三个文件
##### 1. 创建主体运行文件（test.c）
##### 2. 创建游戏运行文件（game.c）
##### 3. 创建全局变量头文件（game.h）
####  首先引用头文件
##### 1. 在（game.h）中引入头文件

```
#include <stdio.h>
```
##### 2.在（game.c）中创建主函数
```
int main()
{

    return 0;
}
```
##### 3.创建循环(test.c)
- 打印菜单
- 选择菜单：开始游戏、结束游戏、重新输入
>  创建循环
1. - 打印菜单
   - 提示请选择
```
menu()//打印菜单的函数
{
	printf("************************\n");
	printf("*****    1.play    *****\n");
	printf("*****    2.exit    *****\n");
	printf("************************\n");
}
int main()
{
	do
	{
		menu();//打印菜单
		printf("请选择:>\n");
		}
	} while ();
	return 0;
}
```
>打印菜单
1. - 创建接收的变量
   - 选择程序
        - 输入  1 ：游戏开始
        - 输入  0 ：游戏结束
        - 输入其他：重新输入

```
int main()
{
	int input = 0; //创建接收的变量
	do
	{
		menu();
		printf("请选择\n");
		scanf("%d", &input);//scanf 为接收键盘输入的变量
		switch (input)
		{
		case 1:
			game();
			break;
		case 0:
			printf("游戏结束\n");
			break;
		default:
			printf("输入错误，请重新输入！\n");
			break;
		}
	} while(input);
	return 0;
}
```
##### 4.进入游戏（函数game()）
- test.c
    - 定义board为二维数组
    - 初始化棋盘  全部打印空格
```
void game()
{
	//存储数据 - 二维数组
	char board[ROW][COL];
	//初始化棋盘 - 初始化空格
	InitBoard(board, ROW, COL);
}
```
- game.h
    - 头文件包含在game.h中 ，在其他两个.c 文件中声明，就可以直接引用.h文件的所有文件
    - 上面的board 需要两个整形，为了方便后期调整，
    - 在.h文件中定义 ROW、 COL ，方便后期修改
    - 初始化棋盘 - 函数的定义
```
//头文件的包含
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


//符号的定义
#define ROW 3
#define COL 3

//函数的声明

//初始化棋盘的
void InitBoard(char board[ROW][COL], int row, int col);
```
- game.c (初始化成空格)
    - 接收二维数组 并接收两个横纵坐标的参数
    - 两层循环 打印出二维棋盘  并赋值为“空格”
```
void InitBoard(char board[ROW][COL], int row, int col)
{
	int i = 0;
	int j = 0;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			board[i][j] = ' ';
		}
	}
}
```
- test.c(打印一下棋盘)
    - 打印棋盘为了 显示游戏界面 并且实时更新打印界面
    - 后面玩家下完棋 会把玩家走的步骤打印出来
    - 电脑步骤同理
```
棋盘样式：
   |   |
---|---|---
   |   |
---|---|---
   |   |
```
```
void game()
{
	//存储数据 - 二维数组
	char board[ROW][COL];
	//初始化棋盘 - 初始化空格
	InitBoard(board, ROW, COL);

	//打印一下棋盘 - 本质是打印数组的内容
	DisplayBoard(board, ROW, COL);

```
- game.h
    - 函数的定义
```
//打印棋盘的函数
void DisplayBoard(char board[ROW][COL], int row, int col);
```
- game.c
    - 两层循环打印
    - 每次循环 打印  "空格-坐标-空格" 和 "丨"
        - 第三次打印  因为棋盘最后面没有 "丨"
    - 打印第三行---同上
```
void DisplayBoard(char board[ROW][COL], int row, int col)
{
	int i = 0;
	for (i = 0; i < row; i++)
	{
		int j = 0;
		for (j = 0; j < col; j++)
		{
			printf(" %c ", board[i][j]);
			if(j<col-1) 
				printf("|");
		}
		printf("\n");
		if (i < row - 1)
		{
			int j = 0;
			for (j = 0; j < col; j++)
			{
				printf("---");
				if(j<col-1)
					printf("|");
			}
			printf("\n");
		}
	}
}
```
##### 5.接受游戏状态
- test.c(玩家下棋、电脑下棋)
    - 定义一个代替变量
    - 当函数变化时 代替变量会改变返回不同的值
    - 这时根据 代替变量返回的值，判断游戏进度
```
	//玩家下棋
	PlayerMove(board, ROW, COL);
	DisplayBoard(board, ROW, COL);//打印棋盘

	//电脑下棋
	ComputerMove(board, ROW, COL);
	DisplayBoard(board, ROW, COL);//打印棋盘
```
```
void game()
{
	//存储数据 - 二维数组
	char board[ROW][COL];
	//初始化棋盘 - 初始化空格
	InitBoard(board, ROW, COL);

	//打印一下棋盘 - 本质是打印数组的内容
	DisplayBoard(board, ROW, COL);
	char ret = 0;//接受游戏状态
	while (1)
	{
		//玩家下棋
		PlayerMove(board, ROW, COL);
		DisplayBoard(board, ROW, COL);//打印棋盘

		//电脑下棋
		ComputerMove(board, ROW, COL);
		DisplayBoard(board, ROW, COL);//打印棋盘
	}
	if (ret == '*')
	{
		printf("玩家赢了\n");
	}
	else if(ret == '#')
	{
		printf("电脑赢了\n");
	}
	else
	{
		printf("平局\n");
	}
	DisplayBoard(board, ROW, COL);
}
```
- game.h(玩家下棋、电脑下棋) 
    - 定义函数
```
//玩家下棋
void PlayerMove(char board[ROW][COL], int row, int col);

//电脑下棋
void ComputerMove(char board[ROW][COL], int row, int col);
```
- game.c(玩家走、电脑走)

    - 玩家走：
        1. 提示玩家输入坐标
        2. 接收坐标
        3. 判断是否满足 要求
            - 如果坐标没被占用 就下棋
            - 被占用--提示重新输入
            - 超出坐标范围--提示重新输入
```
// 1. 玩家走
void PlayerMove(char board[][COL], int row, int col) 
{
	int x = 0;
	int y = 0;

	printf("玩家走:>\n");

	while (1)
	{
		printf("请输入下棋的坐标:>");
		scanf("%d %d", &x, &y);
		//判断坐标合法性
		if (x >= 1 && x <= row && y >= 1 && y <= col)
		{
			//下棋
			//坐标是否被占用
			if (board[x - 1][y - 1] == ' ')
			{
				board[x - 1][y - 1] = '*';
				break;
			}
			else
			{
				printf("坐标被占用, 请重新输入\n");
			}
		}
		else
		{
			printf("坐标非法, 请重新输入\n");
		}
	}
}
```
- 电脑走：
     1. 告诉玩家电脑走
     2. 用- rand() 函数写出随机数 
     3. %坐标位置  是限制是随机数的最大值(范围)
     4. 判断位置并打印
```
void ComputerMove(char board[ROW][COL], int row, int col)
{
	printf("电脑走:>\n");

	while (1)
	{
		int x = rand() % row;
		int y = rand() % col;

		//判断占用
		if (board[x][y] == ' ')
		{
			board[x][y] = '#';
			break;
		}
	}
}
```
##### 5.判断游戏进度(结束/继续)
```
		//判断玩家是否赢得游戏
		ret = IsWin(board, ROW, COL);
		if (ret != 'C')
			break;
```
game()函数 整体代码
```
void game()
{
	//存储数据 - 二维数组
	char board[ROW][COL];
	//初始化棋盘 - 初始化空格
	InitBoard(board, ROW, COL);

	//打印一下棋盘 - 本质是打印数组的内容
	DisplayBoard(board, ROW, COL);
	char ret = 0;//接受游戏状态
	while (1)
	{
		//玩家下棋
		PlayerMove(board, ROW, COL);
		DisplayBoard(board, ROW, COL);
		//判断玩家是否赢得游戏
		ret = IsWin(board, ROW, COL);
		if (ret != 'C')
			break;
		//电脑下棋
		ComputerMove(board, ROW, COL);
		DisplayBoard(board, ROW, COL);
		//判断电脑是否赢得游戏
		ret = IsWin(board, ROW, COL);
		if (ret != 'C')
			break;
	}
	if (ret == '*')
	{
		printf("玩家赢了\n");
	}
	else if(ret == '#')
	{
		printf("电脑赢了\n");
	}
	else
	{
		printf("平局\n");
	}
	DisplayBoard(board, ROW, COL);
}
```
- game.h(定义函数)
    1. 玩家赢了 - *
    2. 电脑赢了 - #
    3. 平局     - Q
    4. 游戏继续 - C
```
//判断游戏是否有输赢
char IsWin(char board[ROW][COL], int row, int col);
```
- game.c (判断输赢函数的实现)
    - 判断三行、三列、对角线是否一致
    - 不管是那方胜利 直接打印这一行的第一个符号
    - 判断平局 棋盘满了平局 /不满继续

```
char IsWin(char board[ROW][COL], int row, int col)
{
	int i = 0;
	//判断三行
	for (i = 0; i < row; i++)
	{
		if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][1] != ' ')
		{
			return  board[i][1];//
		}
	}
	
	//判断三列
	for (i = 0; i < col; i++)
	{
		if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[1][i] != ' ')
		{
			return board[1][i];
		}
	}

	//判断对角线
	if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[1][1] != ' ')
	{
		return board[1][1];
	}
	if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[1][1] != ' ')
	{
		return board[1][1];
	}

	//判断平局
	//如果棋盘满了返回1， 不满返回0
	int ret = IsFull(board, row, col);
	if (ret == 1)
	{
		return 'Q';
	}

	//继续
	return 'C';
}
```
    1. 玩家赢了 - *
    2. 电脑赢了 - #
    3. 平局     - Q
    4. 游戏继续 - C
- 上面用到了一个函数：
    - IsFull(board, row, col);
    - 用来判断棋盘是否已满
    - 如果所有棋盘都没满则 返回0
    - 
    - 上面会判断 == 1 返回 Q
    - 否则 返回C ---游戏继续
```
int IsFull(char board[ROW][COL], int row, int col)
{
	int i = 0;
	int j = 0;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			if (board[i][j] == ' ')
			{
				return 0;//棋盘没满
			}
		}
	}

```

## 请看个原文件的代码
### game.h
```
#pragma once

//头文件的包含
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


//符号的定义
#define ROW 3
#define COL 3

//函数的声明

//初始化棋盘的
void InitBoard(char board[ROW][COL], int row, int col);

//打印棋盘的函数
void DisplayBoard(char board[ROW][COL], int row, int col);

//玩家下棋
void PlayerMove(char board[ROW][COL], int row, int col);

//电脑下棋
void ComputerMove(char board[ROW][COL], int row, int col);

//
//1. 玩家赢了 - *
//2. 电脑赢了 - #
//3. 平局 - Q
//4. 游戏继续 - C

//判断游戏是否有输赢
char IsWin(char board[ROW][COL], int row, int col);


```
### test.c
```
#define _CRT_SECURE_NO_WARNINGS 1

#include "game.h"

void menu()
{
	printf("******************************\n");
	printf("******    1. play        *****\n");
	printf("******    0. exit        *****\n");
	printf("******************************\n");
}

void game()
{
	//存储数据 - 二维数组
	char board[ROW][COL];
	//初始化棋盘 - 初始化空格
	InitBoard(board, ROW, COL);

	//打印一下棋盘 - 本质是打印数组的内容
	DisplayBoard(board, ROW, COL);
	char ret = 0;//接受游戏状态
	while (1)
	{
		//玩家下棋
		PlayerMove(board, ROW, COL);
		DisplayBoard(board, ROW, COL);
		//判断玩家是否赢得游戏
		ret = IsWin(board, ROW, COL);
		if (ret != 'C')
			break;
		//电脑下棋
		ComputerMove(board, ROW, COL);
		DisplayBoard(board, ROW, COL);
		//判断电脑是否赢得游戏
		ret = IsWin(board, ROW, COL);
		if (ret != 'C')
			break;
	}
	if (ret == '*')
	{
		printf("玩家赢了\n");
	}
	else if(ret == '#')
	{
		printf("电脑赢了\n");
	}
	else
	{
		printf("平局\n");
	}
	DisplayBoard(board, ROW, COL);
}

int main()
{
	int input = 0;
	srand((unsigned int)time(NULL));

	do
	{
		menu();
		printf("请选择:>");
		scanf("%d", &input);
		switch (input)
		{
		case 1:
			game();
			break;
		case 0:
			printf("退出游戏\n");
			break;
		default:
			printf("选择错误，重新选择\n");
			break;
		}
	} while (input);

	return 0;
}
```
### game.c
```
#define _CRT_SECURE_NO_WARNINGS 1

#include "game.h"



void InitBoard(char board[ROW][COL], int row, int col)
{
	int i = 0;
	int j = 0;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			board[i][j] = ' ';
		}
	}
}

//void DisplayBoard(char board[ROW][COL], int row, int col)
//{
//	int i = 0;
//	for (i = 0; i < row; i++)
//	{
//		printf(" %c | %c | %c \n", board[i][0], board[i][1], board[i][2]);
//		if(i<row-1)
//			printf("---|---|---\n");
//	}
//}
//


void DisplayBoard(char board[ROW][COL], int row, int col)
{
	int i = 0;
	for (i = 0; i < row; i++)
	{
		int j = 0;
		for (j = 0; j < col; j++)
		{
			printf(" %c ", board[i][j]);
			if(j<col-1)
				printf("|");
		}
		printf("\n");
		if (i < row - 1)
		{
			int j = 0;
			for (j = 0; j < col; j++)
			{
				printf("---");
				if(j<col-1)
					printf("|");
			}
			printf("\n");
		}
	}
}


void PlayerMove(char board[][COL], int row, int col) 
{
	int x = 0;
	int y = 0;

	printf("玩家走:>\n");

	while (1)
	{
		printf("请输入下棋的坐标:>");
		scanf("%d %d", &x, &y);
		//判断坐标合法性
		if (x >= 1 && x <= row && y >= 1 && y <= col)
		{
			//下棋
			//坐标是否被占用
			if (board[x - 1][y - 1] == ' ')
			{
				board[x - 1][y - 1] = '*';
				break;
			}
			else
			{
				printf("坐标被占用, 请重新输入\n");
			}
		}
		else
		{
			printf("坐标非法, 请重新输入\n");
		}
	}
}

void ComputerMove(char board[ROW][COL], int row, int col)
{
	printf("电脑走:>\n");

	while (1)
	{
		int x = rand() % row;
		int y = rand() % col;

		//判断占用
		if (board[x][y] == ' ')
		{
			board[x][y] = '#';
			break;
		}
	}
}


int IsFull(char board[ROW][COL], int row, int col)
{
	int i = 0;
	int j = 0;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			if (board[i][j] == ' ')
			{
				return 0;//棋盘没满
			}
		}
	}

	return 1;//棋盘满了
}
char IsWin(char board[ROW][COL], int row, int col)
{
	int i = 0;
	//判断三行
	for (i = 0; i < row; i++)
	{
		if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][1] != ' ')
		{
			return  board[i][1];//
		}
	}
	
	//判断三列
	for (i = 0; i < col; i++)
	{
		if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[1][i] != ' ')
		{
			return board[1][i];
		}
	}

	//判断对角线
	if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[1][1] != ' ')
	{
		return board[1][1];
	}
	if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[1][1] != ' ')
	{
		return board[1][1];
	}

	//判断平局
	//如果棋盘满了返回1， 不满返回0
	int ret = IsFull(board, row, col);
	if (ret == 1)
	{
		return 'Q';
	}

	//继续
	return 'C';
}
```