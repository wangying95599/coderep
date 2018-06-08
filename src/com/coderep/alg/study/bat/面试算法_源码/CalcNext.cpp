// CalcNext.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <string>
//using namespace std;

void GetNext(char* p,int next[])
{
	int pLen = strlen(p);
	next[0] = -1;
	int k = -1;
	int j = 0;
	while (j < pLen - 1)
	{
		if (k == -1 || p[j] == p[k]) 
		{
			++j;
			++k;
		}
		else 
		{
			k = next[k];
		}
	}
}


void GetNext2(char* p,int next[])
{
	int pLen = strlen(p);
	next[0] = -1;
	int k = -1;
	int j = 0;
	while (j < pLen - 1)
	{
		if (k == -1 || p[j] == p[k]) 
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

int _tmain(int argc, _TCHAR* argv[])
{
	char* pattern = "abaabcaba";
	int next[30];
	getNext(pattern, next);
	return 0;
}

