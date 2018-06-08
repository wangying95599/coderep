// Probability.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
using namespace std;

int P()
{
	return (rand() % 100 == 1) ? 1 : 0;
}

int P_Equal()
{
	int a,b;
	do{
		a = P();
		b = P();
	}while(a == b);
	return a;
}

int _tmain(int argc, _TCHAR* argv[])
{
	int c = 0;
	int p;
	for(int i = 0; i < 1000; i++)
	{
		p = P_Equal();
		cout << p;
		if(p == 1)
			c++;
	}
	cout << "\n\n\n" << c << endl;
	return 0;
}

