// MaxGap.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include <algorithm>
#include <hash_map>
using namespace std;

typedef struct tagSBucket
{
	bool bValid;
	int nMin;
	int nMax;

	tagSBucket() : bValid(false) {}

	void Add(int n)	//����n���뵽Ͱ��
	{
		if(!bValid)
		{
			nMin = nMax = n;
			bValid = true;
		}
		else
		{
			if(nMax < n)
				nMax = n;
			else if(nMin > n)
				nMin = n;
		}
	}
}SBucket;
int CalcMaxGap(const int* A, int size)
{
	//����ֵ
	SBucket* pBucket = new SBucket[size];
	int nMax = A[0];
	int nMin = A[0];
	int i;
	for(i = 1; i < size; i++)	
	{
		if(nMax < A[i])
			nMax = A[i];
		else if(nMin > A[i])
			nMin = A[i];
	}

	//���ν����ݷ���Ͱ��
	int delta = nMax - nMin;
	int nBucket;	//ĳ��Ӧ�����ĸ�Ͱ��
	for(i = 0; i < size; i++)
	{
		nBucket = (A[i] - nMin) * size / delta;
		if(nBucket >= size)
			nBucket = size-1;
		pBucket[nBucket].Add(A[i]);
	}

	//������ЧͰ�ļ��
	i = 0;	//�׸�Ͱһ������Ч��
	int nGap = delta / size;	//��С���
	int gap;
	for(int j = 1; j < size; j++)	//i��ǰһ��Ͱ��j�Ǻ�һ��Ͱ
	{
		if(pBucket[j].bValid)
		{
			gap = pBucket[j].nMin - pBucket[i].nMax;
			if(nGap < gap)
				nGap = gap;
			i = j;
		}
	}
	return nGap;
}
void Print(const int* A, int size)
{
	for(int i = 0; i < size; i++)
		cout << A[i] << "\t";
	cout << endl;
}

void PrintOffset(const int* A, int size)
{
	for(int i = 1; i < size; i++)
		cout << A[i] - A[i-1] << "\t";
	cout << endl;
}

int LocalMaximum(const int* A, int size)
{
	int left = 0;
	int right = size-1;
	int mid;
	while(left < right)
	{
		mid = (left + right) / 2;
		cout << mid << endl;
		if((A[mid] > A[mid+1]))	//midһ��С��size-1
			right = mid;
		else
			left = mid+1;
	}
	return A[left];
}

void Swap(int&a ,int& b)
{
	int t = a;
	a = b;
	b = t;
}

int FirstMissNumber(int* A, int size)
{
	int miss = 1;
	int j = 0;
	while(j < size)
	{
		if((A[j] <= miss) || (A[j] >= size))
		{
			if(A[j] == miss)
				miss++;
			j++;
			continue;
		}
		if(A[j] != A[A[j]])
			Swap(A[j], A[A[j]]);
		else
		{
			A[j] = A[size-1];
			size--;
		}
	}
	return miss;
}

int _tmain(int argc, _TCHAR* argv[])
{
	const int N = 6;
	int A[N];
	for(int i = 0; i < N; i++)
		A[i] = rand() % 20;
	Print(A, N);
	cout << CalcMaxGap(A, N) << endl;
	sort(A, A+N);
	Print(A, N);
	cout << CalcMaxGap(A, N) << endl;
	return 0;
}