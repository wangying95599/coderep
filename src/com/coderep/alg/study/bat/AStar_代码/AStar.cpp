// AStart.cpp : �������̨Ӧ�ó������ڵ㡣
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

//����start��end����̾��룬����graph[i][j]Ϊi-j֮��ľ��룬p[i]Ϊ��i�����е����������
void AStar(const vector<vector<float> >& graph, int start, int end, const vector<CPoint>& p)
{
	int N = (int)graph.size();
	int* type = new int[N];		//0���µ㣬1���ߵ㣬2���ڵ�
	float* f = new float[N];	//����f[i]��start��end�Ĺ���ֵ
	float* g = new float[N];	//��start��g[i]�ľ�ȷֵ
	float* h = new float[N];	//��h[i]��end�Ĺ���ֵ
	int* pre = new int[N];		//pre[i]:i��ǰ��

	//��ʼ��
	int k;
	for(k = 0; k < N; k++)
	{
		g[k] = graph[start][k];					//�������
		h[k] = CPoint::Distance(p[k], p[end]);	//������
		f[k] = g[k] + h[k];						//�ܾ���
		pre[k] = -1;
		type[k] = 0;
	}

	//start����ߵ㼯��
	type[start] = 1;
	g[start] = 0;
	f[start] = h[start];

	float d;
	int j = start;
	while(j != end)	//��δ����end
	{
		//ѡ��ߵ㼯����f[i]��С��
		j = -1;
		for(k = 0; k < N; k++)
		{
			if(type[k] != 1)	//k�����Ǳߵ�
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
			else if(type[k] == 2)	//i���ڵ�
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
		type[j] = 2;	//�ߵ����ڵ�
	}

	//�ָ�·��
	vector<int> path;
	path.push_back(end);
	while(pre[end] != -1)
	{
		end = pre[end];
		path.push_back(end);
	}
	reverse(path.begin(), path.end());

	//���·���Ľ��
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
	iFile.open("D:\\Python\\A_����.txt");
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
	AStar(graph, 0, N-1, p);	//���� - ̨��
	return 0;
}

