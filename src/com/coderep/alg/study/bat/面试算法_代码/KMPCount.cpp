// KMPCount.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

void KMP(char* text, char* pattern, int* next)
{
}

int _tmain(int argc, _TCHAR* argv[])
{
	char* text = "aaaabaaaabaaaabaaaabaaaabaaaab";
	char* pattern = "aaaaa";
	int next[5] = {-1,0,1,2,3};
	KMP(text, pattern, next);
	return 0;
}

