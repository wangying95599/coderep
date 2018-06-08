// Island.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <queue>
using namespace std;

#define WATER	0
#define SOIL	1
#define OCEAN	2

void Print(vector<vector<int> >& land, int M, int N)
{
	int i,j;
	for(i = 0; i < M; i++)
	{
		for(j = 0; j < N; j++)
		{
			cout << land[i][j] << '\t';
		}
		cout << endl;
	}
}

bool IsOcean(vector<vector<int> >& land, int M, int N, int i, int j)
{
	if((i < 0) || (i >= M) || (j < 0) || (j >= N))
		return false;
	return land[i][j] == WATER;
}

void Ocean(vector<vector<int> >& land, int M, int N, int i, int j)
{
	queue<pair<int,int> > q;
	q.push(make_pair(i,j));
	int iDirect[] = {-1,1,0,0};
	int jDirect[] = {0,0,-1,1};
	int iCur,jCur;
	int k;
	while(!q.empty())
	{
		i = q.front().first;
		j = q.front().second;
		q.pop();
		for(k = 0; k < 4; k++)
		{
			iCur = i + iDirect[k];
			jCur = j + jDirect[k];
			if(IsOcean(land, M, N, iCur, jCur))
			{
				q.push(make_pair(iCur,jCur));
				land[iCur][jCur] = OCEAN;
			}
		}
	}
}

void FillLake(vector<vector<int> >& land, int M, int N)
{
	int i,j;

	//从边缘开始，获得海洋区域
	for(i = 0; i < M; i++)
	{
		if(land[i][0] == WATER)
			Ocean(land, M, N, i, 0);
		if(land[i][N-1] == WATER)
			Ocean(land, M, N, i, N-1);
	}
	for(j = 1; j < N-1; j++)
	{
		if(land[0][j] == WATER)
			Ocean(land, M, N, 0, j);
		if(land[M-1][j] == WATER)
			Ocean(land, M, N, M-1, j);
	}

	//恢复海洋，填湖
	for(i = 0; i < M; i++)
	{
		for(j = 0; j < N; j++)
		{
			if(land[i][j] == OCEAN)	//是海洋，恢复成水
				land[i][j] = WATER;
			else if(land[i][j] == WATER)//是湖泊
				land[i][j] = SOIL;		//填湖
		}
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	const int M = 10;
	const int N = 10;
	//随机生成数据
	vector<vector<int> > land(M, vector<int>(N));
	int i,j;
	for(i = 0; i < M; i++)
	{
		for(j = 0; j < N; j++)
		{
			land[i][j] = ((rand() % 3) == 0) ? WATER : SOIL;
		}
	}

	Print(land, M, N);
	FillLake(land, M, N);	//围湖造田
	Print(land, M, N);
	return 0;
}