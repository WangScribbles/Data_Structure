#include "SeqList.h"

//初始化
void SeqListInit(SeqList* psl)
{
	assert(psl);

	//法一
	//psl.a = NULL;
	//psl.size = 0;
	//psl.capacity = 0;

	//法二
	psl->a = (SLDataType*)malloc(sizeof(SLDataType) * 4);
	if (psl->a == NULL)
	{
		printf("申请内存失败\n");
		exit(-1);
	}
	psl->size = 0;
	psl->capacity = 4;
}
//销毁
void SeqListDestory(SeqList* psl)
{
	free(psl->a);
	psl->a = NULL;
	psl->size = psl->capacity = 0;
}

//检查容量（容量不够再扩容）
void SeqListCheckCapacity(SeqList* psl)
{
	if (psl->size >= psl->capacity)
	{
		psl->capacity *= 2;	//一般扩容两倍
		psl->a = (SLDataType*)realloc(psl->a, sizeof(SLDataType) * psl->capacity);
		if (psl->a == NULL)
		{
			printf("扩容失败\n");
			exit(-1);
		}
	}
}

//尾插
void SeqListPushBack(SeqList* psl, SLDataType x)
{
	/*
	//法一
	assert(psl);

	SeqListCheckCapacity(psl);

	psl->a[psl->size] = x;
	psl->size++;
	*/

	SeqListInsert(psl, psl->size, x);
}
//尾删
void SeqListPopBack(SeqList* psl)
{
	/*
	//法一
	assert(psl);

	psl->size--;
	*/

	//法二
	SeqListErase(psl, psl->size - 1);
}

//头插
void SeqListPushFront(SeqList* psl, SLDataType x)
{
	/*
	//法一
	assert(psl);
	SeqListCheckCapacity(psl);

	for (int end = psl->size - 1; end >= 0; end--)
	{
		psl->a[end + 1] = psl->a[end];
	}

	psl->a[0] = x;
	psl->size++;
	*/

	//法二
	SeqListInsert(psl,0, x);
}
//头删
void SeqListPopFront(SeqList* psl)
{
	/*
	//法一
	assert(psl);

	for (int start = 0; start < psl->size - 1; start++)
	{
		psl->a[start] = psl->a[start + 1];
	}
	psl->size--;
	*/

	//法二
	SeqListErase(psl, 0);
}

//输出
void SeqListPrint(SeqList* psl)
{
	assert(psl);

	for (int i = 0; i < psl->size; i++)
	{
		printf("%d ", psl->a[i]);
	}
	printf("\n");
}


//任意位置的插入
void SeqListInsert(SeqList* psl, int pos, SLDataType x)
{
	assert(psl);
	//若形参pos的数据类型为size_t，则不用判断pos >= 0
	assert(pos >= 0 || pos <= psl->size);

	SeqListCheckCapacity(psl);

	for (int end = psl->size - 1; end >= pos; end--)
	{
		psl->a[end + 1] = psl->a[end];
	}
	psl->a[pos] = x;
	psl->size++;
}

//任意位置的删除
void SeqListErase(SeqList* psl, int pos)
{
	assert(psl);
	assert(pos >= 0 || pos < psl->size);

	for (int start = pos; start < psl->size - 1; start++)
	{
		psl->a[start] = psl->a[start + 1];
	}

	psl->size--;
}

//返回指定数据的下标
int SeqListFind(SeqList* psl, SLDataType x)
{
	assert(psl); 

	//遍历查找
	for (int i = 0; i < psl->size; i++)
	{
		if (psl->a[i] == x)
		{
			return i;
		}
	}
	return -1;
}