// LIS.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <algorithm>
using namespace std;

void Insert(int* a, int& size, int x)
{
	if(size <= 0)
	{
		a[0] = x;
		size++;
		return;
	}
	int low = 0;
	int high = size-1;
	int mid;
	while(low <= high)
	{
		mid = (low+high)/2;
		if(x < a[mid])
			high = mid-1;
		else if(x >= a[mid])
			low = mid+1;
	}

	if(low >= size)
	{
		a[size] = x;
		size++;
	}
	else
	{
		if(a[low] < x)
			a[low+1] = x;
		else
			a[low] = x;
	}
}

void Print(const int* a, int size, const int* array)
{
	for(int i = 0; i < size; i++)
		cout << array[a[i]] << "  ";
	cout << endl;
}

void Print(const int* a, int size)
{
	for(int i = 0; i < size; i++)
		cout << a[i] << "  ";
	cout << endl;
}

//�ڻ�����b[0...size-1]�в���Ԫ��a[i]
void Insert2(int* b, int& size, const int* a, int i, int* pre)
{
	if(size <= 0)
	{
		b[0] = i;
		size++;
		pre[i] = -1;
		return;
	}
	int low = 0;
	int high = size-1;
	int mid;
	while(low <= high)
	{
		mid = (low+high)/2;
		if(a[i] < a[b[mid]])
			high = mid-1;
		else if(a[i] >= a[b[mid]])
			low = mid+1;
	}

	if(low >= size)
	{
		b[size] = i;
		pre[i] = b[size-1];
		size++;
	}
	else
	{
		if(a[b[low]] < a[i])
		{
			b[low+1] = i;
			pre[i] = b[low];
		}
		else
		{
			b[low] = i;
			pre[i] = (low==0) ? -1 : b[low-1];
		}
	}
}
int LIS(const int* a, int size)
{
	int* b = new int[size];		//�㹻��Ļ�����
	int s = 0;					//��������Ч����
	int* pre = new int[size];	//ǰ��
	int i;
	for(i = 0; i < size; i++)
		Insert2(b, s, a, i, pre);

	//����LIS����
	int cur = b[s-1];	//LIS�����һ��Ԫ��
	i = 0;
	while(cur != -1)
	{
		b[i] = a[cur];	//b��Ų���ڼ���LIS
		cur = pre[cur];
		i++;
	}
	reverse(b, b+s);
	Print(b, s);
	delete[] b;
	delete[] pre;
	return s;
}

int _tmain(int argc, _TCHAR* argv[])
{
	int a[] = {1,4,6,2,8,9,7};
	int size = sizeof(a) / sizeof(int);
	int len = LIS(a, size);
	cout << len << endl;
	return 0;
}