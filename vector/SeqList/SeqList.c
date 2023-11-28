#include "SeqList.h"

//��ʼ��
void SeqListInit(SeqList* psl)
{
	assert(psl);

	//��һ
	//psl.a = NULL;
	//psl.size = 0;
	//psl.capacity = 0;

	//����
	psl->a = (SLDataType*)malloc(sizeof(SLDataType) * 4);
	if (psl->a == NULL)
	{
		printf("�����ڴ�ʧ��\n");
		exit(-1);
	}
	psl->size = 0;
	psl->capacity = 4;
}
//����
void SeqListDestory(SeqList* psl)
{
	free(psl->a);
	psl->a = NULL;
	psl->size = psl->capacity = 0;
}

//����������������������ݣ�
void SeqListCheckCapacity(SeqList* psl)
{
	if (psl->size >= psl->capacity)
	{
		psl->capacity *= 2;	//һ����������
		psl->a = (SLDataType*)realloc(psl->a, sizeof(SLDataType) * psl->capacity);
		if (psl->a == NULL)
		{
			printf("����ʧ��\n");
			exit(-1);
		}
	}
}

//β��
void SeqListPushBack(SeqList* psl, SLDataType x)
{
	/*
	//��һ
	assert(psl);

	SeqListCheckCapacity(psl);

	psl->a[psl->size] = x;
	psl->size++;
	*/

	SeqListInsert(psl, psl->size, x);
}
//βɾ
void SeqListPopBack(SeqList* psl)
{
	/*
	//��һ
	assert(psl);

	psl->size--;
	*/

	//����
	SeqListErase(psl, psl->size - 1);
}

//ͷ��
void SeqListPushFront(SeqList* psl, SLDataType x)
{
	/*
	//��һ
	assert(psl);
	SeqListCheckCapacity(psl);

	for (int end = psl->size - 1; end >= 0; end--)
	{
		psl->a[end + 1] = psl->a[end];
	}

	psl->a[0] = x;
	psl->size++;
	*/

	//����
	SeqListInsert(psl,0, x);
}
//ͷɾ
void SeqListPopFront(SeqList* psl)
{
	/*
	//��һ
	assert(psl);

	for (int start = 0; start < psl->size - 1; start++)
	{
		psl->a[start] = psl->a[start + 1];
	}
	psl->size--;
	*/

	//����
	SeqListErase(psl, 0);
}

//���
void SeqListPrint(SeqList* psl)
{
	assert(psl);

	for (int i = 0; i < psl->size; i++)
	{
		printf("%d ", psl->a[i]);
	}
	printf("\n");
}


//����λ�õĲ���
void SeqListInsert(SeqList* psl, int pos, SLDataType x)
{
	assert(psl);
	//���β�pos����������Ϊsize_t�������ж�pos >= 0
	assert(pos >= 0 || pos <= psl->size);

	SeqListCheckCapacity(psl);

	for (int end = psl->size - 1; end >= pos; end--)
	{
		psl->a[end + 1] = psl->a[end];
	}
	psl->a[pos] = x;
	psl->size++;
}

//����λ�õ�ɾ��
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

//����ָ�����ݵ��±�
int SeqListFind(SeqList* psl, SLDataType x)
{
	assert(psl); 

	//��������
	for (int i = 0; i < psl->size; i++)
	{
		if (psl->a[i] == x)
		{
			return i;
		}
	}
	return -1;
}