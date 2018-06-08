// CantorExpansion.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <vector>
using namespace std;

void CantorExpansionR(const int* a, int* result, int size)
{
	int i;
	vector<int> v(size);
	for(i = 0; i < size; i++)
		v[i] = i+1;

	for(i = 0; i < size; i++)
	{
		result[i] = v[a[i]];
		v.erase(v.begin()+a[i]);
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	int c[] = {3,4,1,2,1,0};
	int size = sizeof(c) / sizeof(int);
	int* a = new int[size];
	CantorExpansionR(c, a, size);
	Print(a, size);
	return 0;
}

void CantorExpansionR2(int* a, int* result, int size)
{
	memset(result, 0, sizeof(int)*size);	//赋为无效值
	int i,j;
	for(i = 0; i < size; i++)
	{
		for(j = 0; j < size; j++)
		{
			if(result[j] != 0)
				continue;
			if(a[j] == 0)
				break;
			a[j]--;
		}
		result[j] = i+1;
	}
}
void Print(const int* a, int size)
{
	for(int i = 0; i < size; i++)
		cout << a[i] << '\t';
	cout << endl;
}

void CantorExpansion(const int* a, int* b, int size)
{
	int i,j;
	for(i = 0; i < size; i++)
	{
		b[i] = 0;
		for(j = i+1; j < size; j++)
		{
			if(a[j] < a[i])
				b[i]++;
		}
	}
}

/*int _tmain(int argc, _TCHAR* argv[])
{
	int p[] = {4,6,2,5,3,1};
	int size = sizeof(p) / sizeof(int);
	int* a = new int[size];
	CantorExpansion(p, a, size);
	Print(a, size);
	delete[] a;
	return 0;
}*/
