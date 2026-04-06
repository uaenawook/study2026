#include"HeapSort.h"


void HeapPrintf(Heap* hp)
{
	for (int i = 0; i < hp->size; i++)
	{
		printf("%d ", hp->a[i]);
	}
	printf("\n");
}
//void HeapTest()
//{
//	int a[] = { 4,7,1,9,2,3,6,5 };
//	int aSize = sizeof(a) / sizeof(int);
//	for (int i = 0; i < sizeof(a) / sizeof(int); i++)
//	{
//		printf("%d ", a[i]);
//	}
//	printf("\n");
//
//
//	Heap hp;
//	HeapInit(&hp);
//	//插入
//	for (int i = 0; i < aSize ;i++)
//	{
//		HeapPush(&hp, a[i]);
//	}
//
//	HeapPop(&hp);
//	HeapPrintf(&hp);
//	HeapPop(&hp);
//	HeapPrintf(&hp);
//	HeapPop(&hp);
//	HeapPrintf(&hp);
//	HeapPop(&hp);
//	HeapPrintf(&hp);
//	HeapPop(&hp);
//	HeapPrintf(&hp);
//	HeapPop(&hp);
//	HeapPrintf(&hp);
//	HeapPop(&hp);
//	HeapPrintf(&hp);
//	HeapPop(&hp);
//	HeapPrintf(&hp);
//
//	HeapDestroy(&hp);
//}

void HeapTest2()
{
	int a[] = { 4,7,1,9,2,3,6,5 };
	int aSize = sizeof(a) / sizeof(int);
	for (int i = 0; i < sizeof(a) / sizeof(int); i++)
	{
		printf("%d ", a[i]);
	}
	printf("\n");

	Heap hp;
	HeapInit(&hp);
	HeapCreate(&hp, a, aSize);
	HeapPrintf(&hp);

	//HeapSort(&hp);
	//HeapPrintf(&hp);

	//a不是malloc不能destroy
	HeapDestroy(&hp);

}

void HeapTest3()
{
	int a[] = { 4,7,1,9,2,3,6,5 };
	int aSize = sizeof(a) / sizeof(int);
	for (int i = 0; i < sizeof(a) / sizeof(int); i++)
	{
		printf("%d ", a[i]);
	}
	printf("\n");

	HeapSort(a, aSize);
	for (int i = 0; i < sizeof(a) / sizeof(int); i++)
	{
		printf("%d ", a[i]);
	}
	printf("\n");


}
int main()
{

	//HeapTest();
	//HeapTest2();
	HeapTest3();

	return 0;
}