#include<stdio.h>

void swap(int* x, int* y)
{
	int tmp = *x;
	*x = *y;
	*y = tmp;
}
// √∞≈›≈≈–Ú
void BubbleSort(int* arr,int n)
{
	for (int j = 0; j < n - 1 ; ++j)
	{
		int flag = 0;

		for (int i = 0; i < n - 1-j; ++i)
		{
			if (arr[i] > arr[i + 1])
			{
				swap(&arr[i], &arr[i + 1]);
				flag = 1;
			}
		}
		if (flag == 0)
			break;
	}

}

// ∂—≈≈–Ú
void AdjustDown(int* a, int n, int parent)
{
	// Ω®¥Û∂—
	int child = parent * 2 + 1;
	while (child < n)
	{
		if (child + 1 < n && a[child + 1] > a[child])
		{
			++child;
		}

		if (a[parent] < a[child])
		{
			swap(&a[parent], &a[child]);
			parent = child;
			child = parent * 2 + 1;
		}
		else
		{
			break;
		}
	}
}
void HeapSort(int* a, int n)
{
	int child = (n - 1 - 1) / 2;
	for (int i = child; i >= 0; --i)
	{
		AdjustDown(a, n, i);
	}
	while (n--)
	{
		swap(&a[0], &a[n]);
		AdjustDown(a, n, 0);
	}


}

int main()
{
	int arr[] = { 5,9,7,8,6,1,8,2,128,0 };
	int size = sizeof(arr) / sizeof(int);
	//BubbleSort(arr,size);

  	HeapSort(arr, size);


	return 0;
}