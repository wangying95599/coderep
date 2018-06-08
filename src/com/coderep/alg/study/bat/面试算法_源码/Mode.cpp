// Mode.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
using namespace std;

int Mode(int* a, int size)
{
	int count = 0;
	int m = a[0];
	for(int i = 0; i < size; i++)
	{
		if(count == 0)
		{
			m = a[i];
			count = 1;
		}
		else if(m != a[i])
		{
			count--;
		}
		else	//if(m == a[i])
		{
			count++;
		}
	}
	return m;
}

int _tmain(int argc, _TCHAR* argv[])
{
	int a[] = {8,8,1,1,1,8,1,1,6,1,8};
	int m = Mode(a, sizeof(a)/sizeof(int));
	cout << m << endl;
	return 0;
}