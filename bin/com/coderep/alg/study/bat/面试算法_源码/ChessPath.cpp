// ChessPath.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <vector>
using namespace std;

int MinPath(vector<vector<int> >& chess, int M, int N)
{
	vector<int> pathLength(N);
	int i,j;

	//��ʼ��
	pathLength[0] = chess[0][0];
	for(j = 1; j < N; j++)
		pathLength[j] = pathLength[j-1] + chess[0][j];

	//���μ���ÿ��
	for(i = 1; i < M; i++)
	{
		pathLength[0] += chess[i][0];
		for(j = 1; j < N; j++)
		{
			if(pathLength[j-1] < pathLength[j])
				pathLength[j] = pathLength[j-1] + chess[i][j];
			else
				pathLength[j] += chess[i][j];
		}
	}
	return pathLength[N-1];
}

int _tmain(int argc, _TCHAR* argv[])
{
	const int M = 10;
	const int N = 8;
	vector<vector<int> > chess(M, vector<int>(N));

	//��ʼ�����̣�(�������)
	int i,j;
	for(i = 0; i < M; i++)
	{
		for(j = 0; j < N; j++)
			chess[i][j] = rand() % 100;
	}
	cout << MinPath(chess, M, N) << endl;
	return 0;
}