#include "Heap.h"


//С��

void Swap(HPDataType* p1, HPDataType* p2)
{
	HPDataType tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}

//ǰ�᣺������������С��
//O(logN)
void AdjustDown(HPDataType* a, int n, int root)
{
	int parent = root;
	int child = parent * 2 + 1;
	while (child < n)
	{
		//�ҳ����Һ�����С����һ��
		//(child + 1)����Խ��
		if (child + 1 < n && a[child + 1] < a[child]) //1/2:>
		{
			++child;
		}

		//�������С�ڸ��ף��򽻻�
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
	//����while (parent >= 0)����53��ʹ�ø��ײ���С��0
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
	//1.����
	//��������N���ڵ㣬���߶ȣ�logN
	//Ҫע�����ｨ�ѵ�ʱ�临�ӶȲ���O(N * logN)����O(N)
	//��Ϊÿ�β��Ǵ�0��ʼ���µ�
	for (int i = (n - 1 - 1) / 2; i >= 0; i--)
	{
		AdjustDown(a, n, i); //�������iһֱΪ0������O(N * logN)
	}


	//С���Ž��򣬴��������
	//O(N * logN)
	int end = n - 1;
	while (end > 0)
	{
		Swap(&a[0], &a[end]);

		//�ټ���ѡ��С��
		AdjustDown(a, end, 0);
		end--;
	}
}

void HeapInit(Heap* php, HPDataType* a, int n)
{
	php->_a = (HPDataType*)malloc(sizeof(HPDataType) * n);
	if (php->_a == NULL)
	{
		printf("�ڴ治��\n");
		exit(-1);
	}
	memcpy(php->_a, a, sizeof(HPDataType) * n);
	php->_size = n;
	php->_capacity;

	//������
	//�����ʼ����֤������������С��
	//���������Ҷ�ӽڵ㿪ʼ�������ţ���Ϊ����Ҷ�Ӳ���
	//���Դӵ�����һ����Ҷ�ӽڵ㿪ʼ
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
			printf("�ڴ治��\n");
			exit(-1);
		}
		php->_a = tmp;
	}

	php->_a[php->_size++] = x;

	AdjustUp(php->_a, php->_size, php->_size - 1);
}
void HeapPop(Heap* php)  //ɾ���Ѷ�����
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