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
void SelectionSort2(int* a, int n)// 有问题，需重写
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


//插入排序
void InsertionSort(int* a, int n)
{
	// 遍历一遍数组，从下标1开始，跟前一个比较
	// 记录i的值为tmp，cur = i;
	// 用cur向前遍历比较，前一个值比cur大，则让cur的值cur-1的值，cur--;
	// 否则跳出循环
	// 把tmp的值插入到cur的位置
	// i继续往下走

	
	for (int i = 1; i < n; i++)		//遍历数组，因为当前值与前一个比较，所以从1遍历到n-1
	{
		int tmp = a[i];
		int cur = i;
		while (cur > 0)				// cur跟前一个比，cur最后一次比较必须是1，前一个是0
		{
			if (a[cur-1] > tmp)		// 如果前一个比tmp大，则让这个值往后移动
			{
				a[cur] = a[cur-1];
				cur--;
			}
			else					//否则就是找到了比tmp小的值
			{
				break;
			}
		}
		a[cur] = tmp;				// cur的前一个比tmp小，当前值又被挪到了后面，tmp插入在这
	}
}

//希尔排序-在第一次基础上修改
void ShellSort(int* a, int n)
{
	int gap = n;
	while(gap>1)
	{
		gap = gap / 3 + 1;
		for (int i = gap; i < n; i++)
		{
			int tmp = a[i];
			int cur = i;
			while (cur >=gap && a[cur - gap] > tmp)
			{
				a[cur] = a[cur - gap];
				cur -= gap;
			}
			a[cur] = tmp;
		}
	}
}

//希尔排序 - 第一次写
void ShellSort1(int* a, int n)
{
	for (int gap = n/3+1; gap > 0; (gap/=3)+1)
	{
		for (int i = gap; i < n; i++)
		{
			int tmp = a[i];
			int cur = i;
			while (cur > 0 && cur-gap>=0)
			{
				if (a[cur - gap] > tmp)
				{
					a[cur] = a[cur - gap];
					cur-=gap;
				}
				else
				{
					break;
				}
			}
			a[cur] = tmp;
		}
	}
}


// 快速排序-升序
// 遇到的问题-找大小的时候必须判断=，让等于key的值留在原地，不然左右都找到==key，进行交换会死循环
void QuickSort(int* a, int left, int right)
{
	// 递归返回条件
	if (left >= right)
		return;
	// 左边做k，右边先走
	int key = left;
	int l = left;
	int r = right;
	while (l < r)
	{
		// 右边找比key小
		while(l < r && a[r] > a[key])
		{
				r--;
		}

		// 左边找大
		while (l < r && a[l] < a[key])
		{
				l++;
		}

		//找到了交换
		swap(&a[l], &a[r]);

	}

	// 一趟走完，交换key
	swap(&a[key], &a[l]);
	key = l;
	QuickSort(a, left, key - 1);
	QuickSort(a, key+1,right);
}