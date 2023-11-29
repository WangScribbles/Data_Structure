//直接插入排序
//O(N^2)
//有序或接近有序最好O(N)
//逆序或接近逆序最坏

void InsertSort(int* a, int n)
{
	assert(a);
	
	//最后一次排序是把第(n - 1)个（最后一个）元素往前(n - 2)个元素里面插
	for (int i = 0; i < n - 1; i++) //最后一个位置时(n - 1) 
	{
		//单趟排序
		//[0, end]有序，把(end + 1)往[0, end]区间插入保持它有序
		int end = i;
		int tmp = a[end + 1];
		while (end >= 0)
		{
			if (tmp < a[end])  //升序
			{
				a[end + 1] = a[end];
				--end;
			}
			else
			{
				break;
			}
		}
		a[end + 1] = tmp;
	}
}