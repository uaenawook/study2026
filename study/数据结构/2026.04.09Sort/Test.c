#include"Sort.h"


// ≤‚ ‘√∞≈›≈≈–Ú
void TestBubbleSort()
{
	int a[] = { 6,2,9,7,8,4,5,1,3,0 };
	int n = sizeof(a) / sizeof(int);
	printf("√∞≈›≈≈–Ú£∫");
	PrintfArr(a, n);
	BubbleSort(a, n);
	PrintfArr(a, n);
}

// ≤‚ ‘—°‘Ò≈≈–Ú
void TestSelectionSort()
{
	int a[] = { 6,2,9,7,8,4,5,1,3,0 };
	int n = sizeof(a) / sizeof(int);
	printf("—°‘Ò≈≈–Ú£∫");
	PrintfArr(a, n);
	SelectionSort2(a, n);
	PrintfArr(a, n);
}


//≤‚ ‘≤Â»Î≈≈–Ú
void TestInsertionSort()
{
	int a[] = { 6,2,9,7,8,4,5,1,3,0 };
	int n = sizeof(a) / sizeof(int);
	printf("≤Â»Î≈≈–Ú£∫");
	PrintfArr(a, n);
	InsertionSort(a, n);
	PrintfArr(a, n);
}

//≤‚ ‘œ£∂˚≈≈–Ú
void TestShellSort()
{
	int a[] = { 6,2,9,7,8,4,5,1,3,0 };
	int n = sizeof(a) / sizeof(int);
	printf("œ£∂˚≈≈–Ú£∫");
	PrintfArr(a, n);
	ShellSort(a, n);
	PrintfArr(a, n);

}

// ≤‚ ‘øÏÀŸ≈≈–Ú
TestQuickSort()
{
	// ’˝≥£
	int a[] = { 6,2,9,7,8,4,5,1,3,0 };
	//  ˝æ›±‰∂‡£¨”–÷ÿ∏¥æÕÀ¿—≠ª∑ - “—–ﬁ∏¥
	// int a[] = { 6,2,9,7,8,4,5,1,3,0,2,9,7,8,4,5,1,3,0 };
	int n = sizeof(a) / sizeof(int);
	printf("øÏÀŸ≈≈–Ú£∫");
	PrintfArr(a, n);
	QuickSort(a,0, n-1);
	//QuickSortNonR(a,0, n-1);
	PrintfArr(a, n);
}

// ≤‚ ‘πÈ≤¢≈≈–Ú
void TestMergeSort()
{
	//int a[] = { 6,2,9,7,8,4,5,1,3,0};
	int a[] = { 6,2,9,7,8,4,5,1,3,0};
	int n = sizeof(a) / sizeof(int);
	printf("πÈ≤¢≈≈–Ú£∫");
	PrintfArr(a, n);
	//MergeSort(a, n);
	MergeSortNonR(a, n);
	PrintfArr(a, n);
}

void TestOP()
{
	srand(time(0));
	const int N = 1000000;
	int* a1 = (int*)malloc(sizeof(int) * N);
	int* a2 = (int*)malloc(sizeof(int) * N);
	int* a3 = (int*)malloc(sizeof(int) * N);
	int* a4 = (int*)malloc(sizeof(int) * N);
	int* a5 = (int*)malloc(sizeof(int) * N);
	int* a6 = (int*)malloc(sizeof(int) * N);
	int* a7 = (int*)malloc(sizeof(int) * N);

	for (int i = 0; i < N; ++i)
	{
		a1[i] = rand() + i;
		a2[i] = a1[i];
		a3[i] = a1[i];
		a4[i] = a1[i];
		a5[i] = a1[i];
		a6[i] = a1[i];
		a7[i] = a1[i];
	}

	int begin1 = clock();
	//InsertSort(a1, N);
	int end1 = clock();

	int begin2 = clock();
	ShellSort(a2, N);
	int end2 = clock();

	int begin3 = clock();
	//SelectSort(a3, N);
	int end3 = clock();

	int begin4 = clock();
	HeapSort(a4, N);
	int end4 = clock();

	int begin5 = clock();
	//QuickSort(a5, 0, N - 1);
	QuickSortNonR(a5, 0, N - 1);
	int end5 = clock();


	int begin6 = clock();
	//MergeSort(a6, N);
	MergeSortNonR(a6, N);
	int end6 = clock();

	int begin7 = clock();
	//BubbleSort(a7, N);
	int end7 = clock();

	printf("InsertSort:%d\n", end1 - begin1);
	printf("ShellSort:%d\n", end2 - begin2);
	//printf("œ£∂˚≈≈–Ú£∫");PrintfArr(a2, 15);
	printf("SelectSort:%d\n", end3 - begin3);
	printf("HeapSort:%d\n", end4 - begin4);
	//printf("∂—≈≈–Ú£∫"); PrintfArr(a4, 15);
	printf("QuickSort:%d\n", end5 - begin5);
	printf("øÏÀŸ≈≈–Ú£∫"); PrintfArr(a5, 15);
	printf("MergeSort:%d\n", end6 - begin6);
	printf("πÈ≤¢≈≈–Ú£∫"); PrintfArr(a6, 15);
	printf("BubbleSort:%d\n", end7 - begin7);

	free(a1);
	free(a2);
	free(a3);
	free(a4);
	free(a5);
	free(a6);
	free(a7);
}
int main()
{
	// ≤‚ ‘√∞≈›≈≈–Ú
	TestBubbleSort();

	// ≤‚ ‘—°‘Ò≈≈–Ú
	TestSelectionSort();

	// ≤‚ ‘≤Â»Î≈≈–Ú
	TestInsertionSort();

	// ≤‚ ‘œ£∂˚≈≈–Ú
	TestShellSort();

	// ≤‚ ‘øÏÀŸ≈≈–Ú
	TestQuickSort();

	// ≤‚ ‘πÈ≤¢≈≈–Ú
	TestMergeSort();

	TestOP();

	return 0;
}