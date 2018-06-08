// Buffon.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include <math.h>
using namespace std;

double Rand(double n)
{
	return ((double)rand() * n) / (double)(RAND_MAX);
}

double Buffon(double a, double L)	//���ߵļ������ĳ���
{
	double X = a * 100;	//ȡ�㹻�����ֽ
	double Y = a * 100;
	int N = 100000;
	int c = 0;
	double d,y;
	double x1, x2, y1, y2;
	for(int i = 0; i < N; i++)
	{
		x1 = Rand(X);
		y1 = Rand(Y);
		x2 = Rand(X);
		y2 = Rand(Y);
		d = sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
		y = (y2 - y1) * L / d + y1;
		if((int)(y1/a) != (int)(y/a))
			c++;
	}
	return 2 * L * N / (a * c);
}

int _tmain(int argc, char* argv[])
{
	double a = 100;	//���߳���
	double L;
	double pi;
	for(L = a; L > 1; L--)
	{
		pi = Buffon(a, L);
		cout << pi << '\n';
	}
	return 0;
}

