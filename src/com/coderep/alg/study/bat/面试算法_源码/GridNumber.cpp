// GridNumber.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <vector>
using namespace std;

void Print(vector<vector<int> >& chess, int M, int N)
{
	int i,j;
	for(i = 0; i < M; i++)
	{
		for(j = 0; j < N; j++)
			cout << chess[i][j] << '\t';
		cout << '\n';
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	int M = 19;
	int N = 19;
	int count = 0;
	int i,j;
	for(i = 1; i < M; i++)
	{
		for(j = 1; j < N; j++)
		{
			count += min(i,j);
		}
	}
	cout << "总数为：" << count << endl;
	return 0;
}
/*	vector<vector<int> > chess(M, vector<int>(N));

	//初值
	int i,j;
	for(i = 0; i < M; i++)
		chess[i][0] = 0;
	for(j = 0; j < N; j++)
		chess[j][0] = 0;

	//递推关系
	int count = 0;
	for(i = 1; i < M; i++)
	{
		for(j = 1; j < N; j++)
		{
			if(i != j)
				chess[i][j] = max(chess[i-1][j], chess[i][j-1]);
			else
				chess[i][j] = chess[i-1][j]+1;
			count += chess[i][j];
		}
	}
	Print(chess, M, N);
	cout << "总数为：" << count << endl;


	cout << "总数为：" << count << endl;
	return 0;
}*/