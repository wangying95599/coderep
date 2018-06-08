// TestRandom.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <math.h>
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	const int N = 100;
	int a[N];
	int r[N];
	int i;
	for(i = 0; i < N; i++)
	{
		a[i] = i;
		r[i] = rand() % N;
	}

	int b[N];
	int j;
	for(i = 0; i < N; i++)
	{
		j = i + r[i];
		if(j >= N)
			j -= N;
		b[j] = a[i];
	}

	for(i = 0; i < N; i++)
		cout << b[i] << '\t';
	cout << endl;


	return 0;
}

