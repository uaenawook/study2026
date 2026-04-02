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

//向上调整，是在插入时，把数据插在尾部，把数组调整为大根堆或者小根堆
//void AdjustUp(HPDataType* a, int child)
//{
//	assert(a);
//
//	int parent = (child - 1) / 2;
//	while (child > 0)
//	{
//		if (a[child] > a[parent])
//		{
//			swap(&a[child], &a[parent]);
//			child = parent;
//			parent = (child - 1) / 2;
//		}
//		else
//		{
//			break;
//		}
//	}
//}

//void AdjustDown(HPDataType* a, int size, int parent)
//{
//	//假设左孩子小
//	int child = parent * 2 + 1;
//	//如果孩子<size则说明,还能继续调整
//	while (child < size)
//	{
//		if (a[parent * 2 + 2] < a[child])
//		{
//			child++;
//		}
//		//如果父亲大于孩子则交换，因为是小根堆，让小的当父亲
//		if (a[parent] > a[child])
//		{
//			swap(&a[parent], a[child]);
//			parent = child;
//			child = parent * 2 + 1;
//		}
//		else
//		{
//			//此时父亲比孩子小，则不用调整
//			break;
//		}
//	}
//}