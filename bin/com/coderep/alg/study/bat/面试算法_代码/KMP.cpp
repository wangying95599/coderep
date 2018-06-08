// KMP.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
using namespace std;

void GetNext(char* p,int next[])
{
	int nLen = (int)strlen(p);
	next[0] = -1;
	int k = -1;
	int j = 0;
	while (j < nLen - 1)
	{
		//此刻，k即next[j-1]，且p[k]表示前缀，p[j]表示后缀
		//注：k==-1表示未找到k前缀与k后缀相等，首次分析可先忽略
		if(k == -1 || p[j] == p[k]) 
		{
			++j;
			++k;
			next[j] = k;
		}
		else	//p[j]与p[k]失配，则继续递归计算前缀p[next[k]]
		{
			k = next[k];
		}
	}
}
void GetNext2(char* p,int next[])
{
	int nLen = (int)strlen(p);
	next[0] = -1;
	int k = -1;
	int j = 0;
	while (j < nLen - 1)
	{
		if(k == -1 || p[j] == p[k]) 
		{
			++j;
			++k;
			if(p[j] == p[k])
				next[j] = next[k];
			else
				next[j] = k;
		}
		else 
		{
			k = next[k];
		}
	}
}

int MinPeriod(char* p)
{
	int nLen = (int)strlen(p);
	if(nLen == 0)
		return -1;
	int* next = new int[nLen];	//仿照KMP求"伪next"
	next[0] = -1;	//哨兵：串首标志
	int k = -1;
	int j = 0;
	while (j < nLen - 1)
	{
		if((k == -1) || (p[j+1] == p[k]))
		{
			++k;
			++j;
			next[j] = k;
		}
		else
		{
			k = next[k];
		}
	}
	next[0] = 0;	//恢复成逻辑上的0

	int nLast = next[nLen-1];
	delete[] next;
	if(nLast == 0)
		return -1;
	if(nLen % (nLen-nLast) == 0)
		return nLen-nLast;
	return -1;
}
void Print(int* a, int size)
{
	for(int i = 0; i < size; i++)
		cout << a[i] << ' ';
	cout << endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
	char* pattern = "abcdabcdabcdabcdabcd";
	int next[30];
	GetNext(pattern, next);
	Print(next, 30);

	GetNext2(pattern, next);
	Print(next, 30);

	cout << MinPeriod(pattern) << endl;
	return 0;
}
