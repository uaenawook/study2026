#include"HeapSort.h"

void HeapInit(Heap* php)
{
	assert(php);

	php->a = NULL;
	php->size = php->capacity = 0;
}
void HeapDestroy(Heap* php)
{
	assert(php);

	free(php->a);
	php->a = NULL;
	php->size = php->capacity = 0;
}
void swap(HSDataType* x, HSDataType* y)
{
	HSDataType tmp = *x;
	*x = *y;
	*y = tmp;
}

void AdjustUp(HSDataType* a, int child)
{

	//假设建大堆
	//先计算parent
	int parent = (child - 1) / 2;
	//比较交换，主页判断结束条件 1. 到顶了。 2. 父亲比孩子小
	while (child>0)
	{
		// 比较交换
		if (a[parent] < a[child])
		{
			swap(&a[parent], &a[child]);
			child = parent;
			parent = (child - 1) / 2;
		}
		else
		{
			break;
		}
	}
}

void HeapPush(Heap* php, HSDataType x)
{
	assert(php);
	//插入
	//判断数组空间大小
	if (php->size == php->capacity)
	{
		int newCapacity = php->capacity == 0 ? 4 : php->capacity * 2;
		HSDataType* newA = (HSDataType*)realloc(php->a, sizeof(HSDataType) * newCapacity);
		if (newA == NULL)
		{
			perror("realloc fail!\n");
			exit(-1);
		}
		php->capacity = newCapacity;
		php->a = newA;
	}
	php->a[php->size] = x;
	php->size++;
	//调整
	AdjustUp(php->a, php->size - 1);

}
void AdjustDown(HSDataType* a, int n, int parent)
{


	//大根堆，保持堆顶是最大值
	//找出大的孩子交换
	int child = parent * 2 + 1;
	//调整，结束条件1.孩子比父亲小。 2. 调到底了
	while (child < n)
	{
		//必须判断有没有 右孩子，如没有右孩子则a[child+1]会越界访问
		if (child + 1 < n && a[child + 1] > a[child])
			child++;

		//交换
		if (a[child] > a[parent])
		{
			swap(&a[child], &a[parent]);
			parent = child;
			child = parent * 2 + 1;
		}
		else
		{
			break;
		}
	}
}

void HeapPop(Heap* php)
{
	assert(php);
	assert(php->size > 0);

	// 删除
	// 先交换首尾
	swap(&php->a[php->size-1], &php->a[0]);
	php->size--;


	// 调整
	AdjustDown(php->a, php->size, 0);
}

void HeapCreate(Heap* hp, HSDataType* a, int n)
{
	//for (int i = 0; i < n; i++)
	//{
	//	HeapPush(hp, a[i]);
	//}
	assert(hp&&a);
	assert(hp->a == NULL && hp->size == 0 && hp->capacity == 0);

	HSDataType* newNode = (HSDataType*)malloc(sizeof(HSDataType)*n);
	if (newNode == NULL)
	{
		perror("malloc fail!\n");
		exit(-1);
	}
	hp->a = newNode;
	memcpy(hp->a, a,sizeof(HSDataType)*n);
	hp->size = hp->capacity = n;

	int parent = (n - 1 - 1) / 2;
	for (int i = parent; i >= 0; i--)
	{
		AdjustDown(hp->a, hp->size,i);

	}
}

HSDataType HeapTop(Heap* php)
{
	assert(php);

	return php->a[0];
}
int HeapSize(Heap* php)
{
	assert(php);

	return php->size;
}
int HeapEmpty(Heap* php)
{
	return !php->size;
}
//堆排序
void HeapSort(int* a, int n)
{
	//建堆
	for (int i = (n - 1 - 1) / 2; i >= 0; i--)
	{
		AdjustDown(a, n, i);
	}

	//排序
	for (int i = n - 1; i > 0; i--)
	{
		swap(&a[0], &a[i]);
		AdjustDown(a, i, 0);
	}
}