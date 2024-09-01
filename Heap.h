#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

//实现堆(以小堆为例)
typedef int HPDataType;
#include <stdio.h>
typedef struct Heap
{
	HPDataType* _a;
	int _size;
	int _capacity;
}Heap;

void AdjustDown(HPDataType* a, int n, int root);

void HeapInit(Heap* php, HPDataType* a, int n);
void HeapDestory(Heap* php);
void HeapPush(Heap* php, HPDataType x);
void HeapPop(Heap* php);
HPDataType HeapTop(Heap* php);