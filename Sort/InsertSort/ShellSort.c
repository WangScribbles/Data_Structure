//希尔排序
//O(N^1.3 ~ N^2)

//步骤1、预排序（数组接近有序）
	//把间距为gap的值分为一组，进行插入排序
//步骤2、直接插入排序
	//最后一次gap == 1

void ShellSort(int* a, int n)
{
	int gap = n;
	while (gap > 1)
	{
		gap = gap / 3 + 1;  // +1 保证最后一次gap一定是1
		//多组并排
		for (int i = 0; i < n - gap; i++)
		{
			int end = i;
			int tmp = a[end + gap];
			while(end >= 0)
			{
				if (tmp < a[end])
				{
					a[end + gap] = a[end];
					end -= gap;
				}
				else
				{
					break;
				}
			}
			a[end + gap] = tmp;
		}
	}
}
//gap越大，前面大的数可以越快到后面，后面小的数可以越快到前面。gap越大，越不接近有序
//gap越小越接近有序。gap == 1相当于直接插入排序