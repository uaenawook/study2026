//2026.03.08单链表做题

//2026.03.09单链表看课

//2026.03.10单链表实现


#include"SList.h"

//void SListTest()
//{
//	SLTNode* newNode4 = (SLTNode*)malloc(sizeof(SLTNode));
//	newNode4->data = 4;
//	newNode4->next = NULL;
//
//	SLTNode* newNode3 = (SLTNode*)malloc(sizeof(SLTNode));
//	newNode3->data = 3;
//	newNode3->next = newNode4;
//
//	SLTNode* newNode2 = (SLTNode*)malloc(sizeof(SLTNode));
//	newNode2->data = 2;
//	newNode2->next = newNode3;
//
//	SLTNode* newNode1 = (SLTNode*)malloc(sizeof(SLTNode));
//	newNode1->data = 1;
//	newNode1->next = newNode2;
//
//	SLTNode* phead;
//	phead = newNode1;
//
//	SLTPrint(phead);
//}

//void SListTest2()
//{
//	SLTNode* phead = NULL;
//	//尾插
//	SLTPushBack(&phead,1);
//	SLTPushBack(&phead,2);
//	SLTPushBack(&phead,3);
//	SLTPushBack(&phead,4);
//	SLTPrint(phead);
//	
//	//头插
//	//SLTPushFront(&phead, 5);
//	//SLTPushFront(&phead, 6);
//	//SLTPushFront(&phead, 7);
//	//SLTPushFront(&phead, 8);
//	SLTPrint(phead);
//
//	//尾删
//	//SLTPopBack(&phead);
//	//SLTPopBack(&phead);
//	////SLTPopBack(&phead);
//	////SLTPopBack(&phead);
//	//SLTPrint(phead);
//
//	//头删
//	SLTPopFront(&phead);
//	SLTPopFront(&phead);
//	SLTPopFront(&phead);
//	SLTPopFront(&phead);
//
//	SLTPrint(phead);
//
//
//	//头插
//	SLTPushFront(&phead, 5);
//	SLTPushFront(&phead, 6);
//	SLTPushFront(&phead, 7);
//	SLTPushFront(&phead, 8);
//	SLTPrint(phead);
//
//	//尾插
//	SLTPushBack(&phead, 1);
//	SLTPushBack(&phead, 2);
//	SLTPushBack(&phead, 3);
//	SLTPushBack(&phead, 4);
//	SLTPrint(phead);
//}



void SListTest3()
{
	SLTNode* phead = NULL;
	//尾插
	SLTPushBack(&phead,1);
	SLTPushBack(&phead,2);
	SLTPushBack(&phead,3);
	SLTPushBack(&phead,4);
	SLTPrint(phead);

	SLTNode* find = SLTFind(phead, 1);
	if(find != NULL)
		printf("%d\n", find->data);

	//SLTInsert(&phead,find,99);
	//SLTPrint(phead);

	//SLTInsertAfter(find, 99);
	//SLTPrint(phead);

	SLTErase(&phead,find);


	SLTPrint(phead);

	SListDesTroy(&phead);
}

int main()
{
	//SListTest();
	//SListTest2();
	SListTest3();
	return 0;
}