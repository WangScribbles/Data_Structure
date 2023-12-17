#include "Stack.h"

//��ʼ��������
void StackInit(Stack* pst)
{
	assert(pst);

	/*pst->_a = NULL;
	pst->_top = 0;
	pst->_capacity = 0;*/

	pst->_a = (STDataType*)malloc(sizeof(STDataType) * 4);
	pst->_top = 0;  //
	pst->_capacity = 4;
}
void StackDestory(Stack* pst)
{
	assert(pst);

	free(pst->_a);
	pst->_a = NULL;
	pst->_top = pst->_capacity = 0;
}

//��ջ�ͳ�ջ
void StackPush(Stack* pst, STDataType x)
{
	assert(pst);

	if (pst->_top == pst->_capacity)
	{
		pst->_capacity *= 2;
		STDataType* tmp = (STDataType*)realloc(pst->_a, sizeof(STDataType) * pst->_capacity);
		if (tmp == NULL)
		{
			printf("�ڴ治��\n");
			exit(-1);
		} 
		else
		{
			pst->_a = tmp;
		}
	}
	pst->_a[pst->_top] = x;
	pst->_top++;
}
void StackPop(Stack* pst)
{
	assert(pst);
	assert(pst->_top > 0);

	pst->_top--;
}

//��ȡջ��������
STDataType StackTop(Stack* pst)
{
	assert(pst);
	assert(pst->_top > 0);

	return pst->_a[pst->_top - 1];
}


//����1�ǿգ�����0�Ƿǿ�
int StackEmpty(Stack* pst)
{
	assert(pst);

	//return pst->_top == 0 ? 1 : 0;
	return !pst->_top;
}

//��ȡ���ݸ���
int StackSize(Stack* pst)
{
	assert(pst);

	return pst->_top;
}