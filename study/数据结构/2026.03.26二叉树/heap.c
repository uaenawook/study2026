#include"Heap.h"



//初始化
void HPInit(HP* php)
{
	assert(php);
	php->a = NULL;
	php->size = php->capacity = 0;
}
//销毁
void HPDestroy(HP* php)
{
	assert(php);
	free(php->a);
	php->a = NULL;
	php->size = php->capacity = 0;

}
void swap(HPDataType* x, HPDataType* y)
{
	HPDataType tmp = *x;
	*x = *y;
	*y = tmp;
}
//向下调整12

void AdjustUp(HPDataType* a, int child)
{
	//child 为size的前一个，size 是尾元素的下一个，
	int parent = (child - 1) / 2;
	while (child > 0)
	{
		if (a[child] < a[parent])
		{
			swap(&a[child], &a[parent]);
			child = parent;
			parent = (child - 1) / 2;
		}
		else
		{
			break;
		}

	}
}

//重写的第二遍
void AdjustUp1(HPDataType* a, int child)
{
	assert(a);

	int parent = (child - 1) / 2;
	while (child > 0)
	{
		if (a[child] < a[parent])
		{
			swap(&a[child], &a[parent]);
			child = parent;
			parent = (child - 1) / 2;
		}
		else
		{
			break;
		}
	}
}
//插入
void HPPush(HP* php, HPDataType x)
{
	//不完整 继续补充
	assert(php);

	if (php->size == php->capacity)
	{
		int newCapacity = php->capacity == 0 ? 4 : php->capacity * 2;
		HPDataType* newNode = (HPDataType*)realloc(php->a, newCapacity * sizeof(HPDataType));
		if (newNode == NULL)
		{
			perror("ralloc fail!\n");
			exit(-1);
		}
		php->a = newNode;
		php->capacity = newCapacity;
	}
	php->a[php->size] = x;
	php->size++;

	//插入后调整，假设向上调整为小根堆
	AdjustUp1(php->a , php->size - 1);
}
//向下调整
void AdjustDown(HPDataType* a, int n, int parent)
{
	//向下调整，小根堆，把小的往上调
	//假设左孩子小
	int child = parent * 2 + 1;
	while (child<n)
	{
		if (child + 1 < n && a[child + 1] < a[child])
		{
			child++;
		}

		if (a[child] < a[parent])
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

void AdjustDown2(HPDataType* a, int size, int parent)
{
	//假设左孩子小
	int child = parent * 2 + 1;
	//如果孩子<size则说明,还能继续调整
	while (child < size)
	{
		if (child + 1 < size && a[child+1] < a[child])
		{
			child++;
		}
		//如果父亲大于孩子则交换，因为是小根堆，让小的当父亲
		if (a[parent] > a[child])
		{
			swap(&a[parent], &a[child]);
			parent = child;
			child = parent * 2 + 1;
		}
		else
		{
			//此时父亲比孩子小，则不用调整
			break;
		}
	}
}
//删除
void HPPop(HP* php)
{
	assert(php);
	assert(php->size>0);

	//先把要删除的节点交换到最后，再向下调整堆
	swap(&php->a[0], &php->a[php->size - 1]);
	php->size--;

	AdjustDown2(php->a, php->size, 0);


}

//取数据
HPDataType HPTop(HP* php)
{
	assert(php);
	assert(php->size > 0);
	return php->a[0];
}
//判空
bool HPEmpty(HP* php)
{
	assert(php);
	return php->size == 0;

}