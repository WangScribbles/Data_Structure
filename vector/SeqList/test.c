#define _CRT_SECURE_NO_WARNINGS 1
#include "SeqList.h"

void test()
{
	SeqList s;

	//��ʼ��
	SeqListInit(&s);

	//β��
	SeqListPushBack(&s, 1);
	SeqListPushBack(&s, 2);
	SeqListPushBack(&s, 3);
	SeqListPushBack(&s, 4);
	SeqListPushBack(&s, 5);
	printf("β���");
	SeqListPrint(&s);

	//βɾ
	SeqListPopBack(&s);
	printf("βɾ��");
	SeqListPrint(&s);

	//ͷ��
	SeqListPushFront(&s, 7);
	printf("ͷ���");
	SeqListPrint(&s);

	//ͷɾ
	SeqListPopFront(&s);
	printf("ͷɾ��");
	SeqListPrint(&s);

	//����λ�ò���
	SeqListInsert(&s, 3, 18);
	printf("��4��λ�ò����");
	SeqListPrint(&s);

	//����λ��ɾ��
	SeqListErase(&s, 3);
	printf("��4��λ��ɾ����");
	SeqListPrint(&s);

	//ָ�����ݣ���ϲ��Һ�����
	int pos = SeqListFind(&s, 2);
	if (pos != -1)
	{
		SeqListErase(&s, pos);
	}
	printf("��2��λ�ò��Ҳ�ɾ����");
	SeqListPrint(&s);
}

int main()
{
	test();

	return 0;
}