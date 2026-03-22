#include"SList.h"

void SLTPrint(SLTNode* phead)
{
	SLTNode* cur = phead;
	while (cur)
	{
		printf("%d->", cur->data);
		cur = cur->next;
	}
	printf("NULL\n");
}



SLTNode* SListBuyNode(SLTDataType x)
{
	SLTNode* newNode = (SLTNode*)malloc(sizeof(SLTNode));
	if (newNode == NULL)
	{
		perror("SListMalloc fail!");
		exit(1);//失败返回非0，成功返回0
	}
	newNode->data = x;
	newNode->next = NULL;
	return newNode;
}
//尾插
void SLTPushBack(SLTNode** pphead, SLTDataType x)
{
	assert(pphead);
	if (*pphead == NULL)
	{
		*pphead = SListBuyNode(x);
		return;
	}
	//找尾
	SLTNode* tail = *pphead;
	while (tail->next)
	{
		tail = tail->next;
	}
	//插入
	//申请节点
	tail->next = SListBuyNode(x);
}
//头插
void SLTPushFront(SLTNode** pphead, SLTDataType x)
{
	assert(pphead);
	//保存头
	SLTNode* tmp = *pphead;
	//申请节点
	SLTNode* newNode = SListBuyNode(x);
	//插入头
	*pphead = newNode;
	//恢复连接
	newNode->next = tmp;
}
//尾删
void SLTPopBack(SLTNode** pphead)
{
	//修改的
	assert(pphead && *pphead);
	if ((*pphead)->next == NULL)
	{
		free(*pphead);
		*pphead = NULL;
	}
	else
	{
		//找尾和尾之前的节点
		SLTNode* cur;
		SLTNode* tail;
		cur = tail = *pphead;
		while (tail->next)
		{
			cur = tail;
			tail = tail->next;
		}
		//释放节点
		free(tail);
		cur->next = NULL;
	}


	//我写的
	//assert(pphead);
	//if (*pphead == NULL)
	//{
	//	printf("节点已清空！\n");
	//	return;
	//}
	////找尾和尾之前的节点
	//SLTNode* cur;
	//SLTNode* tail;
	//cur = tail = *pphead;
	//while (tail->next)
	//{
	//	cur = tail;
	//	tail = tail->next;
	//}
	////释放节点
	//free(tail);
	//cur->next = NULL;
	//if (cur == *pphead)
	//{
	//	*pphead = NULL;
	//}

}
//头删
void SLTPopFront(SLTNode** pphead)
{
	assert(pphead && *pphead);
	if ((*pphead)->next == NULL)
	{
		free(*pphead);
		*pphead = NULL;
	}
	else
	{
		SLTNode* next = (*pphead)->next;
		free(*pphead);
		*pphead = next;
	}
}



//查找
SLTNode* SLTFind(SLTNode* phead, SLTDataType x)
{
	assert(phead);

	SLTNode* cur = phead;
	while (cur)
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
	printf("没找到！\n");
	return NULL;
}

//在指定位置之前插入数据
void SLTInsert(SLTNode** pphead, SLTNode* pos, SLTDataType x)
{
	assert(*pphead && pos);
	if (*pphead == pos)
	{
		SLTPushFront(pphead,x);
		return;
	}
	//遍历找到pos的前一个节点
	SLTNode* prev = *pphead;
	while(prev->next != pos)
	{
		prev = prev->next;
	}

	//插入数据
	SLTNode* newNode = SListBuyNode(x);
	newNode->next = pos;
	prev->next = newNode;
}
//在指定位置之后插入数据
void SLTInsertAfter(SLTNode* pos, SLTDataType x)
{
	assert(pos);
	SLTNode* newNode = SListBuyNode(x);
	newNode->next = pos->next;
	pos->next = newNode;
}

//删除pos节点
void SLTErase(SLTNode** pphead, SLTNode* pos)
{
	if (*pphead == pos)
	{
		*pphead = pos->next;
		free(pos);
		pos = NULL;
		return;
	}
	assert(pphead&&pos);
	//遍历找到pos的前一个节点
	SLTNode* prev = *pphead;
	while (prev->next != pos)
	{
		prev = prev->next;
	}
	//删除pos
	prev->next = pos->next;
	free(pos);
	pos = NULL;

}
//删除pos之后的节点
void SLTEraseAfter(SLTNode* pos)
{
	assert(pos && pos->next);
	SLTNode* next = pos->next;
	pos = next->next;
	free(next);
	next = NULL;
}

//销毁链表
void SListDesTroy(SLTNode** pphead)
{
	//调用删除:可能造成额外开销，如果链表有 10 万个节点，就会产生 10 万次函数调用（压栈、退栈）的开销。
	//while (*pphead)
	//{
	//	SLTPopFront(pphead);
	//}

	//直接循环删除\写的可以但不咋地
	//assert(*pphead);
	//SLTNode* cur = *pphead;
	//while (cur)
	//{
	//	*pphead = cur->next;
	//	free(cur);
	//	cur = *pphead;
	//}
	//*pphead = NULL;

	//标准写法
	assert(pphead);
	SLTNode* cur = *pphead;
	while (cur)
	{
		SLTNode* next = cur->next;
		free(cur);
		cur = next;
	}
	*pphead = NULL;
}