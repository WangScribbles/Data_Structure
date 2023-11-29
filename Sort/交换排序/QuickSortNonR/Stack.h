#pragma once
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

typedef int STDataType;

typedef struct Stack
{
	STDataType* _a;
	int _top;  //栈顶下标
	int _capacity;
}Stack;

//初始化和销毁
void StackInit(Stack* pst);
void StackDestory(Stack* pst);

//入栈和出栈
void StackPush(Stack* pst, STDataType x);
void StackPop(Stack* pst);

//获取栈顶的数据
STDataType StackTop(Stack* pst);

//返回1是空，返回0是非空
int StackEmpty(Stack* pst); 

//获取数据个数
int StackSize(Stack* pst);