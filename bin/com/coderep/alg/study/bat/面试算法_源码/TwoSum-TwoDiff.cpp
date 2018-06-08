// Manacher.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
using namespace std;

void Manacher(const char* str)
{
	int size = strlen(str);
	int* p = new int[2*size-1];
}

int Rand(int m)
{
	return rand() * m / RAND_MAX;
}

void Print(const int* a, int N)
{
	for(int i = 0; i < N; i++)
		cout << a[i] << '\t';
	cout << '\n';
}

void TwoDiff2(int* a, int N, int diff)
{
	sort(a, a+N);
	Print(a, N);
	int* p = new int[N];
	int i,j;
	for(i = 0; i < N; i++)
	{
		p[i] = a[i] + diff;
	}
	i = j = 0;
	while((i <= N-1) && (j <= N-1))
	{
		if(a[i] < p[j])
			i++;
		else if(a[i] > p[j])
			j++;
		else	//if(a[i] == p[j])
		{
			cout << p[j] - diff << '\t' << a[i] << '\n';
			i++;
			j++;
		}
	}
	delete[] p;
}

void TwoDiff(int* a, int N, int diff)
{
	int i,j;
	i = j = 0;
	while((i <= N-1) && (j <= N-1))
	{
		if(a[i] < a[j]+diff)
			i++;
		else if(a[i] > a[j]+diff)
			j++;
		else	//if(a[i] == a[j]+diff)
		{
			cout << a[j] << ',' << a[i] << '\n';
			i++;
			j++;
		}
	}
}


void TwoSum(int* a, int N, int sum)
{
	int i = 0;
	int j = N-1;
	while(i < j)
	{
		if(a[i] + a[j] < sum)
			i++;
		else if(a[i] + a[j] > sum)
			j--;
		else	//if(a[i] + a[j] == sum)
		{
			cout << a[i] << ',' << a[j] << '\n';
			i++;
			j--;
		}
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	int a[] = {0, 3, 7, 9, 11, 14, 16, 17};
	//sort(a, a+N);	若给定数组未排序，则先排序
	TwoSum(a, sizeof(a)/sizeof(int), 20);
	return 0;
}

