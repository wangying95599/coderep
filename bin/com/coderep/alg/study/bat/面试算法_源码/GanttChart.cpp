// GanttChart.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <algorithm>
using namespace std;

typedef struct tagSItem
{
	int t;
	int nIndex;
	bool bFirst;

	bool operator < (struct tagSItem& item) const
	{
		return t < item.t;
	}
}SItem;

void GanttChart(const int* a, const int* b, int* c, int size)
{
	int i;
	int s2 = 2*size;
	//整理数据
	SItem* pItem = new SItem[s2];
	for(i = 0; i < size; i++)
	{
		pItem[i].t = a[i];
		pItem[i].nIndex = i;
		pItem[i].bFirst = true;

		pItem[size+i].t = b[i];
		pItem[size+i].nIndex = i;
		pItem[size+i].bFirst = false;
	}
	sort(pItem, pItem+s2);

	bool* bArrage = new bool[size];	//d[i]：第i号已经安排
	for(i = 0; i < size; i++)
		bArrage[i] = false;
	int from = 0;
	int to = size-1;
	for(i = 0; i < s2; i++)
	{
		if(bArrage[pItem[i].nIndex])	//pItem[i].nIndex已经确定
			continue;
		bArrage[pItem[i].nIndex] = true;
		if(pItem[i].bFirst)
		{
			c[from] = pItem[i].nIndex;
			from++;
		}
		else
		{
			c[to] = pItem[i].nIndex;
			to--;
		}
		if(to - from < 0)	//提前退出
			break;
	}
	delete[] pItem;
	delete[] bArrage;
}
int _tmain(int argc, _TCHAR* argv[])
{
	int a[] = {8,6,2,4};
	int b[] = {3,1,3,12};
	int n = sizeof(a) / sizeof(int);
	int*c = new int[n];
	GanttChart(a, b, c, n);
	Print(c, n);
	delete[] c;
	return 0;
}
void Print(const int* a, int size)
{
	for(int i = 0; i < size; i++)
		cout << a[i] << '\t';
	cout << endl;
}
