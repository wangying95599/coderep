// Bucket.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <string>
#include <vector>
using namespace std;

int GetDigital(int number, int d)
{
	int top = 0;	//最高位
	int topD = 0;	//待求的第d高位
	int t = number;
	while(d != 0)
	{
		top = t;
		t /= 10;
		d--;
	}
	while(t != 0)
	{
		top = t;
		topD = number % 10;
		number /= 10;
		t /= 10;
	}
	return topD;
}

void MaxNumber(int* a, int size, int d, int* b, int& n)
{
	vector<vector<int> > bucket(10, vector<int>());
	int i;
	for(i = 0; i < size; i++)
	{
		bucket[GetDigital(a[i], d)].push_back(a[i]);
	}

	for(i = 9; i >= 0; i--)
	{
		vector<int>::iterator it = bucket[i].begin();
		while(it != bucket[i].end())
		{
			if(*it == i)
			{
				b[n] = i;
				n++;
				it = bucket[i].erase(it);
			}
			else
			{
				it++;
			}
		}

		int s = (int)bucket[i].size();
		if(s == 0)
			continue;
		if(s == 1)
		{
			b[n] = bucket[i].front();
			n++;
		}
		else
		{
			MaxNumber(&bucket[i].front(), s, d+1, b, n);
		}
	}
}

void Print(int* a, int size)
{
	for(int i = 0; i < size; i++)
		cout << a[i] << '.';
	cout << "\n\n";
}

void Print2(int* a, int size)
{
	for(int i = 0; i < size; i++)
		cout << a[i] << "  ";
	cout << "\n\n";
}

int _tmain(int argc, _TCHAR* argv[])
{
	const int N = 100;
	int a[N];
	for(int i = 0; i < N; i++)
		a[i] = rand() % 100;
	Print2(a, N);

	int size = sizeof(a) / sizeof(int);
	int* s = new int[size];
	int n = 0;
	MaxNumber(a, size, 0, s, n);
	Print(s, n);
	return 0;
}

