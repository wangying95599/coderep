// ArraySum.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <string>
#include <iostream>
using namespace std;

int a[] = {-3,-5,-2,4,2,1,3};
int size = sizeof(a) / sizeof(int);
int sum = 5;	//sum为计算的和


void Sum(int* a, int size, int& negative, int& positive)
{
	positive = 0;
	negative = 0;
	for(int i = 0; i < size; i++)
	{
		if(a[i] > 0)
			positive += a[i];
		else
			negative += a[i];
	}
}

void Print(bool* x)
{
	static int number = 0;
	number++;
	cout << number << ":\t";
	for(int i = 0; i < size; i++)
	{
		if(x[i])
			cout << a[i] << '\t';
	}
	cout << '\n';
}


//x[]为最终解，i为考察第x[i]是否加入，has表示当前的和
void EnumNumber(bool* x, int i, int has)
{
	if(i >= size)
		return;
	if(has + a[i] == sum)
	{
		x[i] = true;
		Print(x);
		x[i] = false;
	}
	x[i] = true;
	EnumNumber(x, i+1, has+a[i]);
	x[i] = false;
	EnumNumber(x, i+1, has);
}

//x[]为最终解，i为考察第x[i]是否加入，has表示当前的和
//residue是剩余数的全部和
void FindNumber(bool* x, int i, int has, int residue)
{
	if(i >= size)
		return;
	if(has + a[i] == sum)
	{
		x[i] = true;
		Print(x);
		x[i] = false;
	}
	else if((has + residue >= sum) && (has + a[i] <= sum))
	{
		x[i] = true;
		FindNumber(x, i+1, has+a[i], residue-a[i]);
	}
	if(has + residue - a[i] >= sum)
	{
		x[i] = false;
		FindNumber(x, i+1, has, residue-a[i]);
	}
}

//residue剩余的所有正数的和
void FindNumber2(bool* x, int i, int has, int negative, int positive)
{
	if(i >= size)
		return;
	if(has + a[i] == sum)
	{
		x[i] = true;
		Print(x);
		x[i] = false;
	}

	if(a[i] >= 0)
	{
		if((has + positive >= sum) && (has + a[i] <= sum))
		{
			x[i] = true;
			FindNumber2(x, i+1, has+a[i], negative, positive-a[i]);
			x[i] = false;
		}
		if(has + positive - a[i] >= sum)
		{
			x[i] = false;
			FindNumber2(x, i+1, has, negative, positive-a[i]);
		}
	}
	else
	{
		if(has + x[i] + positive >= sum)
		{
			x[i] = true;
			FindNumber2(x, i+1, has+a[i], negative-a[i], positive);
			x[i] = false;
		}
		if((has + negative <= sum) && (has + positive >= sum))
		{
			x[i] = false;
			FindNumber2(x, i+1, has, negative-a[i], positive);
		}
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	int positive,negative;
	Sum(a, size,negative, positive);
	bool* x = new bool[size];
	memset(x, 0, size);
	FindNumber2(x, 0, 0, negative, positive);
	delete[] x;
	return 0;
}

