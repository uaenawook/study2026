#include"Stack.h"

// 初始化和销毁
void STInit(ST* pst)
{
	assert(pst);
	pst->arr = NULL;
	pst->top = 0;
	pst->capacity = 0;
}
void STDestroy(ST* pst)
{
	assert(pst);
	free(pst->arr);
	pst->arr = NULL;
	pst->top = 0;
	pst->capacity = 0;
}

// 入栈  出栈
void STPush(ST* pst, STDataType x)
{
	assert(pst);
	if (pst->top == pst->capacity)
	{
		int newCapacity = pst->capacity == 0 ? 4 : pst->capacity * 2;
		STDataType* newNode = (STDataType*)realloc(pst->arr, sizeof(STDataType) * newCapacity);
		if (newNode == NULL)
		{
			printf("STPush realloc fail!");
			exit(-1);
		}

		pst->arr = newNode;
		pst->capacity = newCapacity;
	}
	pst->arr[pst->top] = x;
	pst->top++;

}
void STPop(ST* pst)
{
	assert(pst && pst->top > 0);
	pst->top--;
}

// 取栈顶数据
STDataType STTop(ST* pst)
{
	assert(pst && pst->top > 0);
	return pst->arr[pst->top-1];
}

// 判空
bool STEmpty(ST* pst)
{
	assert(pst);
	return pst->top == 0;
}
// 获取数据个数
int STSize(ST* pst)
{
	assert(pst);
	return pst->top;
}