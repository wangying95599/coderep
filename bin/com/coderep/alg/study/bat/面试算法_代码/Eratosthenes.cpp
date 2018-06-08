// Eratosthenes.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <list>
using namespace std;

void Eratosthenes(bool* a, int n)
{
	a[1] = false;//a[0]����
	int i;
	for(i = 2; i <= n; i++)	//ɸ����Ĭ��������
		a[i] = true;
	int p = 2;	//��һ��ɸ��
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
		while(!a[p])	//������һ������
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