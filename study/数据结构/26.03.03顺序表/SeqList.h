#pragma once

#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Contact.h"

//静态顺序表
#define N 100
struct seqlist
{
	int arr[N];
	int size;
};

//动态顺序表
//#define SLDateType int //不能这样写，因为：
						//#define SLDateType int*
						//SLDateType p1, p2; // 替换后变成 int* p1, p2; 结果：p1是指针，p2是整数
						// 
						//typedef int* SLDateType;
						//SLDateType p1, p2; // p1和p2都是指针
//typedef int SLDataType;
typedef struct personInfo SLDataType;

typedef struct SeqList
{
	SLDataType* arr;
	int size;
	int capacity;
}SL;


//顺序表初始化
void SLInit(SL* ps);
//顺序表的销毁
void SLDestroy(SL* ps);
//顺序表的打印
void SLPrint(SL s);

//头部插入删除 / 尾部插入删除
void SLPushBack(SL* ps, SLDataType x);
void SLPushFront(SL* ps, SLDataType x);

void SLPopBack(SL* ps);
void SLPopFront(SL* ps);

//指定位置之前插入/删除数据
void SLInsert(SL* ps, int pos, SLDataType x);
void SLErase(SL* ps, int pos);
int SLFind(SL* ps, SLDataType x);

