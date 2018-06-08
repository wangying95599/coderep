// FirstMissNumber.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
using namespace std;

int FirstMissNumber(int* a, int size)
{
	a--;	//��1��ʼ��
	int i = 1;
	while(i <= size)
	{
		if(a[i] == i)
		{
			i++;
		}
		else if((a[i] < i) || (a[i] > size) || (a[i] == a[a[i]]))
		{
			a[i] = a[size];
			size--;
		}
		else //if(a[i] > i)
		{
			swap(a[a[i]], a[i]);
		}
	}
	return i;
}

int _tmain(int argc, _TCHAR* argv[])
{
	int a[] = {3,5,1,2,-3,7,4,8};
	int m = FirstMissNumber(a, sizeof(a) / sizeof(int));
	cout << m << endl;
	return 0;
}