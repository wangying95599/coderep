// PostOrder.cpp : 定义控制台应用程序的入口点。
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
	int nRight = size-2;	//size-1是根
	while(nRight >= 0)
	{
		if(a[nRight] < root)
			break;
		nRight--;
	}
	if(nRight != nLeft-1)	//无法根据root分成两部分
		return false;

	return CanPostOrder(a, nLeft)			//左子树
	&& CanPostOrder(a+nLeft, size-nLeft-1);	//右子树
}

int _tmain(int argc, _TCHAR* argv[])
{
	int a[] = {1,2,5,4,3};
	bool b = CanPostOrder(a, sizeof(a)/sizeof(int));
	cout << b << endl;
	return 0;
}