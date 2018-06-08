// Expect.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <math.h>
using namespace std;

#define MATH_E	2.71828182845904523536

void CalcCumulate(const int* song, int size, int* pCumulate)
{
	pCumulate[0] = song[0];
	for(int i = 1; i < size; i++)
		pCumulate[i] = pCumulate[i-1] + song[i];
}

int RandSong(const int* song, int size, const int* pCumulate)
{
	int nRec = rand() % pCumulate[size-1];
	int low = 0;
	int high = size-1;
	int mid;
	int nSong = -1;
	while(low < high)
	{
		mid = (low + high) / 2;
		if(nRec < pCumulate[mid])
			high = mid;
		else if(nRec > pCumulate[mid])
			low = mid + 1;
		else
		{
			nSong = mid+1;
			break;
		}
	}
	if(nSong == -1)
		nSong = low;
	return nSong;
}

int Rand(int N)	//[1,N]
{
	return rand()%(N-1) + 1;
}

double Randf(double N)	//连续：[0,N]
{
	return rand() * N / RAND_MAX;
}

double Randf(double from, double to)
{
	return rand() * (to - from) / RAND_MAX + from;
}

int Gauss(double niu, double sigma, int from, int to)
{
	bool bGet = false;
	double num, x;
	double sigma2 = 2 * sigma * sigma;
	while(!bGet)
	{
		num = Randf(niu-10*sigma, niu+10*sigma);
		x = num - niu;
		x *= x;
		x /= sigma2;
		x = pow(MATH_E, -x);
		if(x >= Randf(0, 1.0))
			bGet = true;
	}
	int t = (int)(num+0.5);
	if(t > to)
		t = to;
	else if(t < from)
		t = from;
	return t;
}

int GameEquilibrium()
{
	int category[] = {25, 25, 30, 19, 1};
	int size = sizeof(category) / sizeof(int);
	int* pCumulate = new int[size];	//累积概率，方便随机选择类别
	CalcCumulate(category, size, pCumulate);	//计算累积概率
	int N = 9;	//样本数目
	int M = 0;		//除绝顶聪明人以外的有效样本数
	double cur = 0;	//当前有效样本的总和
	int nCategory;	//选择某个类别的人
	for(int i = 0; i < N; i++)
	{
		nCategory = RandSong(category, size, pCumulate);
		if(Randf(100) < 2)			//恶作剧的人
		{
			cur += 100;
			M++;
		}
		else if(nCategory == 0)		//随机化的人
		{
			cur += Rand(100);
			M++;
		}
		else if(nCategory == 1)		//稍思维的人
		{
			cur += Gauss(33.3, 10, 1, 100);
			M++;
		}
		else if(nCategory == 2)		//思维的人
		{
			cur += Gauss(1, 3, 1, 100);
			M++;
		}
		else if(nCategory == 3)		//再思维的人
		{
			cur += Gauss(10, 3, 1, 100);
			M++;
		}
		cout << nCategory;
	}
	cout << endl << setprecision(10) << cur << endl;
	cout << cur/M << endl;
	delete[] pCumulate;
	return (int)(cur/M+0.5);
}
int _tmain(int argc, _TCHAR* argv[])
{
	cout << GameEquilibrium();
	return 0;
}

