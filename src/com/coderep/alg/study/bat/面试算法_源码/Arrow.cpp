// Arrow.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <math.h>
using namespace std;

double Rand(double d)
{
	return rand() * d / RAND_MAX;
}

//在回头率为p时，n个路人的期望回头数目
int LookBeauty(double p, int n)
{
	int c = 0;
	for(int i = 0; i < n; i++)
	{
		if(Rand(1.0) < p)
			c++;
	}
	return c;
}

double Beauty(int N, double p)
{
	int c = 0;		//貂蝉赢的次数
	for(int i = 0; i < N; i++)
	{
		if(LookBeauty(p, 10001) > LookBeauty(p, 10000))
			c++;
	}
	return (double)c/N;
}

int _tmain(int argc, _TCHAR* argv[])
{
	int N = 100000;	//模拟计算次数
	double p = 0.9;	//先验回头率
	cout << Beauty(N, p) << endl;
	return 0;
}