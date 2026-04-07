#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>



typedef int HSDataType;
typedef struct Heap
{
	HSDataType* a;
	int size;
	int capacity;
}Heap;

// ¶ÑµÄ¹¹½¨


void HeapInit(Heap* php);
void HeapDestroy(Heap* php);
void swap(HSDataType* x, HSDataType* y);

void AdjustDown(HSDataType* a, int n, int parent);
void AdjustUp(HSDataType* a, int child);

void HeapPush(Heap* php, HSDataType x);
void HeapPop(Heap* php);

void HeapCreate(Heap* hp, HSDataType* a, int n);

HSDataType HeapTop(Heap* php);
int HeapSize(Heap* php);
int HeapEmpty(Heap* php);


void HeapSort(int* a, int n);

//void PrintTopK(int* a, int n, int k);
