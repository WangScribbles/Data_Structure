#include "Heap.h"

void Test()
{
	int a[] = { 27, 15, 19, 18, 28, 34, 65, 49, 25, 37 };
	Heap hp;
	HeapInit(&hp, a, sizeof(a) / sizeof(HPDataType));
	HeapPush(&hp, 100);

}
void SortTest()
{
	int a[] = { 37, 359, 20, 5, 10, 435, 34, 64, 8,4234 };
	HeapSort(a, sizeof(a) / sizeof(a[0]));
	for (int i = 0; i < sizeof(a) / sizeof(a[0]); i++)
	{
		printf("%d ", a[i]);
	}
}

int main()
{
	//InitTest();
	SortTest();

	return 0;
}