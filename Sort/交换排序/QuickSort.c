//快速排序
//O(N * logN)
//空间复杂度：O(logN)（栈帧深度）

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
//1、左右指针法
int PartSort1(int* a, int begin, int end)
{
	//让key不是最大也不是最小
	int midIndex = GetMidIndex(a, begin, end);
	Swap(&a[midIndex], &a[end]);
	
	
	int keyIndex = end;
	while (begin < end)
	{
		//key选右边，左边先走，保证最后停下的位置比key大
		//(key选左边，右边先走，保证最后停下的位置比key小)
		
		//begin找大
		//begin和end不能错过
		while (begin < end && a[begin] <= a[keyIndex])
		{
			++begin;
		}
		
		//end找小
		//begin和end不能错过
		while (begin < end && a[end] >= a[keyIndex])
		{
			--end;
		}
		
		Swap(&a[begin], &a[end]);
	}
	
	Swap(&a[begin], &a[keyIndex]);
	
	return begin;
}

//2、挖坑法
int PartSort2(int* a, int begin, int end)
{
	//让key不是最大也不是最小
	int midIndex = GetMidIndex(a, begin, end);
	Swap(&a[midIndex], &a[end]);
	
	//最开始的坑
	int key = a[end];
	while (begin < end)
	{
		while (begin < end && a[begin] <= key)
		{
			++begin;
		}
		
		//左边找到比key大的填到右边的坑，begin位置形成新的坑
		a[end] = a[begin];
		
		while (begin < end && a[end] >= key)
		{
			--end;
		}
		
		//右边找到比key小的填到左边的坑，end位置形成新的坑
		a[begin] = a[end];
	}
	
	a[begin] = key;
	
	return begin;
}

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

//前提：[left, right]
void QuickSort(int* a, int left, int right)
{
	assert(a);
	
	if (left >= right)
		return;
	
	//优化2
	if ((right - left + 1) > 10)
	{
		int div = PartSort1(a, left, end);
		//int div = PartSort2(a, left, end);
		//int div = PartSort3(a, left, end);
		
		
		//[left, div-1] div [div+1, right]
		QuickSort(a, left, div - 1);
		QuickSort(a, div + 1, right);
	}
	else
	{
		//小于10个数以内的区间，不再递归排序
		//小区间使用直接插入排序
		InsertSort(a + left, right - left + 1);
	}
}