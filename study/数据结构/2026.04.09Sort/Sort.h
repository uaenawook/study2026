#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

//打印数组
void PrintfArr(int* a, int n);

//冒泡排序
void BubbleSort(int* a, int n);

//选择排序
void SelectionSort(int* a, int n);
void SelectionSort2(int* a, int n);

//插入排序
void InsertionSort(int* a, int n);

//希尔排序
void ShellSort(int* a, int n);

// 快速排序
void QuickSort(int* a, int left, int right);