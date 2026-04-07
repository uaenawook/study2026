#include"TopK.h"



void PrintTopK(int* a, int n, int k)
{
	// 选出最大K个：建小根堆，保持根的数据是堆中最小的，但这个堆存的是a中最大的前K个，
	//				比根大就替换插入进去，选出次小的当根，比根小则不插入

	// 选出最小K个：建大根堆，保持根的数据是堆中最大的，但这个堆存的是a中最小的前K个，
	//				比根小就替换插入进去，选出次大的当根，比根大则不插入

	// 用前a中K个数建堆
	Heap hp;
	HeapInit(&hp);
	HeapCreate(&hp, a, k);

	// 剩余a中的数调整
	for (int i = k; i < n; i++)
	{
		// 比较
		if (a[i] < HeapTop(&hp))
		{
			// 插入调整
			hp.a[0] = a[i];
			AdjustDown(hp.a, k, 0);
		}

	}

	HeapSort(hp.a, k);
	for (int i = 0; i < k; i++)
	{
		printf("%d ", hp.a[i]);
	}
	printf("\n");
	HeapDestroy(&hp);


}



//int main()
//{
//	TestTopk();
//	return 0;
//}