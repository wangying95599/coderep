// ReverseDigital.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <bitset>
using namespace std;

void Print(int i, int k)
{
	cout << i << '\t' << bitset<32>(k) << endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
	const int N = 100;
	int M = 32;
	unsigned a[N];
	a[0] = 0;
	for(int i = 0; i < N; i++)
	{
		a[i] = ((a[i>>1]) >> 1) | ((i&1) << (M-1));
		Print(i, a[i]);
	}
	return 0;
}

