//选择排序
//O(N^2)

//一次选两个数（max和min）

void Swap(int* p1, int* p2)
{
	int tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}

void SelectSort(int* a, int n)
{
	assert(a);d
	
	int begin = 0;
	int end = n - 1;
	while (begin < end)
	{
		//在[begin, end]找出min和max的下标
		int mini = begin
		int maxi = begin;
		for (int i = begin + 1; i <= end; i++)
		{
			if (a[i] > a[maxi])
				maxi = i;
			if (a[i] < a[mini])
				mini = i;
		}
		
		Swap(&a[begin], &a[mini]);
		//如果max和begin位置重叠，则maxi的位置需要修正
		if (begin = maxi)
		{
			maxi = mini;
		}
		
		Swap(&a[end], &a[maxi]);
		
		begin++;
		end--;
	}
}