// Mouse.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <vector>
#include <iostream>
using namespace std;

void Print(const vector<int>& c)
{
	for(int i = 0; i < (int)c.size(); i++)
		cout << c[i] << '\t';
	cout << '\n';
}

void Print(const vector<vector<int> >& chess)
{
	int i;
	cout << '\t';
	for(i = 0; i < (int)chess.size(); i++)
		cout << i << ":\t";
	cout << '\n';

	for(i = 0; i < (int)chess.size(); i++)
	{
		cout << i << ":\t";
		Print(chess[i]);
	}
}

void Print(const vector<pair<int, int> >& path)
{
	for(int i = 0; i < (int)path.size(); i++)
		cout << path[i].first << ", " << path[i].second << '\n';
}

vector<vector<pair<int, int> > > all;

bool Search(const vector<vector<int> >& chess, int i, int j, 
	vector<pair<int, int> >& path, vector<vector<bool> >& visit)
{
	if(chess[i][j] == 9)
	{
		Print(path);
		return true;
	}
	int iNext[] = {0, 0, -1, 1};
	int jNext[] = {-1, 1, 0, 0};
	int iCur, jCur;
	int m = (int)chess.size();
	int n = (int)chess[0].size();
	for(int k = 0; k < 4; k++)
	{
		iCur = i + iNext[k];
		jCur = j + jNext[k];
		if ((iCur < 0) || (iCur >= m) || (jCur < 0) || (jCur >= n))
			continue;
		if(!visit[iCur][jCur] && (chess[iCur][jCur] != 0))
		{
			path.push_back(make_pair(iCur, jCur));
			visit[iCur][jCur] = true;
			if(Search(chess, iCur, jCur, path, visit))
			{
				//如果求所有路径，则将下句替换成all.push_back(path);
				return true;
			}
			path.pop_back();
			visit[iCur][jCur] = false;
		}
	}
	return false;
}

void MousePath(const vector<vector<int> >& chess)
{
	vector<pair<int, int> > path;
	vector<vector<bool> > visit(chess.size(), 
		vector<bool>(chess[0].size(), false));

	//开始路径搜索
	path.push_back(make_pair(0, 0));
	visit[0][0] = true;
	Search(chess, 0, 0, path, visit);
}

int _tmain(int argc, _TCHAR* argv[])
{
	const int N = 8;
	int c[N][N] = {
		{1, 1, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 1, 0, 0, 1},
		{1, 1, 1, 0, 1, 0, 0, 1},
		{0, 1, 0, 0, 1, 1, 1, 1},
		{0, 1, 0, 0, 0, 0, 0, 1},
		{0, 1, 0, 9, 1, 1, 1, 1},
		{0, 1, 1, 1, 0, 0, 1, 0}
	};
	vector<vector<int> > chess(N, vector<int>(N));
	for(int i = 0; i < N; i++)
		chess[i].assign(c[i], c[i]+N);

	MousePath(chess);
	return 0;
}

