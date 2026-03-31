#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>

typedef int QDataType;


//单链表实现队列
typedef struct QueueNode
{
	struct QueueNode* next;
	QDataType val;
}QNode;

typedef struct Queue
{
	QNode* phead;
	QNode* tail;
	int size;
}Queue;

//初始化

void QueueInit(Queue* pq);
//销毁
void QueueDestroy(Queue* pq);

//插入
void QueuePush(Queue* pq,QDataType x);
//删除
void QueuePop(Queue* pq);

//取数据
QDataType QueueFront(Queue* pq);
QDataType QueueBack(Queue* pq);

//判空
bool QueueEmpty(Queue* pq);
//数据个数
int QueueSize(Queue* pq);

