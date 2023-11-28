#pragma once

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

typedef int SLDataType;

typedef struct SeqList
{
	SLDataType* a;  //ָ��̬���ٵ�����
	int size;        //��Ч���ݵĸ���
	int capacity;    //����
}SeqList;

//��ʼ��
void SeqListInit(SeqList* psl);
//����
void SeqListDestory(SeqList* psl);

//����������������������ݣ�
void SeqListCheckCapacity(SeqList* psl);

//����λ�õĲ���
void SeqListInsert(SeqList* psl, int pos, SLDataType x);
//����λ�õ�ɾ��
void SeqListErase(SeqList* psl, int pos);

//β��
void SeqListPushBack(SeqList* psl, SLDataType x);
//βɾ
void SeqListPopBack(SeqList* psl);

//ͷ��
void SeqListPushFront(SeqList* psl, SLDataType x);
//ͷɾ
void SeqListPopFront(SeqList* psl);

//���
void SeqListPrint(SeqList* psl);

//���ң�����ָ�����ݵ��±꣩
int SeqListFind(SeqList* psl, SLDataType x);