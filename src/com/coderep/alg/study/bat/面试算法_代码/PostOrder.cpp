// PostOrder.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
using namespace std;

bool CanPostOrder(const int* a, int size)
{
	if(size <= 1)
		return true;

	int root = a[size-1];
	int nLeft = 0;
	while(nLeft < size-1)
	{
		if(a[nLeft] > root)
			break;
		nLeft++;
	}
	int nRight = size-2;	//size-1�Ǹ�
	while(nRight >= 0)
	{
		if(a[nRight] < root)
			break;
		nRight--;
	}
	if(nRight != nLeft-1)	//�޷�����root�ֳ�������
		return false;

	return CanPostOrder(a, nLeft)			//������
	&& CanPostOrder(a+nLeft, size-nLeft-1);	//������
}

int _tmain(int argc, _TCHAR* argv[])
{
	int a[] = {1,2,5,4,3};
	bool b = CanPostOrder(a, sizeof(a)/sizeof(int));
	cout << b << endl;
	return 0;
}