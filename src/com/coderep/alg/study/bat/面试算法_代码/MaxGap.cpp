// MaxGap.cpp : 定义控制台应用程序的入口点。
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

	void Add(int n)	//将数n加入到桶中
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
	//求最值
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

	//依次将数据放入桶中
	int delta = nMax - nMin;
	int nBucket;	//某数应该在哪个桶中
	for(i = 0; i < size; i++)
	{
		nBucket = (A[i] - nMin) * size / delta;
		if(nBucket >= size)
			nBucket = size-1;
		pBucket[nBucket].Add(A[i]);
	}

	//计算有效桶的间隔
	i = 0;	//首个桶一定是有效的
	int nGap = delta / size;	//最小间隔
	int gap;
	for(int j = 1; j < size; j++)	//i是前一个桶，j是后一个桶
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
		if((A[mid] > A[mid+1]))	//mid一定小于size-1
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