// HollandFlag.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
using namespace std;

void HollandFlag(int* a, int size)
{
	int begin = 0;
	int end = size-1;
	int cur = 0;
	while(cur <= end)
	{
		if(a[cur] == 0)
		{
			swap(a[begin], a[cur]);
			begin++;
			cur++;
		}
		else if(a[cur] == 1)
		{
			cur++;
		}
		else
		{
			swap(a[cur], a[end]);
			end--;
		}
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	int a[] = {2,0,1,2,0,1,1,1,0,0,0,2,0,2,1,1,2,0,1,0,0,2,1,};
	int size = sizeof(a) / sizeof(int);
	HollandFlag(a, size);
	return 0;
}

