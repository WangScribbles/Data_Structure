//KMP算法
//主串长M，模式串长N
//时间复杂度：O(M + N)
//其中求next数组时间复杂度是O(M)
//模式匹配过程的最坏时间复杂度为O(N)

#include <stdio.h>
#include <assert.h>
#include <string.h>
#incldue <stdlib.h>

void GetNext(char* sub, int* next, int lenSub)
{
	// next中的0、1下标处元素均为默认值
	next[0] = -1;
	if (lenSub == 1)
		return;
		
	next[1] = 0;
	int i = 2;  //当前i下标
	int k = 0;  //前一项的k（第一项的k是0）

	while (i < lenSub)
	{
		if (k == -1 || sub[i - 1] == sub[k])
		{
			next[i] = k + 1;
			i++;
			k++;
		}
		else
		{
			k = next[k];
		}
	}
}





//next数组的优化（nextval）
//1、回退到的位置和当前字符一样，当前nextval值就和回退位置的nextval值相同
//2、回退到的位置和当前字符一样，当前nextval值就是当前字符原来的next值
void Getnextval(char* sub, int* nextval, int lenSub)
{
	assert(nextval && sub);
	
	nextval[0] = -1;
	//nextval[1] = 0;  //改动处
	
	int i = 1;   //改动处
	int k = -1;  //前一个下标的回退值
	
	while (i < lenSub)
	{
		if (k == -1 || sub[k] == str2[i - 1])
		{
			nextval[i] = k + 1;
			
			if (sub[i] == sub[nextval[i]])  //改动处
				nextval[i] = nextval[nextval[i]];
				
			k++;
			i++;
		}
		else
		{
			k = nextval[k];
		}
	}
}





/**
str:代表主串
sub:代表模式串
pos:代表从主串的pos位置开始找
*/
int KMP(const char* str, const char* sub, int pos)
{
	assert(str && sub);
	int lenStr = strlen(str);
	int lenSub = strlen(sub);
	
	//传入的参数有问题
	if (lenStr == 0 || lenSub == 0)
		return -1;
	if (pos < 0 || pos >= lenStr)
		return -1;


	int* next = (int*)malloc(sizeof(int) * lenSub);
	assert(next);
	GetNext(sub, next, lenSub);
	
	int i = pos;  //遍历主串
	int j = 0;    //遍历模式串
	while (i < lenStr && j < lenSub)
	{
		if (j == -1 || str[i] == sub[j])
		{
			i++;
			j++;
		}
		else
		{
			j = next[j];
		}
	}
	
	free(next);
	
	if (j >= lenSub)  //j走完了字串，找到了
		return i - j;	
	else  			  //i走完了主串，没找到
		return -1;
}

int main()
{
	int ret1 = KMP("abcdefabc", "def", 0);     //3
	int ret2 = KMP("abcdefabc", "defghi", 0);  //-1
	int ret3 = KMP("abcdefabd", "abc", 0);     //0
	
	printf("%d %d %d", ret1, ret2, ret3);

	return 0;
}
