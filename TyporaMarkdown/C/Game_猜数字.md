# 猜数字游戏
#### 1.生成随机数
#### 2.猜数字（大、小、对）
#### 3.可以反复玩

**rand()** 函数生成随机数 **范围0~327677**

    头文件：<stdlib.h>
    
    想用rand函数需要用srand函数接收时间戳
    
    time() 为时间戳 头文件<time.h>
    
    srand((unsigned int)tame(NULL));
    int ret = rand();
-    
    ​    
    sqrt(i) 开平方i
    头文件 <math.h>
## 写一个猜数字游戏

    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #include <time.h>
    void menu() //打印菜单
    {
    	printf("************************\n");
    	printf("******   1.play   ******\n");
    	printf("******   0.exly   ******\n");
    	printf("************************\n");
    }
    void game()//开始游戏
    {
    	int ret = rand()%100; //限定100以内的随机数
    	int put = 0;
    	while (1)
    	{
    		printf("请输入数字：");//提示开始输入
    		scanf("%d", &put);//接收输入
    		if (put > ret)//判断
    			printf("猜大了\n");
    		else if (put < ret)//判断
    			printf("猜小了\n");
    		else//判断
    		{
    			printf("恭喜你，猜对了！\n");
    			break;//赢了以后此局结束，返回
    		}	
    	}
    }
    int main()
    {
    	//打印菜单
    	int input = 0;//要定义在外面  不然while识别不到
    	srand((unsigned int)time(NULL)); //创建随机数
    	do
    	{
    		menu();//打印菜单
    		scanf("%d", &input);//接收选择菜单的指令
    		switch(input)
    		{ 
    			case 1:
    				game();
    				break;
    			case 0:
    				printf("游戏结束\n");
    				break;
    			default:
    				printf("输入错误，请重新选择！\n");
    				break;
    		}
    
    	} while (input);//判断输入的值  为0则为假结束，非0为真 继续
    	return 0;
    }