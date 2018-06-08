// MaxSeq.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
using namespace std;

int MaxSequence(const int* a, int size)
{
	int* p = new int[size];
	int i;
	for(i = 0; i < size; i++)
		p[i] = 1;

	int m = 1;
	for(i = 1; i < size; i++)
	{
		if(a[i] - a[i-1] == 1)
		{
			p[i] += p[i-1];
			m = max(p[i], m);
		}
	}
	delete[] p;
	return m;
}

int MaxSequence2(const int* a, int size, int& from, int& to)
{
	from = to = 0;
	int* p = new int[size];
	int i;
	for(i = 0; i < size; i++)
		p[i] = 1;

	int m = 1;
	for(i = 1; i < size; i++)
	{
		if(a[i] - a[i-1] == 1)
		{
			p[i] += p[i-1];
			m = max(p[i], m);
			to = i;
		}
	}
	from = to - m + 1;
	delete[] p;
	return m;
}

void Print(const int* a, int from, int to)
{
	while(from <= to)
		cout << a[from++] << '\t';
	cout << endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
	int a[] = {1, 2, 3, 34, 56, 57, 58, 59, 60, 61, 99, 121};
	int size = sizeof(a) / sizeof(int);
	int from = 0, to = 0;
	int m = MaxSequence(a, size);
	Print(a, from, to);
	cout << m << endl;
	return 0;
}

