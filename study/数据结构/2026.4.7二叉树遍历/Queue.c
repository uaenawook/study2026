#include"Queue.h"

//初始化

void QueueInit(Queue* pq)
{
	assert(pq);
	pq->phead = pq->tail = NULL;
	pq->size = 0;
}


//插入
void QueuePush(Queue* pq, QDataType x)
{
	assert(pq);
	QNode* newNode = (QNode*)malloc(sizeof(QNode));
	if (newNode == NULL)
	{
		perror("QueuePush Node fail");
		exit(-1);
	}
	newNode->next = NULL;
	newNode->val = x;
	if (pq->tail == NULL)
	{
		pq->phead = pq->tail = newNode;
	}
	else
	{
		pq->tail->next = newNode;
		pq->tail = newNode;
	}
	pq->size++;
}
//删除
void QueuePop(Queue* pq)
{
	assert(pq && pq->size > 0);
	//取头部数据free
	if (pq->phead == pq->tail)
	{
		free(pq->tail);
		pq->phead = pq->tail = NULL;
	}
	else
	{
		QNode* next = pq->phead->next;
		free(pq->phead);
		pq->phead = next;
	}
	pq->size--;
}

//取数据
QDataType QueueFront(Queue* pq)
{
	assert(pq && pq->phead);

	return pq->phead->val;
}
QDataType QueueBack(Queue* pq)
{
	assert(pq && pq->tail);
	return pq->tail->val;
}

//判空
bool QueueEmpty(Queue* pq)
{
	assert(pq);
	return pq->size == 0;
}
//
int QueueSize(Queue* pq)
{
	assert(pq);
	return pq->size;
}


//销毁
void QueueDestroy(Queue* pq)
{
	QNode* cur = pq->phead;
	//先销毁节点
	while (cur)
	{
		QNode* next = cur->next;
		free(cur);
		cur = next;
	}
	//再销毁指针结构体
	pq->phead = pq->tail = NULL;
	pq->size = 0;

}