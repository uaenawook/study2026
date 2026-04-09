#include"Sort.h"


//打印数组
void PrintfArr(int* a, int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
}
void swap(int* x, int* y)
{
	int tmp = *x;
	*x = *y;
	*y = tmp;
}

//冒泡排序
void BubbleSort(int* a, int n)
{
	// 比较多少次呢？ 3个数比较2次，2个数比较1次，那n-1个数比较n-1-1次
	for (int j = 0; j < n - 1; j++)
	{
		int flog = 0;
		// 升序：前一个数比当前数大，交换
		// 一趟冒泡把最大的值冒到最后
		for (int i = 1; i < n-j; i++)
		{
			if (a[i - 1] > a[i])
			{
				swap(&a[i - 1], &a[i]);
				flog = 1;
			}
		}
		if (flog == 0)
			break;
	}

}


// 选择排序--一次排序选择一个最小的
void SelectionSort(int* a, int n)
{
	int mini = 0;
	int begin = 0;
	while (begin < n-1)
	{
		for (int i = begin; i < n; i++)
		{
			if (a[i] < a[mini])
			{
				mini = i;
			}
		}
		swap(&a[mini], &a[begin]);
		begin++;
	}

}

// 选择排序--一次排序选择一个最小的，一个最大的
void SelectionSort2(int* a, int n)
{
	int mini = 0;
	int maxi = 0;
	int begin = 0;
	int end = n - 1;
	while (begin < end)
	{
		for (int i = begin; i <= end; i++)
		{
			if (a[i] < a[mini])
			{
				mini = i;
			}
			if (a[i] > a[maxi])
			{
				maxi = i;
			}
		}
		swap(&a[mini], &a[begin]);
		swap(&a[maxi], &a[end]);
		begin++;
		end--;
	}

}