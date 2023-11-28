#define _CRT_SECURE_NO_WARNINGS 1
#include "SeqList.h"

void test()
{
	SeqList s;

	//初始化
	SeqListInit(&s);

	//尾插
	SeqListPushBack(&s, 1);
	SeqListPushBack(&s, 2);
	SeqListPushBack(&s, 3);
	SeqListPushBack(&s, 4);
	SeqListPushBack(&s, 5);
	printf("尾插后：");
	SeqListPrint(&s);

	//尾删
	SeqListPopBack(&s);
	printf("尾删后：");
	SeqListPrint(&s);

	//头插
	SeqListPushFront(&s, 7);
	printf("头插后：");
	SeqListPrint(&s);

	//头删
	SeqListPopFront(&s);
	printf("头删后：");
	SeqListPrint(&s);

	//任意位置插入
	SeqListInsert(&s, 3, 18);
	printf("第4个位置插入后：");
	SeqListPrint(&s);

	//任意位置删除
	SeqListErase(&s, 3);
	printf("第4个位置删除后：");
	SeqListPrint(&s);

	//指定数据（配合查找函数）
	int pos = SeqListFind(&s, 2);
	if (pos != -1)
	{
		SeqListErase(&s, pos);
	}
	printf("第2个位置查找并删除后：");
	SeqListPrint(&s);
}

int main()
{
	test();

	return 0;
}