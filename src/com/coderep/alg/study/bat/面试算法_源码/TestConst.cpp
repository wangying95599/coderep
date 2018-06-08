// TestConst.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	const int c = 5;
	int* p = (int*)&c;
	*p = 6;
	cout << c;
	int x = c;

	int i = 8;
	int j = i;
	int* p2 = &i;
	return 0;
}

