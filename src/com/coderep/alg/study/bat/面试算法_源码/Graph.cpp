// Graph.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <vector>
#include <queue>
using namespace std;

void Print(int* p, int size)
{
	for(int i = 0; i < size; i++)
		cout << p[i] << "，";
	cout << endl;
}

const int N = 16;
int Calc(int G[N][N])
{
	int step[N];	//每个结点第几步可以达到
	int stepNumber[N];	//到每个结点有几种走法
	memset(step, 0, sizeof(int)*N);
	memset(stepNumber, 0, sizeof(int)*N);
	stepNumber[0] = 1;
	queue<int> q;	//当前搜索的结点
	q.push(0);
	int from,i,s;
	while(!q.empty())
	{
		from = q.front();
		q.pop();
		s = step[from] + 1;
		for(i = 1; i < N; i++)	//0是起点，不遍历
		{
			if(G[from][i] == 1)	//连通
			{
				//i尚未可达或发现更快的路(权值不同才可能)
				if((step[i] == 0) || (step[i] > s))
				{
					step[i] = s;
					stepNumber[i] = stepNumber[from];
					q.push(i);
				}
				else if(step[i] == s) //发现相同长度的路径
				{
					stepNumber[i] += stepNumber[from];
				}
			}
		}
	}
	return stepNumber[N-1];
}
int _tmain(int argc, _TCHAR* argv[])
{
	int G[N][N];
	memset(G, 0, sizeof(int)*N*N);
	G[0][1] = G[0][4] = 1;
	G[1][5] = G[1][0] = G[1][2] = 1;
	G[2][1] = G[2][6] = G[2][3] = 1;
	G[3][2] = G[3][7] = 1;
	G[4][0] = G[4][5] = 1;
	G[5][1] = G[5][4] = G[5][6] = G[5][9] = 1;
	G[6][2] = G[6][5] = G[6][7] = G[6][10] = 1;
	G[7][3] = G[7][6] = 1;
	G[8][9] = G[8][12] = 1;
	G[9][8] = G[9][13] = G[9][10] = 1;
	G[10][9] = G[10][14] = G[10][11] = 1;
	G[11][10] = G[11][15] = 1;
	G[12][8] = G[12][13] = 1;
	G[13][9] = G[13][12] = G[13][14] = 1;
	G[14][10] = G[14][13] = G[14][15] = 1;
	G[15][11] = G[15][14] = 1;

	cout << Calc(G) << endl;
	return 0;
}