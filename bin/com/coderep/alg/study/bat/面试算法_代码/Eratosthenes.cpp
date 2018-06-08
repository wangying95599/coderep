// Eratosthenes.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <list>
using namespace std;

void Eratosthenes(bool* a, int n)
{
	a[1] = false;//a[0]不用
	int i;
	for(i = 2; i <= n; i++)	//筛法，默认是素数
		a[i] = true;
	int p = 2;	//第一个筛孔
	int j = p*p;
	int c = 0;
	while(j <= n)
	{
		while(j <= n)
		{
			a[j] = false;
			j += p;
		}
		p++;
		while(!a[p])	//查找下一个素数
			p++;
		j = p*p;
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	int N = 1000000;
	bool* num = new bool[N+1];
	Eratosthenes(num, N);
	list<int> p;
	for(int i = 1; i <= N; i++)
	{
		if(num[i])
			p.push_back(i);
	}

	cout << "The Number of Prime is:\n";
	for(list<int>::iterator it = p.begin(); it != p.end(); it++)
		cout << *it << '\t';
	cout << endl;
	return 0;
}