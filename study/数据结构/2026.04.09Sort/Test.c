#include"Sort.h"

// ≤‚ ‘√∞≈›≈≈–Ú
void TestBubbleSort()
{
	int a[] = { 2,5,9,7,6,4,8,1,3,0 };
	int n = sizeof(a) / sizeof(int);
	printf("√∞≈›≈≈–Ú£∫");
	PrintfArr(a, n);
	BubbleSort(a, n);
	PrintfArr(a, n);
}

// ≤‚ ‘—°‘Ò≈≈–Ú
void TestSelectionSort()
{
	int a[] = { 2,5,9,7,6,4,8,1,3,0 };
	int n = sizeof(a) / sizeof(int);
	printf("—°‘Ò≈≈–Ú£∫");
	PrintfArr(a, n);
	SelectionSort2(a, n);
	PrintfArr(a, n);
}

int main()
{
	// ≤‚ ‘√∞≈›≈≈–Ú
	TestBubbleSort();

	// ≤‚ ‘—°‘Ò≈≈–Ú
	TestSelectionSort();

	return 0;
}