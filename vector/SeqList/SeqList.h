#pragma once

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

typedef int SLDataType;

typedef struct SeqList
{
	SLDataType* a;  //指向动态开辟的数组
	int size;        //有效数据的个数
	int capacity;    //容量
}SeqList;

//初始化
void SeqListInit(SeqList* psl);
//销毁
void SeqListDestory(SeqList* psl);

//检查容量（容量不够再扩容）
void SeqListCheckCapacity(SeqList* psl);

//任意位置的插入
void SeqListInsert(SeqList* psl, int pos, SLDataType x);
//任意位置的删除
void SeqListErase(SeqList* psl, int pos);

//尾插
void SeqListPushBack(SeqList* psl, SLDataType x);
//尾删
void SeqListPopBack(SeqList* psl);

//头插
void SeqListPushFront(SeqList* psl, SLDataType x);
//头删
void SeqListPopFront(SeqList* psl);

//输出
void SeqListPrint(SeqList* psl);

//查找（返回指定数据的下标）
int SeqListFind(SeqList* psl, SLDataType x);