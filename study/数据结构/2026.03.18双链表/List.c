
#include"List.h"

//声明双向链表中提供的方法
//双链表接口实现



LTNode* LTBuyNode(LTDataType x)
{
	LTNode* newNode = (LTNode*)malloc(sizeof(LTNode));
	if (newNode == NULL)
	{
		perror("LTBuyNode fail!");
		exit(1);
	}
	newNode->data = x;
	newNode->next = newNode->prev = newNode;

	return newNode;
}
//初始化
void LTInit(LTNode** pphead)
{
	*pphead = LTBuyNode(0);
	(*pphead)->prev = *pphead;
	(*pphead)->next = *pphead;
}
LTNode* LTInit2()
{
	LTNode* newNode = LTBuyNode(0);
	newNode->prev = newNode;
	newNode->next = newNode;
	return newNode;
}
void LTDesTroy(LTNode* phead)
{
	LTNode* cur = phead->next;
	while (cur != phead)
	{
		LTNode* next = cur->next;
		free(cur);
		cur = next;
	}
	free(phead);
	phead = NULL;
}

void LTPrint(LTNode* phead)
{
	LTNode* cur = phead->next;
	while (cur != phead)
	{
		printf("%d->", cur->data);
		cur = cur->next;
	}
	printf("NULL\n");
}

//插入数据之前，链表必须初始化到只有一个头结点的情况
//不改变哨兵位的地址，因此传一级即可
//尾插
void LTPushBack(LTNode* phead, LTDataType x)
{
	//双向循环链表
	//  prev  phead  next
	assert(phead);
	LTNode* newNode = LTBuyNode(x);//新节点
	newNode->prev = phead->prev;
	newNode->next = phead;

	phead->prev->next = newNode;
	phead->prev = newNode;

}
//头插
void LTPushFront(LTNode* phead, LTDataType x)
{
	assert(phead);
	LTNode* newNode = LTBuyNode(x);
	newNode->prev = phead;
	newNode->next = phead->next;

	phead->next->prev = newNode;
	phead->next = newNode;
}

//尾删
void LTPopBack(LTNode* phead)
{

	assert(phead && phead->next != phead);

	LTNode* tail = phead->prev;
	phead->prev = tail->prev;
	tail->prev->next = phead;

	free(tail);
	tail = NULL;
}
//头删
void LTPopFront(LTNode* phead)
{
	assert(phead && phead->next != phead);

	LTNode* first = phead->next;
	phead->next = first->next;
	first->next->prev = phead;

	free(first);
	first = NULL;
}


//在pos位置之后插入数据
void LTInsert(LTNode* pos, LTDataType x)
{
	assert(pos);
	LTNode* newNode = LTBuyNode(x);
	newNode->prev = pos;
	newNode->next = pos->next;

	pos->next->prev = newNode;
	pos->next = newNode;
}
//删除pos节点
void LTErase(LTNode* pos)
{
	assert(pos);
	pos->prev->next = pos->next;
	pos->next->prev = pos->prev;

	free(pos);
	pos = NULL;
}
LTNode* LTFind(LTNode* phead, LTDataType x)
{
	assert(phead);
	LTNode* cur = phead->next;
	while (cur != phead)
	{
		if (cur->data == x)
		{
			return cur;
		}
		else
		{
			cur = cur->next;
		}
	}
	return NULL;

}