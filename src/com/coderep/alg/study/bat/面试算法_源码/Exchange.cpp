// Exchange.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <algorithm>
using namespace std;

void Print(const int* a, int size)
{
	for(int i = 0; i < size; i++)
		cout << a[i] << '\t';
	cout << endl;
}

void Print(const bool* a, int size)
{
	for(int i = 0; i < size; i++)
		cout << a[i] << '\t';
	cout << endl;
}

int Exchange0(const int* a, int size)
{
	bool* visit = new bool[size];
	memset(visit, 0, sizeof(bool)*size);
	int j;
	int c = (a[0] == 0) ? 2 : 0;
	for(int i = 0; i < size; i++)
	{
		if(visit[i] || (a[i] == i))
			continue;
		j = a[i];
		while(j != i)
		{
			c++;
			visit[j] = true;
			j = a[j];
		}
		c += 2;
	}
	c -= 2;
	delete[] visit;
	return c;
}
int _tmain(int argc, _TCHAR* argv[])
{
	int N = 12;
	int* a = new int[N];
	for(int i = 0; i < N; i++)
		a[i] = i;
	random_shuffle(a, a+N);
	cout << Exchange0(a, N) << endl;
	delete[] a;
	return 0;
}