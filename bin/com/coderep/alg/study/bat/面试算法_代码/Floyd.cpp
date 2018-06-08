// Floyd.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <vector>
using namespace std;

#define INFINITY	10000

void Floyd(const vector<vector<int> >& graph, vector<vector<int> >& sp)
{
	sp = graph;
	int size = (int)graph.size();
	int k,i,j;
	for(k = 0; k < size; k++)
	{
		for(i = 0; i < size; i++)
		{
			for(j = 0; j < size; j++)
			{
				if(sp[i][j] > sp[i][k] + sp[k][j])
				{
					sp[i][j] = sp[i][k] + sp[k][j];
				}
			}
		}
	}
}


void Floyd2(const vector<vector<int> >& graph,
	vector<vector<int> >& sp, vector<vector<int> >& next)
{
	sp = graph;
	int size = (int)graph.size();
	int k,i,j;
	for(i = 0; i < size; i++)
		for(j = 0; j < size; j++)
			next[i][j] = j;	//直接后继

	for(k = 0; k < size; k++)
	{
		for(i = 0; i < size; i++)
		{
			for(j = 0; j < size; j++)
			{
				if(sp[i][j] > sp[i][k] + sp[k][j])
				{
					sp[i][j] = sp[i][k] + sp[k][j];
					next[i][j] = next[i][k];
				}
			}
		}
	}
}

void Print(const vector<vector<int> >& graph)
{
	int size = (int)graph.size();
	int i,j;
	cout << '\t';
	for(i = 0; i < size; i++)
		cout << i << '\t';
	cout << '\n';

	for(i = 0; i < size; i++)
	{
		cout << i << ":\t";
		for(j = 0; j < size; j++)
		{
			if(graph[i][j] == INFINITY)
				cout << "-\t";
			else
				cout << graph[i][j] << '\t';
		}
		cout << '\n';
	}
	cout << "======\n\n\n";
}

void Print(int start, int end, int length, const vector<int>& a)
{
	if(length == INFINITY)
		return;
	//cout << '(' << start+1 << " , " << end+1 << "):\t";
	cout << end << ":\t";
	if(length == INFINITY)
	{
		cout << "∞\n";
		return;
	}
	cout << length << '\t';

	int size = (int)a.size();
	for(int i = 0; i < size; i++)
	{
		cout << a[i]+1;
		if(i != size-1)
			cout << " → ";
	}
	cout << '\n';
}

void Print(const vector<int>& a)
{
	int size = (int)a.size();
	for(int i = 0; i < size; i++)
	{
		cout << a[i] << '\t';
	}
	cout << '\n';
}

void MinPath(int start, int end, const vector<vector<int> >& next, vector<int>& path)
{
	path.push_back(start);
	int s = start;
	while(s != end)
	{
		s = next[s][end];
		path.push_back(s);
	}
}

void MinPath(int start, int end,
	const vector<int>& pre, vector<int>& path)
{
	path.push_back(end);
	int e = end;
	while(start != e)
	{
		e = pre[e];
		path.push_back(e);
	}
	reverse(path.begin(), path.end());
}

void Min_Floyd(const vector<vector<int> >& graph)
{
	int N = (int)graph.size();
	vector<vector<int> > sp(N, vector<int>(N, INT_MAX));	//最短路径的值
	vector<vector<int> > next(N, vector<int>(N, -1));		//直接后继
	Floyd2(graph, sp, next);

	//输出所有结点间的最短路径
	vector<int> path;
	int i,j;
	for(i = 0; i < N; i++)
	{
		for(j = 0; j < N; j++)
		{
			path.clear();
			MinPath(i, j, next, path);
			Print(i, j, sp[i][j], path);
		}
	}
}

//graph：邻接矩阵，src：源点，sp[i]：src到i的最短路径的长度
void Dijkstra(const vector<vector<int> >& graph, int src, vector<int>& sp)
{
	int N = (int)graph.size();
	vector<bool> s(N, false);	//集合S初始化为空
	sp = graph[src];			//从src到任意点的直接路径

	//将src加入集合S
	s[src] = true;
	sp[src] = 0;
	int num,k,j;
	int mp;
	for(num = 1; num < N; num++)	//将剩余的N-1个结点加入到集合S
	{
		k = -1;		//候选结点编号
		mp = -1;	//最短路径值
		for(j = 0; j < N; j++)
		{
			if(s[j])
				continue;
			if((mp < 0) || (mp > sp[j]))
			{
				mp = sp[j];
				k = j;
			}
		}
		s[k] = true;
		for(j = 0; j < N; j++)
		{
			if(s[j])
				continue;
			sp[j] = min(sp[j], sp[k]+graph[k][j]);
		}
	}
}

//graph：邻接矩阵，src：源点，sp[i]：src到i的最短路径的长度
void Dijkstra2(const vector<vector<int> >& graph, int src, vector<int>& sp, vector<int>& pre)
{
	int N = (int)graph.size();
	vector<bool> s(N, false);	//集合S初始化为空
	sp = graph[src];			//从src到任意点的直接路径

	//将src加入集合S
	s[src] = true;
	sp[src] = 0;
	int num,k,j;
	int mp;
	for(num = 1; num < N; num++)	//将剩余的N-1个结点加入到集合S
	{
		k = -1;		//候选结点编号
		mp = -1;	//最短路径值
		for(j = 0; j < N; j++)
		{
			if(s[j])
				continue;
			if((mp < 0) || (mp > sp[j]))
			{
				mp = sp[j];
				k = j;
			}
		}
		s[k] = true;
		for(j = 0; j < N; j++)
		{
			if(s[j])
				continue;
			if(sp[j] > sp[k]+graph[k][j])
			{
				sp[j] = sp[k]+graph[k][j];
				pre[j] = k;
			}
		}
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	const int N = 8;
	vector<vector<int> > graph(N, vector<int>(N, INFINITY));
	graph[0][5] = 24;
	graph[0][2] = 47;
	graph[0][4] = 70;
	graph[1][3] = 31;
	graph[1][6] = 74;
	graph[1][7] = 79;
	graph[2][1] = 55;
	graph[2][3] = 88;
	graph[2][4] = 23;
	graph[2][6] = 66;
	graph[3][7] = 29;
	graph[4][1] = 31;
	graph[4][6] = 42;
	graph[5][2] = 25;
	graph[5][3] = 120;
	graph[6][7] = 66;
	//Min_Floyd(graph);

	int src = 0;
	vector<int> sp(N);
	vector<int> pre(N, src);
	Dijkstra2(graph, 0, sp, pre);
	Print(sp);
	Print(pre);
	//输出src到其他所有结点间的最短路径
	vector<int> path;
	for(int j = 0; j < N; j++)
	{
		path.clear();
		MinPath(src, j, pre, path);
		Print(src, j, sp[j], path);
	}
	return 0;
}

