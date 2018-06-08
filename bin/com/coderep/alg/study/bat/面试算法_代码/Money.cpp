// Money.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
using namespace std;

int Charge3(int value)
{
	int n100 = value / 100;
	int n50 = value / 50;
	int n20 = value / 20;
	int n10 = value / 10;
	int n5 = value / 5;
	int n2 = value / 2;
	int n1 = value;

	int time = 0;
	for(int c100 = 0; c100 <= n100; c100++)
	{
		for(int c50 = 0; c50 <= n50; c50++)
		{
			for(int c20 = 0; c20 <= n20; c20++)
			{
				for(int c10 = 0; c10 <= n10; c10++)
				{
					for(int c5 = 0; c5 <= n5; c5++)
					{
						for(int c2 = 0; c2 <= n2; c2++)
						{
							for(int c1 = 0; c1 <= n1; c1++)
							{
								if(100*c100 + 50*c50 + 20*c20 + 10*c10 + 5*c5 + 2*c2 + c1 == value)
								{
									time++;
									//cout << c100 << '\t' << c50 << '\t' << c20 << '\t' << c10 << '\t' << c5 << '\t' << c2 << '\t' << c1 << '\n';
								}
							}
						}
					}
				}
			}
		}
	}
	return time;
}

int Charge(int value, const int* denomination, int size)
{
	int i;
	int** dp = new int*[size];	//dp[i][j]：用i面额以下的组合成j元
	for(i = 0; i < size; i++)
		dp[i] = new int[value+1];

	int j;
	for(j = 0; j <= value; j++)	//只用面额1元的
		dp[0][j] = 1;

	for(i = 1; i < size; i++)	//先用面额小的，再用面额大的
	{
		dp[i][0] = 1;	//原因：添加任何一个面额，就是一个有效组合
		for(j = 1; j <= value; j++)
		{
			if(j >= denomination[i])
				dp[i][j] = dp[i-1][j] + dp[i][j-denomination[i]];
			else
				dp[i][j] = dp[i-1][j];
		}
	}
	int time = dp[size-1][value];

	for(i = 0; i < size; i++)	//清理内存
		delete[] dp[i];
	delete[] dp;
	return time;
}


int Charge2(int value, const int* denomination, int size)
{
	int i;
	int* dp = new int[value+1];	//dp[j]：凑成j元的组合数
	int* last = new int[value+1];

	int j;
	for(j = 0; j <= value; j++)	//只用面额1元的
	{
		dp[j] = 1;
		last[j] = 1;
	}

	for(i = 1; i < size; i++)	//先用面额小的，再用面额大的
	{
		for(j = 1; j <= value; j++)
		{
			if(j >= denomination[i])
				dp[j] = last[j] + dp[j-denomination[i]];
		}
		memcpy(last, dp, sizeof(int)*(value+1));
	}
	int chargeTimes = dp[value];

	delete[] last;
	delete[] dp;
	return chargeTimes;
}
int _tmain(int argc, _TCHAR* argv[])
{
	int denomination[] = {1,2,5,10,20,50,100};	//面额
	int size = sizeof(denomination) / sizeof(int);
	int value = 1;
	while(value < 1000)
	{
		int c = Charge(value, denomination, size);
		//cout << c << endl;
		int c2 = Charge2(value, denomination, size);
		//cout << c2 << endl;
		if(c != c2)
			cout << value << endl;
		//else
		//	cout << "EROROR\n";
		value++;
	}
	return 0;
}