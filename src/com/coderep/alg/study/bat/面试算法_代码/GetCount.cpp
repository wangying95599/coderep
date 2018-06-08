// GetCount.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <list>
using namespace std;

int stop = 1;
int CalcCount3(int n, int* pCount, int* pPre)
{
	if(n == stop)
	{
		pCount[n] = 0;
		return 0;
	}
	if(n % 2 == 1)	//奇数
	{
		if(pCount[n-1] == 0)
			pCount[n-1] = CalcCount3(n-1, pCount, pPre);
		pPre[n] = n-1;
		pCount[n] = pCount[n-1] + 1;
	}
	else	//偶数
	{
		int n2 = n / 2;
		if((n2 >= stop) && (pCount[n2] == 0))
			pCount[n2] = CalcCount3(n2, pCount, pPre);
		if(pCount[n-1] == 0)
			pCount[n-1] = CalcCount3(n-1, pCount, pPre);

		if((n2 >= stop) && (pCount[n2] < pCount[n-1]))
		{
			pPre[n] = n2;
			pCount[n] = pCount[n2] + 1;
		}
		else
		{
			pPre[n] = n-1;
			pCount[n] = pCount[n-1] + 1;
		}
	}
	return pCount[n];
}

int CalcCount4(int n, list<int>& path)
{
	if(n == stop)
		return 0;
	while(n > stop)
	{
		if((n % 2 == 0) && (n/2 > stop))
			n /= 2;
		else	//n为奇数，或者比较小
			n--;
		path.push_back(n);
	}

	path.reverse();
	return (int)path.size();
}

int CalcCount(int n, int* pCount, int* pPre)
{
	if(n == 1)
		return 0;
	if(n % 2 == 1)	//奇数
	{
		if(pCount[n-1] == 0)
			pCount[n-1] = CalcCount(n-1, pCount, pPre);
		pPre[n] = n-1;
		pCount[n] = pCount[n-1] + 1;
	}
	else	//偶数
	{
		int n2 = n / 2;
		if(pCount[n2] == 0)
			pCount[n2] = CalcCount(n2, pCount, pPre);
		if(pCount[n-1] == 0)
			pCount[n-1] = CalcCount(n-1, pCount, pPre);

		if(pCount[n2] < pCount[n-1])
		{
			pPre[n] = n2;
			pCount[n] = pCount[n2] + 1;
		}
		else
		{
			pPre[n] = n-1;
			pCount[n] = pCount[n-1] + 1;
		}
	}
	return pCount[n];
}

int CalcCount2(int n)
{
	if(n == 1)
		return 0;
	list<int> path;
	while(n > 1)
	{
		if(n % 2 == 0)	//偶数
			n /= 2;
		else			//奇数
			n--;
		path.push_back(n);
	}
	path.reverse();

	//输出
	int s = (int)path.size();
	cout << s << ":\n";
	list<int>::const_iterator iEnd = path.end();
	for(list<int>::const_iterator i = path.begin(); i != iEnd; i++)
		cout << *i << '\t';
	cout << endl;
	return s;
}

void Print(const list<int>& path)
{
	cout << (int)path.size() << "==========:\n";
	for(list<int>::const_iterator a = path.begin(); a != path.end(); a++)
		cout << *a << "，";
	cout << endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
	int N = 201314;
	/*int* pCount = new int[N+1];
	int* pPre = new int[N+1];
	memset(pCount+1, 0, sizeof(int)*N);
	memset(pPre+1, 0, sizeof(int)*N);
	CalcCount3(N, pCount, pPre);

	cout << "Times:\t" << pCount[N] << endl;
	//求2015的变化过程
	int n = N;
	while(n != stop)
	{
		cout << pPre[n] << '\t';
		n = pPre[n];
	}
*/
	list<int> path;
	CalcCount4(N, path);
	Print(path);
	return 0;
}