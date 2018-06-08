// SquareCut.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <vector>
using namespace std;

bool IsSquare(int a, int* nSquare)
{
	if(nSquare[a] == 0)
	{
		int x = a/2;	//x�㹻��ʱ��x����a��ƽ����
		int t = a;
		while(x < t)	//��ֵС��ԭֵ
		{
			t = x;		//��¼ԭ����ֵ
			x = (x + a/x)/2;	//xֵ����
		}
		nSquare[a] = (x*x == a) ? 1 : 2;
	}
	if(nSquare[a] == 1)
		return true;
	return false;
}
int SquareCut(int a, int* pre, int* nSquare, int* minCut)
{
	if(minCut[a] == 0)	//a��δ�����
	{
		if(IsSquare(a, nSquare))	//���a����ȫƽ����
		{
			minCut[a] = 1;
			pre[a] = 0;
		}
		else	//�������з�
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
	int x = a/2;	//x�㹻��ʱ��x����a��ƽ����
	int t = a;
	while(x < t)		//��ֵС��ԭֵ
	{
		t = x;			//��¼ԭ����ֵ
		x = (x + a/x)/2;	//xֵ����
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
		K = GetSquare(n);	//n��ƽ������ȡ��
		if(K*K == n)
		{
			minCut[n] = 1;
			pre[n] = 0;
			continue;
		}
		minCut[n] = n;	//Ĭ�Ϸֳ�n��
		pre[n] = n-1;	//n�ݣ���ǰ����n-1
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
	int* pre = new int[N+1];	//pre[i]��i��ǰһ������ֵ(0δ��)
	int* minCut = new int[N+1];	//minCut[i]��i����С������(0δ��)
	SquareCut2(N, pre, minCut);
	Print(N, pre);
	delete[] pre;
	delete[] minCut;
	return 0;
}