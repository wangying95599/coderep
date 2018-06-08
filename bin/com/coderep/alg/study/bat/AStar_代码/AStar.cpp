// AStart.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <fstream>
#include <vector>
#include <math.h>
#include <iostream>
using namespace std;

#define INFINITY	10000000

class CPoint
{
public:
	float x;
	float y;
	char name[30];
public:
	CPoint() {}
	CPoint(float X, float Y, const char* n) : x(X), y(Y)
	{
		strcpy_s(name, n);
	}

	static float Distance(const CPoint& p1, const CPoint& p2)
	{
		float x = p1.x - p2.x;
		float y = p1.y - p2.y;
		return sqrt(x*x + y*y);
	}
};

//计算start到end的最短距离，其中graph[i][j]为i-j之间的距离，p[i]为第i个城市的坐标和名称
void AStar(const vector<vector<float> >& graph, int start, int end, const vector<CPoint>& p)
{
	int N = (int)graph.size();
	int* type = new int[N];		//0：新点，1：边点，2：内点
	float* f = new float[N];	//经过f[i]的start到end的估计值
	float* g = new float[N];	//从start到g[i]的精确值
	float* h = new float[N];	//从h[i]到end的估计值
	int* pre = new int[N];		//pre[i]:i的前驱

	//初始化
	int k;
	for(k = 0; k < N; k++)
	{
		g[k] = graph[start][k];					//到点距离
		h[k] = CPoint::Distance(p[k], p[end]);	//离点距离
		f[k] = g[k] + h[k];						//总距离
		pre[k] = -1;
		type[k] = 0;
	}

	//start加入边点集合
	type[start] = 1;
	g[start] = 0;
	f[start] = h[start];

	float d;
	int j = start;
	while(j != end)	//尚未到达end
	{
		//选择边点集合中f[i]最小的
		j = -1;
		for(k = 0; k < N; k++)
		{
			if(type[k] != 1)	//k必须是边点
				continue;
			if((j == -1) || (d > f[k]))
			{
				d = f[k];
				j = k;
			}
		}

		for(k = 0; k < N; k++)
		{
			if(graph[j][k] >= INFINITY)
				continue;
			if(type[k] == 0)
			{
				if(g[k] > g[j] + graph[j][k])
				{
					g[k] = g[j] + graph[j][k];
					f[k] = g[k] + h[k];
				}
				type[k] = 1;
				pre[k] = j;
			}
			else if(type[k] == 2)	//i是内点
			{
				if(g[k] > g[j] + graph[j][k])
				{
					g[k] = g[j] + graph[j][k];
					f[k] = g[k] + h[k];
					type[k] = 1;
					pre[k] = j;
				}
			}
			else if(type[k] == 1)
			{
				if(g[k] > g[j] + graph[j][k])
				{
					g[k] = g[j] + graph[j][k];
					f[k] = g[k] + h[k];
					pre[k] = j;
				}
			}
		}
		type[j] = 2;	//边点变成内点
	}

	//恢复路径
	vector<int> path;
	path.push_back(end);
	while(pre[end] != -1)
	{
		end = pre[end];
		path.push_back(end);
	}
	reverse(path.begin(), path.end());

	//输出路径的结点
	float m = 0;
	for(k = 0; k < (int)path.size(); k++)
	{
		cout << p[path[k]].name << '\n';
		if(k != 0)
			m += graph[path[k-1]][path[k]];
	}
	cout << m << '\n';
	delete[] f;
	delete[] g;
	delete[] h;
	delete[] pre;
	delete[] type;
}

float Rand(float a, float b)
{
	return (rand()*(b-a) / RAND_MAX) + a;
}

int _tmain(int argc, _TCHAR* argv[])
{
	ifstream iFile;
	iFile.open("D:\\Python\\A_数据.txt");
	float x, y;
	char str[30];
	vector<CPoint> p;
	while(iFile >> x >> y)
	{
		iFile >> str;
		p.push_back(CPoint(x/1000, y/1000, str));
	}
	iFile.close();

	int N = (int)p.size();
	vector<vector<float> > graph(N, vector<float>(N));
	int i,j;
	for(i = 0; i < N; i++)
	{
		for(j = i; j < N; j++)
		{
			graph[i][j] = CPoint::Distance(p[i], p[j]);
			if(graph[i][j] < 300)
				graph[j][i] = graph[i][j];
			else
				graph[j][i] = graph[i][j] = INFINITY;
		}
	}
	AStar(graph, 0, N-1, p);	//北京 - 台北
	return 0;
}

