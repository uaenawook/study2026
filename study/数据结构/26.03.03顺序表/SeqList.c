#include "SeqList.h"

//顺序表初始化
void SLInit(SL* ps)
{
	ps->arr = NULL;
	ps->size = ps->capacity = 0;
}

//顺序表的销毁
void SLDestroy(SL* ps)
{
	if (ps->arr)
	{
		free(ps->arr);
	}
	ps->arr = NULL;
	ps->size = ps->capacity = 0;
}

////顺序表的打印
//void SLPrint(SL s)
//{
//	if (s.size == 0)
//	{
//		printf("链表无数据\n");
//	}
//	for (int i = 0; i < s.size; i++)
//	{
//		printf("%d ",s.arr[i]);
//	}
//	printf("\n");
//}

//检擦扩容
void SLCheckCapacity(SL* ps)
{
	//检查空间是否需要扩容
	if (ps->size == ps->capacity)
	{
		int NewCapacity = ps->capacity == 0 ? 4 : 2 * ps->capacity;
		//扩容
		SLDataType* tmp = realloc(ps->arr, NewCapacity * sizeof(SLDataType));
		if (tmp == NULL)
		{
			perror("realloc x");
			exit(1);
		}
		ps->arr = tmp;
		ps->capacity = NewCapacity;
	}
}
//尾插
void SLPushBack(SL* ps, SLDataType x)
{
	assert(ps);
	//检查空间是否需要扩容
	SLCheckCapacity(ps);

	ps->arr[ps->size] = x;
	ps->size++;
	
}
//头插
void SLPushFront(SL* ps, SLDataType x)
{
	assert(ps);
	//检查空间是否需要扩容
	SLCheckCapacity(ps);
	//挪动数据
	for (int i = ps->size; i > 0; i--)
	{
		ps->arr[i] = ps->arr[i - 1];
	}
	//头插数据
	ps->arr[0] = x;
	ps->size++;
}

//尾删
void SLPopBack(SL* ps)
{
	assert(ps);
	assert(ps->size);
	//if (ps->size == 0)
	//	return;
	ps->size--;
}


//头删
void SLPopFront(SL* ps)
{
	assert(ps);
	assert(ps->size);

	for (int i = 0; i < ps->size - 1; i++)
	{
		ps->arr[i] = ps->arr[i + 1];
	}
	ps->size--;
}


//指定位置之前插入/删除数据
void SLInsert(SL* ps, int pos, SLDataType x)
{
	assert(ps);
	assert(pos>=0 && pos<=ps->size);
	//检查空间是否需要扩容
	SLCheckCapacity(ps);
	for (int i = ps->size; i > pos; i--)
	{
		ps->arr[i] = ps->arr[i - 1];
	}
	ps->arr[pos] = x;
	ps->size++;
}
void SLErase(SL* ps, int pos)
{
	assert(ps);
	assert(pos >= 0 && pos<= ps->size);
	for (int i = pos; i < ps->size-1; i++)
	{
		ps->arr[i] = ps->arr[i + 1];
	}
	ps->size--;
}
//int SLFind(SL* ps, SLDataType x)
//{
//	assert(ps);
//
//	for (int i = 0; i < ps->size; i++)
//	{
//		if (ps->arr[i] == x)
//		{
//			return i;
//		}
//	}
//	printf("没找到！\n");
//}
