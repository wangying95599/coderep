// SquareCut.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <vector>
using namespace std;

bool IsSquare(int a, int* nSquare)
{
	if(nSquare[a] == 0)
	{
		int x = a/2;	//x足够大时，x大于a的平方根
		int t = a;
		while(x < t)	//新值小于原值
		{
			t = x;		//记录原来的值
			x = (x + a/x)/2;	//x值更新
		}
		nSquare[a] = (x*x == a) ? 1 : 2;
	}
	if(nSquare[a] == 1)
		return true;
	return false;
}
int SquareCut(int a, int* pre, int* nSquare, int* minCut)
{
	if(minCut[a] == 0)	//a尚未计算过
	{
		if(IsSquare(a, nSquare))	//如果a是完全平方数
		{
			minCut[a] = 1;
			pre[a] = 0;
		}
		else	//否则，则切分
		{
			minCut[a] = a;
			pre[a] = a-1;
			int c;
			int i = 1;
			while(i*i < a)
			{
				c = SquareCut(a-i*i, pre, nSquare, minCut) + 1;
				if(c < minCut[a])
				{
					minCut[a] = c;
					pre[a] = a-i*i;
				}
				i++;
			}
		}
	}
	return minCut[a];
}


int GetSquare(int a)
{
	if(a == 1)
		return 1;
	int x = a/2;	//x足够大时，x大于a的平方根
	int t = a;
	while(x < t)		//新值小于原值
	{
		t = x;			//记录原来的值
		x = (x + a/x)/2;	//x值更新
	}
	if(x*x > a)
		return x-1;
	return x;
}

void SquareCut2(int N, int* pre, int* minCut)
{
	int n,k,K,t;
	for(n = 1; n <= N; n++)
	{
		K = GetSquare(n);	//n的平方根下取整
		if(K*K == n)
		{
			minCut[n] = 1;
			pre[n] = 0;
			continue;
		}
		minCut[n] = n;	//默认分成n份
		pre[n] = n-1;	//n份，则前驱是n-1
		for(k = 1; k <= K; k++)
		{
			t = n-k*k;
			if(minCut[n] > minCut[t]+1)
			{
				minCut[n] = minCut[t]+1;
				pre[n] = t;
			}
		}
	}
}

void Print(int a, const int* pre)
{
	while(a != 0)
	{
		cout << a - pre[a] << '-' << GetSquare(a - pre[a]) << '\t';
		a = pre[a];
	}
	cout << endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
	int N = 12;
	int* pre = new int[N+1];	//pre[i]：i的前一个划分值(0未用)
	int* minCut = new int[N+1];	//minCut[i]：i的最小划分数(0未用)
	SquareCut2(N, pre, minCut);
	Print(N, pre);
	delete[] pre;
	delete[] minCut;
	return 0;
}