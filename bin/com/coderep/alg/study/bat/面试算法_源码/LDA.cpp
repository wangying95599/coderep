// LDA.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

void Init()
{
	int m,n,w,N;
	for(m = 0; m < data.M; m++)
	{
		N = LDAModel.docs[m].GetLength();
		LDAModel.z[m] = new vector<int>();

		for(n = 0; n < N; n++)
		{
			int topic = (int)(rand(1.0)*K);
			LDAModel.z[m].add(topic);
			w = data.docs[m].words[n];	//���ҵ���n�ڴʵ��еı��(word->term)
			LDAModel.nw[w][topic]++;
			LDAModel.nd[m][topic]++;
			LDAModel.nwSum[topic]++;
		}
		LDAModel.ndSum[m] = N;	//��mƪ�ĵ��Ŀ��ظ�������Ŀ
	}
}

void Estimate()
{
	for(int times = 0; times < nMaxTimes; times++)
	{
		for(int m = 0; m < LDAModel.M; m++)	//����ÿƪ�ĵ�
		{				
			for(int n = 0; n < LDAModel.docs[m].GetLength(); n++)	//����ÿ������word
			{
				//�����õ���word��������
				LDAModel.z[m][n] = GibbsSampling(m, n);
			}
		}
	}
	CalcTheta();	//ÿ���ĵ�������ֲ�
	CalcPhi();		//ÿ������Ĵʷֲ�
}

int GibbsSampling(int m, int n)
{
	int topic = LDAModel.z[m][n];
	int w = LDAModel.docs[m].words[n];	//word->term

	//��topic�Ӽ������Ƴ�
	LDAModel.nw[w][topic]--;
	LDAModel.nd[m][topic]--;
	LDAModel.nwSum[topic]--;
	LDAModel.ndSum[m]--;

	double Vbeta = LDAModel.V * LDAModel.beta;
	double Kalpha = LDAModel.K * LDAModel.alpha;
	//���㵱ǰ�����ڸ�������k�ĸ���
	int k;
	for(k = 0; k < LDAModel.K; k++)
	{
		LDAModel.p[k] = 
			(LDAModel.nd[m][k] + LDAModel.alpha) / (LDAModel.ndSum[m] + Kalpha) *
			(LDAModel.nw[w][k] + LDAModel.beta) / (LDAModel.nwSum[k] + Vbeta);

		if(k >= 1)	//ת�����ۻ�����
			LDAModel.p[k] += LDAModel.p[k-1];
	}
	double u = rand(1.0)*LDAModel.p[LDAModel.K-1];	//����u��[0,pk]
	for (topic = 0; topic < LDAModel.K; topic++)
	{
		if (LDAModel.p[topic] > u)	//������������
			break;
	}

	//���µ�topic���뵽������
	LDAModel.nw[w][topic]++;
	LDAModel.nd[m][topic]++;
	LDAModel.nwSum[topic]++;
	LDAModel.ndSum[m]++;
	return topic;
}
//ÿ���ĵ�������ֲ�
void CalcTheta()
{
	int m,k;
	double Kalpha = LDAModel.K * LDAModel.alpha;
	for(m = 0; m < LDAModel.M; m++)
	{
		for(k = 0; k < LDAModel.K; k++)
		{
			LDAModel.theta[m][k] = 
				(LDAModel.nd[m][k] + LDAModel.alpha) / (LDAModel.ndSum[m] + Kalpha);
		}
	}
}

//ÿ������Ĵʷֲ�
void CalcPhi()
{
	int k,w;
	double Vbeta = LDAModel.V * LDAModel.beta;
	for(k = 0; k < LDAModel.K; k++)
	{
		for(int w = 0; w < LDAModel.V; w++)
		{
			LDAModel.phi[k][w] = 
				(LDAModel.nw[w][k] + LDAModel.beta) / (LDAModel.nwSum[k] + Vbeta);
		}
	}
}