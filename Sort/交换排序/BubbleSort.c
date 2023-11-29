//冒泡排序
//O(N^2)

void Swap(int* p1, int* p2)
{
	int tmp = *p1;
	*p1= *p2;
	*p2 = tmp;
}

void BubbleSort(int* a, int n)
{
	int end = n;
	while(end > 0)
	{
		int exchange = 0;
		for (int i = 1; i < end; ++i)
		{
			if (a[i - 1] > a[i])
			{
				Swap(&a[i - 1], &a[i]);
				exchange = 1;
			}
		}
		
		if (exchange == 0)
		{
			break;
		}
		
		--end;
	}
}