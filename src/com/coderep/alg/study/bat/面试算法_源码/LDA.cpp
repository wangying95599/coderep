// LDA.cpp : 定义控制台应用程序的入口点。
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
			w = data.docs[m].words[n];	//查找单词n在词典中的编号(word->term)
			LDAModel.nw[w][topic]++;
			LDAModel.nd[m][topic]++;
			LDAModel.nwSum[topic]++;
		}
		LDAModel.ndSum[m] = N;	//第m篇文档的可重复单词数目
	}
}

void Estimate()
{
	for(int times = 0; times < nMaxTimes; times++)
	{
		for(int m = 0; m < LDAModel.M; m++)	//对于每篇文档
		{				
			for(int n = 0; n < LDAModel.docs[m].GetLength(); n++)	//对于每个单词word
			{
				//采样得到该word的新主题
				LDAModel.z[m][n] = GibbsSampling(m, n);
			}
		}
	}
	CalcTheta();	//每个文档的主题分布
	CalcPhi();		//每个主题的词分布
}

int GibbsSampling(int m, int n)
{
	int topic = LDAModel.z[m][n];
	int w = LDAModel.docs[m].words[n];	//word->term

	//将topic从记数中移除
	LDAModel.nw[w][topic]--;
	LDAModel.nd[m][topic]--;
	LDAModel.nwSum[topic]--;
	LDAModel.ndSum[m]--;

	double Vbeta = LDAModel.V * LDAModel.beta;
	double Kalpha = LDAModel.K * LDAModel.alpha;
	//计算当前词属于各个主题k的概率
	int k;
	for(k = 0; k < LDAModel.K; k++)
	{
		LDAModel.p[k] = 
			(LDAModel.nd[m][k] + LDAModel.alpha) / (LDAModel.ndSum[m] + Kalpha) *
			(LDAModel.nw[w][k] + LDAModel.beta) / (LDAModel.nwSum[k] + Vbeta);

		if(k >= 1)	//转换成累积概率
			LDAModel.p[k] += LDAModel.p[k-1];
	}
	double u = rand(1.0)*LDAModel.p[LDAModel.K-1];	//采样u∈[0,pk]
	for (topic = 0; topic < LDAModel.K; topic++)
	{
		if (LDAModel.p[topic] > u)	//采样到新主题
			break;
	}

	//将新的topic加入到记数中
	LDAModel.nw[w][topic]++;
	LDAModel.nd[m][topic]++;
	LDAModel.nwSum[topic]++;
	LDAModel.ndSum[m]++;
	return topic;
}
//每个文档的主题分布
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

//每个主题的词分布
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