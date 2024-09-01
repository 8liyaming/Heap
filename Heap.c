#include "Heap.h"

void Swap(HPDataType* p1, HPDataType* p2)  //交换节点
{
	HPDataType tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}

void AdjustDown(HPDataType* a, int n, int root)  //向下调整算法，前提：左右子树都是小堆或者大堆(特别重要！)
{
	int parent = root;
	int child = parent * 2 + 1;  //假设法：假设左右孩子中小的那个是左孩子

	while (child < n)  //孩子节点位置超出总的最大位置时即不用再交换
	{
		//找出左右孩子中小的那一个
		//注意：上面保证了child不会越界，但child+1可能会越界(没有右孩子，小的就是左孩子)，故在下面补上了“child+1 < n”的条件
		if (child + 1 < n && a[child + 1] < a[child])  //child+1即表示右孩子  //**********排大堆此处改为: >************//
		{
			++child;  //如果右孩子的值比左孩子的值小，则假设错误，更正为右孩子是左右孩子中小的那个
		}

		//如果孩子节点比父亲节点小，则交换两节点
		if (a[child] < a[parent])    //**********排大堆此处改为: >************//
		{
			Swap(&a[child], &a[parent]);
			//循环迭代
			parent = child;
			child = parent * 2 + 1;
		}
		else
		{
			break;
		}
	}
}

AdjustUp(HPDataType* a, int n, int child)  //向上调整算法
{
	int parent = (child - 1) / 2;
	while (child > 0)  //不能写: parent >= 0,因为从下面循环迭代中可以知道当child为0时，parent仍等于0
	{
		if (a[child] < a[parent])
		{
			Swap(&a[child], &a[parent]);
			//循环迭代
			child = parent;
			parent = (child - 1) / 2;
		}
		else
		{
			break;
		}
	}
}

void HeapInit(Heap* php, HPDataType* a, int n)
{
	php->_a = (HPDataType*)malloc(sizeof(HPDataType) * n);
	memcpy(php->_a, a, sizeof(HPDataType) * n); //将数据拷贝到自己的数组上以方便增删查改，因为给的a是一个静态数组，无法动态增容等
	php->_size = n;
	php->_capacity = n;  //堆一上来就是给一堆数据，与栈、链表等一个一个数据进不同

	//构建堆
	//调整为左右子树都是小堆的形式
	for (int i = (n - 1 - 1) / 2; i >= 0; i--)  //从倒数的第一个非叶子节点开始调整(即最后一个叶子节点:n-1的父亲)
	{
		AdjustDown(php->_a, php->_size, i);
	}
}

void HeapDestory(Heap* php)
{
	assert(php);
	free(php->_a);
	php->_a = NULL;
	php->_capacity = NULL;
	php->_size = NULL;
}
void HeapPush(Heap* php, HPDataType x)
{
	assert(php);
	if (php->_size == php->_capacity)
	{
		php->_capacity *= 2;
		HPDataType* tmp = (HPDataType*)realloc(php->_a, sizeof(HPDataType) * php->_capacity);
		php->_a = tmp;
	}
	php->_a[php->_size++] = x;  //注意是_size++,尾插，头插不行
	AdjustUp(php->_a, php->_size,php->_size-1);  //从插入的数据位置开始向上调整
}
void HeapPop(Heap* php) //堆的删除是删除堆顶元素
{
	assert(php);
	assert(php->_size > 0);

	Swap(&php->_a[0], &php->_a[php->_size - 1]);
	php->_size--;

	AdjustDown(php->_a, php->_size, 0);
}
HPDataType HeapTop(Heap* php)
{
	assert(php);
	assert(php->_size > 0);

	return php->_a[0];
}