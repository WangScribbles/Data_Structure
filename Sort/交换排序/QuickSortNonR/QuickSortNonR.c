//快速排序（非递归）
//O(N * logN)
#include "Stack.h"

void Swap(int* p1, int* p2)
{
	int tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}

//优化1
//三数取中，让有序时变成最优
int GEtMidIndex(int* a, int begin, int end)
{
	int mid = (begin + end) / 2;
	if (a[begin] < a[mid])
	{
		if (a[mid] < a[end])
			return mid; 
		else if (a[begin] > a[end])
			return begin;
		else
			return end;
	}
	else
	{
		if (a[mid] > a[end])
			return mid;
		else if (a[begin] < a[end])
			return begin;
		else
			return end;
	}
}

//单趟排序O(N)
//前提：[begin, end]
//

//3、前后指针法
int PartSort3(int* a, int begin, int end)
{
	//让key不是最大也不是最小
	int midIndex = GetMidIndex(a, begin, end);
	Swap(&a[midIndex], &a[end]);
	
	int prev = begin - 1;
	int cur = begin;
	int keyIndex = end;
	
	while (cur < end)
	{
		if (a[cur] < a[keyIndex] && ++prev != cur)
			Swap(&a[prev], &a[cur]);
		
		++cur;
	}
	
	Swap(&a[++prev], &a[keyIndex]);
	
	return prev;
}

// 递归改非递归
// 1、直接改循环 -- 比如斐波那契数列、归并排序
// 2、用数据结构栈模拟递归过程
//非递归：1、提高效率（递归建立栈帧有消耗，对于现代计算机，这个优化微乎其微）
//		  2、递归最大的缺陷是：如果栈帧的深度太深，可能导致栈溢出。因为系统栈空间一般不大，在m级别
//			 数据结构栈模拟非递归，数据是存储在堆上，堆是g级别的空间
void QuickSortNonR(int* a, int left, int right)
{
	//栈模拟
	assert(a);
	
	Stack st;
	StackInit(&st);
	
	StackPush(&st, right);
	StackPush(&st, left);
	
	while (!StackEmpty(&st))
	{
		int begin =StackTop(&st);
		StackPop(&st);
		int end = StackTop(&st);
		StackPop(&st);
		
		//[begin, end]
		int div = PartSort3(a, begin, end);
		
		//[begin, div-1] div [div+1, end]
		if (div + 1 < end)
		{
			StackPush(&st, end);
			StackPush(&st, div + 1);
		}
		
		if (begin < div - 1)
		{
			StackPush(&st, div - 1);
			StackPush(&st, begin);
		}
	}
	
	StackDestory(&st);
}