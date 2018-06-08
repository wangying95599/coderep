// Stock.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <vector>
using namespace std;

int maxProfit(int* prices, int size)
{
	int local = 0;  
	int global = 0;
	for(int i=0; i< size-1; i++)
	{  
		local = max(local+prices[i+1]-prices[i],0);  
		global = max(local, global);  
	}  
	return global;  
}

int MaxProfit(const int* prices, int size)
{
	int p = 0;
	int mn = prices[0];
	for(int i = 1; i < size; i++)
	{
		mn = min(mn, prices[i-1]);	//p[0...i-1]最小值
		p = max(p, prices[i] - mn);
	}
	return p;
}

int MaxProfitK(const int* prices, int size, int K)
{
	vector<vector<int> > dp(K+1, vector<int>(size, 0));
	int k,i,j;
	for(k = 1; k <= K; k++)
	{
		for(i = 1; i < size; i++)
		{
			dp[k][i] = dp[k][i-1];
			for(j = 0; j < i; j++)
			{
				dp[k][i] = max(dp[k][i], dp[k-1][j] + prices[i]-prices[j]);
			}
		}
	}
	return dp[K][size-1];
}

int _tmain(int argc, _TCHAR* argv[])
{
	int prices[] = {7, 1, 5, 3, 6, 4};
	cout << MaxProfitK(prices, sizeof(prices)/sizeof(int), 3) << endl;
	return 0;
}


//	MaxProfitK2(prices, sizeof(prices)/sizeof(int), 3);

int MaxProfitK2(const int* prices, int size, int K)
{
	vector<vector<int> > dp(K+1, vector<int>(size, 0));
	int k,i;
	int mx;
	for(k = 1; k <= K; k++)
	{
		mx = dp[k-1][0]-prices[0];
		for(i = 1; i < size; i++)
		{
			dp[k][i] = max(dp[k][i-1], mx+prices[i]);
			mx = max(mx, dp[k-1][i]-prices[i]);
		}
	}
	return dp[K][size-1];
}