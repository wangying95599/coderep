// Holland.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include <algorithm>
using namespace std;

void Holland2(int* a, int length)
{
	int begin = 0;
	int current = 0;
	int end = length - 1;
	while(current <= end)
	{
		if(a[current] == 2)
		{
			swap(a[end], a[current]);
			end--;
		}
		else if(a[current] == 1)
		{
			current++;
		}
		else// if(a[current == 0])
		{
			if(begin == current)
			{
				begin++;
				current++;
			}
			else
			{
				swap(a[current], a[begin]);
				begin++;
				current++;
			}
		}
	}
}
void Holland(int* a, int length)
{
	int begin = 0;
	int current = 0;
	int end = length - 1;
	while(current <= end)
	{
		if(a[current] == 2)
		{
			swap(a[end], a[current]);
			end--;
		}
		else if(a[current] == 1)
		{
			current++;
		}
		else// if(a[current == 0])
		{
			//1�������ø�ֱ�ӵ��ж�if(a[current] != a[begin])��
			//2����Ϊ���ȵĴ���ԶԶ������ȵĴ���������ֱ��ɾȥ���ж�
			if(current != begin)
				swap(a[current], a[begin]);
			begin++;
			current++;
		}
	}
}

void Hollandr(int* a, int length)
{
	int begin = 0;
	int end = length - 1;
	int current = end;
	while(current >= begin)
	{
		if(a[current] == 2)
		{
			swap(a[end], a[current]);
			end--;
			current--;
		}
		else if(a[current] == 1)
		{
			current--;
		}
		else// if(a[current == 0])
		{
			swap(a[current], a[begin]);
			begin++;
		}
	}
}
int _tmain(int argc, _TCHAR* argv[])
{
	int a[] = {0,1,2,1,1,2,0,2,1,0,2,1,0,2,1,0,2,1,0,2,0,1,2,1,0};
	int size = sizeof(a)/sizeof(int);
	Holland(a, size);

	for(int i = 0; i < size; i++)
	{
		cout << a[i];
	}
	cout << endl;
	return 0;
}

