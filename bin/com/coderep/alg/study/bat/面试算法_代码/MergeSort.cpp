// MergeSort.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
using namespace std;

void Print(const int* p, int size)
{
	for(int i = 0; i < size; i++)
		cout << p[i] << '\t';
	cout << endl;
}

int temp[100];
void Merge(int* a, int low, int mid, int high, int& count)
{
	int i = low;
	int j = mid+1;
	int size = 0;
	for(;(i <= mid) && (j <= high); size++)
	{
		if(a[i] < a[j])
		{
			temp[size] = a[i++];
		}
		else
		{
			count += (j - mid);
			temp[size] = a[j++];
		}
	}
	while(i <= mid)
		temp[size++] = a[i++];
	while(j <= high)
		temp[size++] = a[j++];

	for(i = 0; i < size; i++)
		a[low+i] = temp[i];
}
void MergeSort(int* a, int low, int high, int& count)
{
	if(low >= high)
		return;

	int mid = (low + high) / 2;
	MergeSort(a, low, mid, count);
	MergeSort(a, mid+1, high, count);
	Merge(a, low, mid, high, count);
}

int _tmain(int argc, _TCHAR* argv[])
{
	int a[] = {3,56,2,7};
	int size = sizeof(a) / sizeof(int);
	int count = 0;
	MergeSort(a, 0, size-1, count);
	cout << count << endl;
	return 0;
}