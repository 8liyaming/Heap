#include "Heap.h"

//实现堆排序
void HeapSort(int* a, int n)
{
	//1.建堆
	for (int i = (n - 1 - 1) / 2; i >= 0; i--)
	{
		AdjustDown(a, n, i);
	}

	int end = n - 1;
	while (end > 0)
	{
		Swap(&a[0], &a[end]);

		//再继续选次小的
		AdjustDown(a, end, 0);
		--end;
	}

}

int main()
{
	int a[] = { 27, 15, 19, 18, 28, 34, 65, 49, 25, 37 };
	//画图可以发现该树的左右子树都是小堆，只有根节点不满足。可以采用“向下调整算法”实现小堆
	Heap hp;
	HeapInit(&hp, a, sizeof(a) / sizeof(HPDataType));
	//HeapSort(a, sizeof(a) / sizeof(HPDataType));   //用于实现堆排序
	HeapDestory(&hp);
	HeapPush(&hp,13);

	return 0;
}