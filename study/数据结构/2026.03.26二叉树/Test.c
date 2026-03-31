#include"Heap.h"

void HeapSort(int* a, int n)
{
	// 降序，建小堆
	// 升序，建大堆
	/*for (int i = 1; i < n; i++)
	{
		AdjustUp(a, i);
	}*/

	for (int i = n-1; i > 0; i--)
	{
		AdjustUp(a, i);
	}

	//for (int i = (n - 1 - 1) / 2; i >= 0; i--)
	//{
	//	AdjustDown(a, n, i);
	//}

	//int end = n - 1;
	//while (end > 0)
	//{
	//	swap(&a[0], &a[end]);
	//	AdjustDown(a, end, 0);
	//	--end;
	//}
}

void TestHeap2()
{
	int a[] = { 4,2,8,1,5,6,9,7,2,7,9 };
	HeapSort(a, sizeof(a) / sizeof(int));
}

int main()
{
	TestHeap2();

	return 0;
}