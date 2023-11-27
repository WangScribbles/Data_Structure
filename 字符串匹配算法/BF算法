//BF算法
//主串长M，字串长N
//时间复杂度：O(M * N)

#include <stdio.h>
#include <assert.h>
#include <string.h>

int BF(char* str, char* sub)
{
	assert(str && sub);
	
	int lenStr = strlen(str);
	int lenSub = strlen(sub);
	
	int i = 0;
	int j = 0;
	
	while (i < lenStr && j < lenSub)
	{
		if (str[i] == sub[j])
		{
			i++;
			j++;
		}
		else
		{
			i = i - j + 1;
			j = 0;
		}
	}
	
	if (j >= lenSub)  //j走完了字串，找到了
		return i - j;
	else
		return -1;    //i走完了主串，没找到
}

int main()
{
	int ret1 = BF("abcdef", "bcd");   //1
	int ret2 = BF("abcdef", "fgh");   //-1
	int ret3 = BF("abcdef", "abcd");  //0
	
	printf("%d %d %d", ret1, ret2, ret3);
	
	return 0;	
}
