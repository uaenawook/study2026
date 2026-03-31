#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>


typedef int HPDataType;

typedef struct Heap
{
	HPDataType* a;
	int size;
	int capacity;
}HP;



//初始化
void HPInit(HP* php);
//销毁
void HPDestroy(HP* php);

void AdjustUp(HPDataType* a,int child);

void AdjustDown(HPDataType* a, int n, int parent);

//插入
void HPPush(HP* php, HPDataType x);
//删除
void HPPop(HP* php);

//取数据
HPDataType HPTop(HP* php);
//判空
bool HPEmpty(HP* php);
