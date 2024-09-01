#include "Heap.h"

void Swap(HPDataType* p1, HPDataType* p2)  //�����ڵ�
{
	HPDataType tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}

void AdjustDown(HPDataType* a, int n, int root)  //���µ����㷨��ǰ�᣺������������С�ѻ��ߴ��(�ر���Ҫ��)
{
	int parent = root;
	int child = parent * 2 + 1;  //���跨���������Һ�����С���Ǹ�������

	while (child < n)  //���ӽڵ�λ�ó����ܵ����λ��ʱ�������ٽ���
	{
		//�ҳ����Һ�����С����һ��
		//ע�⣺���汣֤��child����Խ�磬��child+1���ܻ�Խ��(û���Һ��ӣ�С�ľ�������)���������油���ˡ�child+1 < n��������
		if (child + 1 < n && a[child + 1] < a[child])  //child+1����ʾ�Һ���  //**********�Ŵ�Ѵ˴���Ϊ: >************//
		{
			++child;  //����Һ��ӵ�ֵ�����ӵ�ֵС���������󣬸���Ϊ�Һ��������Һ�����С���Ǹ�
		}

		//������ӽڵ�ȸ��׽ڵ�С���򽻻����ڵ�
		if (a[child] < a[parent])    //**********�Ŵ�Ѵ˴���Ϊ: >************//
		{
			Swap(&a[child], &a[parent]);
			//ѭ������
			parent = child;
			child = parent * 2 + 1;
		}
		else
		{
			break;
		}
	}
}

AdjustUp(HPDataType* a, int n, int child)  //���ϵ����㷨
{
	int parent = (child - 1) / 2;
	while (child > 0)  //����д: parent >= 0,��Ϊ������ѭ�������п���֪����childΪ0ʱ��parent�Ե���0
	{
		if (a[child] < a[parent])
		{
			Swap(&a[child], &a[parent]);
			//ѭ������
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
	memcpy(php->_a, a, sizeof(HPDataType) * n); //�����ݿ������Լ����������Է�����ɾ��ģ���Ϊ����a��һ����̬���飬�޷���̬���ݵ�
	php->_size = n;
	php->_capacity = n;  //��һ�������Ǹ�һ�����ݣ���ջ�������һ��һ�����ݽ���ͬ

	//������
	//����Ϊ������������С�ѵ���ʽ
	for (int i = (n - 1 - 1) / 2; i >= 0; i--)  //�ӵ����ĵ�һ����Ҷ�ӽڵ㿪ʼ����(�����һ��Ҷ�ӽڵ�:n-1�ĸ���)
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
	php->_a[php->_size++] = x;  //ע����_size++,β�壬ͷ�岻��
	AdjustUp(php->_a, php->_size,php->_size-1);  //�Ӳ��������λ�ÿ�ʼ���ϵ���
}
void HeapPop(Heap* php) //�ѵ�ɾ����ɾ���Ѷ�Ԫ��
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