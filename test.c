#include "Heap.h"

//ʵ�ֶ�����
void HeapSort(int* a, int n)
{
	//1.����
	for (int i = (n - 1 - 1) / 2; i >= 0; i--)
	{
		AdjustDown(a, n, i);
	}

	int end = n - 1;
	while (end > 0)
	{
		Swap(&a[0], &a[end]);

		//�ټ���ѡ��С��
		AdjustDown(a, end, 0);
		--end;
	}

}

int main()
{
	int a[] = { 27, 15, 19, 18, 28, 34, 65, 49, 25, 37 };
	//��ͼ���Է��ָ�����������������С�ѣ�ֻ�и��ڵ㲻���㡣���Բ��á����µ����㷨��ʵ��С��
	Heap hp;
	HeapInit(&hp, a, sizeof(a) / sizeof(HPDataType));
	//HeapSort(a, sizeof(a) / sizeof(HPDataType));   //����ʵ�ֶ�����
	HeapDestory(&hp);
	HeapPush(&hp,13);

	return 0;
}