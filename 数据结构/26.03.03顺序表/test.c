#include "SeqList.h"
#include "Contact.h"



//void sltest01()
//{
//	SL sl;
//	SLInit(&sl);
//	SLPushBack(&sl,1);
//	SLPushBack(&sl,2);
//	SLPushBack(&sl,3);
//	SLPushBack(&sl,4);
//	SLPushBack(&sl,5);
//
//	//SLPushFront(&sl, 1);
//	//SLPushFront(&sl, 2);
//	//SLPushFront(&sl, 3);
//	//SLPushFront(&sl, 4);
//	//SLPushFront(&sl, 5);
//	SLPrint(sl);
//
//	//SLInsert(&sl,5, 10);
//
//	SLErase(&sl, 0);
//	SLErase(&sl, 0);
//	SLErase(&sl, 0);
//	SLErase(&sl, 0);
//
//	SLPrint(sl);
//	int find = 5;
//	printf("%d的下标是%d\n", find,SLFind(&sl, find));
//
//
//}


void Contact01()
{
	Contact Con;
	ContactInit(&Con);

	ContactPush(&Con);
	ContactPush(&Con);
	//ContactPush(&Con);
	ContactFind(&Con);

	ContactDestroy(&Con);
}

void menu()
{
	printf("*****************************************\n");
	printf("*******1.增加联系人    2.修改联系人******\n");
	printf("*******3.查找联系人    4.删除联系人******\n");
	printf("*******5.展示联系人    0.退出     ******\n");
	printf("*****************************************\n");
	return;
}
int main()
{
	int i = -1;
	Contact Con;
	ContactInit(&Con);

	do {
		menu();
		printf("选择您的操作:\n");
		scanf("%d", &i);
		
		switch (i)
		{
		case 0:
			printf("成功退出！\n");
			break;
		case 1:
			ContactPush(&Con);
			break;
		case 2:
			ContactModify(&Con);
			break;
		case 3:
			ContactFind(&Con);
			break;
		case 4:
			ContactPop(&Con);
			break;
		case 5:
			ContactShow(&Con);
			break;
		default:
			printf("输入错误，重新输入！\n");
			break;
		}
	} while (i);

	ContactDestroy(&Con);

	return 0;
}