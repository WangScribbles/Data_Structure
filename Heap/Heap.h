#pragma once

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

typedef int HPDataType;

typedef struct Heap
{
	HPDataType* _a;
	int _size;
	int _capacity;
}Heap;

void HeapInit(Heap* php, HPDataType* a, int n);
void HeapDestory(Heap* php);

void HeapPush(Heap* php, HPDataType x);
void HeapPop(Heap* php);  //删除堆顶数据

HPDataType HeapTop(Heap* php);

/堆排序
void HeapSort(int* a, int n);

void AdjustDown(HPDataType* a, int n, int root);
void AdjustUp(HPDataType* a, int n, int child);
