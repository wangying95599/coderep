// SecondMax2.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
using namespace std;

void Select(const int* a, int size, int& nMax, int& nSecondMax)
{
	nMax = a[0];
	bool bSecond = false;	//�ڶ������δ����ֵ
	for(int i = 1; i < size; i++)
	{
		if(nMax < a[i])
		{
			nSecondMax = nMax;
			nMax = a[i];
		}
		else if(!bSecond || (nSecondMax < a[i]))
		{
			nSecondMax = a[i];
			bSecond = true;
		}
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	int nMax, nSecondMax;
	int a[] = {12,5,5,8,8,10,3,4};
	Select(a, sizeof(a)/sizeof(int), nMax, nSecondMax);
	cout << nMax << endl;
	cout << nSecondMax << endl;
	return 0;
}


