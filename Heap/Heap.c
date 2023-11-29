#include "Heap.h"


//小堆

void Swap(HPDataType* p1, HPDataType* p2)
{
	HPDataType tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}

//前提：左右子树都是小堆
//O(logN)
void AdjustDown(HPDataType* a, int n, int root)
{
	int parent = root;
	int child = parent * 2 + 1;
	while (child < n)
	{
		//找出左右孩子中小的那一个
		//(child + 1)可能越界
		if (child + 1 < n && a[child + 1] < a[child]) //1/2:>
		{
			++child;
		}

		//如果孩子小于父亲，则交换
		if (a[child] < a[parent])  //2/2:>
		{
			Swap(&a[child], &a[parent]);
			parent = child;
			child = parent * 2 + 1;
		}
		else
		{
			break;
		}
	}
}

void AdjustUp(HPDataType* a, int n, int child)
{
	int parent = (child - 1) / 2;
	//错误：while (parent >= 0)，第53行使得父亲不会小于0
	while (child > 0)
	{
		if (a[child] < a[parent])
		{
			Swap(&a[child], &a[parent]);
			//
			child = parent;
			parent = (child - 1) / 2;
		}
		else
		{
			break;
		}
	}
}


//O(N * logN)
void HeapSort(int* a, int n)
{
	//1.建堆
	//假设树有N个节点，树高度：logN
	//要注意这里建堆的时间复杂度不是O(N * logN)，是O(N)
	//因为每次不是从0开始往下调
	for (int i = (n - 1 - 1) / 2; i >= 0; i--)
	{
		AdjustDown(a, n, i); //如果这里i一直为0，则是O(N * logN)
	}


	//小堆排降序，大堆排升序
	//O(N * logN)
	int end = n - 1;
	while (end > 0)
	{
		Swap(&a[0], &a[end]);

		//再继续选次小的
		AdjustDown(a, end, 0);
		end--;
	}
}

void HeapInit(Heap* php, HPDataType* a, int n)
{
	php->_a = (HPDataType*)malloc(sizeof(HPDataType) * n);
	if (php->_a == NULL)
	{
		printf("内存不足\n");
		exit(-1);
	}
	memcpy(php->_a, a, sizeof(HPDataType) * n);
	php->_size = n;
	php->_capacity;

	//构建堆
	//从最后开始，保证左右子树都是小堆
	//如果从最后的叶子节点开始调不够优，因为最后的叶子不动
	//所以从倒数第一个非叶子节点开始
	for (int i = (n - 1 - 1) / 2; i >= 0; --i)
	{
		AdjustDown(php->_a, php->_size, i);
	}
}
void HeapDestory(Heap* php)
{
	assert(php);

	free(php->_a);
	php->_a = NULL;
	php->_capacity = php->_size = 0;
}

void HeapPush(Heap* php, HPDataType x)
{
	assert(php);

	if (php->_size == php->_capacity)
	{
		php->_capacity *= 2;
		HPDataType* tmp = (HPDataType*)realloc(php->_a, sizeof(HPDataType) * php->_capacity);
		if (tmp == NULL)
		{
			printf("内存不足\n");
			exit(-1);
		}
		php->_a = tmp;
	}

	php->_a[php->_size++] = x;

	AdjustUp(php->_a, php->_size, php->_size - 1);
}
void HeapPop(Heap* php)  //删除堆顶数据
{
	assert(php);
	assert(php->_size > 0);

	Swap(&php->_a[0], &php->_a[php->_size - 1]);
	php->_size--;
	AdjustDown(php->_a, php->_size, 0);
}

HPDataType HeapTop(Heap* php)
{
	assert(php);
	assert(php->_size > 0);

	return php->_a[0];
}