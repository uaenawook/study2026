#include"Queue.h"

//初始化

void QueueInit(Queue* pq)
{
	assert(pq);
	pq->phead = pq->size = NULL;
	pq->size = 0;
}


//插入
void QueuePush(Queue* pq, QDataType x)
{
	QNode* newNode = (QNode*)malloc(sizeof(QNode));
	if (newNode == NULL)
	{
		perror("QueuePush Node fail");
		exit(-1);
	}
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
		Queue* cur = pq->phead;
		pq->phead = pq->phead->next;
		free(cur);
	}
	pq->size--;
}

//取数据
QDataType QueueFront(Queue* pq)
{
	assert(pq && pq->size > 0);

	return pq->phead->val;
}
QDataType QueueBack(Queue* pq);

//判空
bool QueueEmpty(Queue* pq);
//
void QueueSize(Queue* pq);


//销毁
void QueueDestroy(Queue* pq)
{

}