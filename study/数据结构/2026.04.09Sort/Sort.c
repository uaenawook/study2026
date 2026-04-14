#include"Sort.h"
#include"Stack.h"

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



// 向下调整
void AdjustDown(int* a, int n, int parent)
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

// 三数取中
int GetMidi(int* a, int left, int right)
{
	int midi = (left + right) / 2;
	if (a[left] < a[midi] && a[midi] < a[right])
		return midi;
	else if (a[left] > a[midi] && a[midi] > a[right])
		return midi;
	else if (a[midi] < a[right] && a[right] < a[left])
		return right;
	else if (a[midi] > a[right] && a[right] > a[left])
		return right;
	else
		return left;

	//int midi = (left + right) / 2;
	//if (a[left] < a[midi])
	//{
	//	if (a[midi] < a[right])
	//		return midi;
	//	else if (a[right] > a[left])
	//		return right;
	//	else
	//		return left;
	//}
	//else //a[left] >= a[midi]
	//{
	//	if (a[midi] > a[right])
	//		return midi;
	//	else if (a[left] < a[right])
	//		return left;
	//	else
	//		return right;
	//}
}


int PartSort1(int* a, int left, int right)
{
	//三数取中
	int midi = GetMidi(a, left, right);
	swap(&a[left], &a[midi]);

	// 左边做k，右边先走
	int keyi = left;
	//int keyi = left;
	int begin = left;
	int end = right;
	while (begin < end)
	{
		// 右边找比key小
		while (begin < end && a[end] >= a[keyi])
		{
			end--;
		}

		// 左边找大
		while (begin < end && a[begin] <= a[keyi])
		{
			begin++;
		}

		//找到了交换
		swap(&a[begin], &a[end]);

	}

	// 一趟走完，交换key
	swap(&a[keyi], &a[begin]);
	keyi = begin;

	return keyi;
}

int PartSort2(int* a, int left, int right)
{

	//三数取中
	int midi = GetMidi(a, left, right);
	swap(&a[left], &a[midi]);

	int keyi = left;
	int prev = left, cur = prev+1;
	while (cur <= right)
	{
		// 为了防止自己和自己交换
		if (a[cur] < a[keyi]&& ++prev != cur )
			swap(&a[prev], &a[cur]);
		cur++;
		// 正常版本
		/*if (a[cur] < a[keyi])
			swap(&a[++prev], &a[cur]);
		cur++;*/
	}
	swap(&a[keyi], &a[prev]);
	keyi = prev;
	return keyi;
}
// 快速排序-升序
// 遇到的问题-找大小的时候必须判断=，让等于key的值留在原地，不然左右都找到==key，进行交换会死循环
void QuickSort(int* a, int left, int right)
{
	// 递归返回条件
	if (left >= right)
		return;
	//小区间优化
	if ((right - left + 1) < 10)
	{
		InsertionSort(a + left, right -left + 1);
	}
	else
	{
		int keyi = PartSort1(a, left, right);
		QuickSort(a, left, keyi - 1);
		QuickSort(a, keyi + 1, right);
	}

}

// 快排非递归
void QuickSortNonR(int* a, int left, int right)
{
	//用栈实现非递归，入左右下标，需要交换时取出，交换完算出新的区间入栈，栈为空则结束
	ST st;
	STInit(&st);
	STPush(&st, right); // 先入右再入左，取的时候先取到左
	STPush(&st, left);

	while (!STEmpty(&st))
	{

		int begin = STTop(&st);
		STPop(&st);

		int end = STTop(&st);
		STPop(&st);


		int keyi = PartSort1(a, begin, end);

		//[begin1,keyi-1] keyi [keyi+1,end1]
		// 先入有区间，和右区间的右值
		if ((end - keyi) > 1)
		{
			STPush(&st, end);
			STPush(&st, keyi + 1);
		}
		if ((keyi - begin) > 1)
		{
			STPush(&st, keyi - 1);
			STPush(&st, begin);
		}
	}

	

	STDestroy(&st);

}

// 比较大小
void compare(int* a, int* b)
{
	if (*a > *b)
	{
		swap(a, b);
	}
}

void _MergeSort(int* a,int*newArr, int left,int right)
{
	// 归并最小条件
	if (left >= right)
		return;
	//if (left + 1 == right)
	//{
	//	compare(&a[left], &a[right]);
	//	return;
	//}

	// 分割
	int midi = (left + right) / 2;
	//[left,midi][midi,right]
	_MergeSort(a, newArr, left, midi);
	_MergeSort(a, newArr, midi+1,right);

	//归并
	int j = left; // newArr的下标
	int i1 = left;
	int i2 = midi + 1;
	while (i1 <= midi && i2 <= right)
	{
		if (a[i1] <= a[i2])
		{
			newArr[j++] = a[i1++];
		}
		else
		{
			newArr[j++] = a[i2++];
		}
	}
	while (i1 <= midi)
	{
		newArr[j++] = a[i1++];
	}
	while (i2 <= right)
	{
		newArr[j++] = a[i2++];
	}

	// 覆盖回原数组
	while (j-- > left)
	{
		a[j] = newArr[j];
	}
}

// 归并排序
void MergeSort(int* a, int n)
{
	int* newArr = (int*)malloc(sizeof(int) * n);
	if (newArr == NULL)
	{
		perror("malloc fail!\n");
		exit(-1);
	}
	_MergeSort(a, newArr, 0, n - 1);

	free(newArr);
	newArr = NULL;
}

// 归并排序非递归
void MergeSortNonR(int* a, int n)
{
	int* tmp = (int*)malloc(sizeof(int) * n);

	// 归并
	int gap = 1;
	while(gap < n)
	{
		for (int i = 0; i < n; i += gap * 2)
		{
			int begin1 = i;
			int end1 = i + gap - 1;
			int begin2 = i + gap;
			int end2 = i + gap * 2 - 1;
			//printf("[%d,%d][%d,%d] ", begin1, end1, begin2, end2);
			int j = i;
			if (begin2 >= n)
				break;

			if (end2 >= n)
				end2 = n-1;

			while (begin1 <= end1 && begin2 <= end2)
			{
				if (a[begin1] <= a[begin2])
				{
					tmp[j++] = a[begin1++];
				}
				else
				{
					tmp[j++] = a[begin2++];
				}
			}
			while (begin1 <= end1)
			{
				tmp[j++] = a[begin1++];
			}
			while (begin2 <= end2)
			{
				tmp[j++] = a[begin2++];
			}

			//// gap = 1
			//if (a[i] > a[i + 1])
			//{
			//	tmp[i] = a[i+1];
			//	tmp[i + 1] = a[i];
			//}
			//memcpy(a + i, tmp + i, sizeof(int) * (end2 - i + 1));
			// 覆盖原数组
			int k = i;
			while (k <= end2)
			{
				a[k] = tmp[k++];
			}
		}
		//printf("\n");

		gap *=2 ;
	}

}

// 计数排序
void CountSort(int*a, int n)
{
	int n1 = n;
	int max = a[0];
	int min = a[0];
	while (n1--)
	{
		if (a[n1] > max)
			max = a[n1];
		if (a[n1] < min)
			min = a[n1];
	}
	//max = max + 1;
	int tmpN = max - min + 1;
	printf("数组大小：%d\n", tmpN);
	int* tmp = (int*)calloc(tmpN, sizeof(int));
	if (tmp == NULL)
	{
		perror("clloc fail\n");
		exit(-1);
	}
	for (int i = 0; i < n; i++)
	{
		tmp[a[i]-min]++;
	}
	int j = 0;
	for (int i = 0; i < tmpN; i++)
	{
		while (tmp[i] != 0)
		{
			a[j++] = i+min;
			tmp[i]--;
		}
	}
	free(tmp);
}