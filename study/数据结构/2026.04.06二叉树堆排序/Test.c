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


void PrintTopK(int* a, int n, int k);
void TestTopk()
{
	int n = 10000;
	int* a = (int*)malloc(sizeof(int) * n);
	srand(time(0));
	for (size_t i = 0; i < n; ++i)
	{
		a[i] = rand() % 1000000;
	}

	a[5] = 1000000 + 1;
	a[1231] = 1000000 + 2;
	a[531] = 1000000 + 3;
	a[5121] = 1000000 + 4;
	a[115] = 1000000 + 5;
	a[2335] = 1000000 + 6;
	a[9999] = 1000000 + 7;
	a[76] = 1000000 + 8;
	a[423] = 1000000 + 9;
	a[3144] = 1000000 + 10;

	a[5+1] = 1;
	a[1231 + 1] = 2;
	a[531 + 1] = 3;
	a[5121 + 1] = 4;
	a[115 + 1] = 5;
	a[2335 + 1] = 6;
	a[9999 + 1] = 7;
	a[76 + 1] = 8;
	a[423 + 1] = 9;
	a[3144 + 1] = 10;


	PrintTopK(a, n, 10);
}

int main()
{

	//HeapTest();
	//HeapTest2();
	//HeapTest3();
	TestTopk();

	return 0;
}