// Arrow.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include <math.h>
using namespace std;

double Rand(double d)
{
	return rand() * d / RAND_MAX;
}

//�ڻ�ͷ��Ϊpʱ��n��·�˵�������ͷ��Ŀ
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
	int c = 0;		//����Ӯ�Ĵ���
	for(int i = 0; i < N; i++)
	{
		if(LookBeauty(p, 10001) > LookBeauty(p, 10000))
			c++;
	}
	return (double)c/N;
}

int _tmain(int argc, _TCHAR* argv[])
{
	int N = 100000;	//ģ��������
	double p = 0.9;	//�����ͷ��
	cout << Beauty(N, p) << endl;
	return 0;
}