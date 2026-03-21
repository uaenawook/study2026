#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>


//定义结构体
typedef int LTDataType;

typedef struct ListNode
{
	LTDataType data;
	struct ListNode* prev;
	struct ListNode* next;
}LTNode;



//声明双向链表中提供的方法

//初始化
//void LTInit(LTNode** pphead);
LTNode* LTInit();
void LTDesTroy(LTNode* phead);

void LTPrint(LTNode* phead);

//插入数据之前，链表必须初始化到只有一个头结点的情况
//不改变哨兵位的地址，因此传一级即可
//尾插
void LTPushBack(LTNode* phead, LTDataType x);
//头插
void LTPushFront(LTNode* phead, LTDataType x);

//尾删
void LTPopBack(LTNode* phead);
//头删
void LTPopFront(LTNode* phead);


//在pos位置之后插入数据
void LTInsert(LTNode* pos, LTDataType x);
//删除pos节点
void LTErase(LTNode* pos);
LTNode* LTFind(LTNode* phead, LTDataType x);