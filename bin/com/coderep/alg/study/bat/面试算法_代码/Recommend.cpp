// Recommend.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <iomanip>
using namespace std;

void Test(int a, int from, int to)
{
	if(a < from)
		cout << a << "：a < from" << endl;
	if(a > to)
		cout << a << "：a > to" << endl;
}

//更优
int RandSong(const int* song, int size)
{
	int i;
	int* pCumulate = new int[size];	//i的区间范围：[i-1,i)
	pCumulate[0] = song[0];
	for(i = 1; i < size; i++)
		pCumulate[i] = pCumulate[i-1] + song[i];

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
	delete[] pCumulate;
	return nSong;
}

int RandSong2(const int* song, int size)
{
	int nSum = song[0];
	for(int i = 1; i < size; i++)
		nSum += song[i];

	bool bFind = false;
	int nCandidate = 0;
	while(!bFind)
	{
		nCandidate = rand() % size;	//候选
		if(rand() % nSum < song[nCandidate])
		{
			bFind = true;
			break;
		}
	}
	return nCandidate;
}

void Print(const int* a, int size)
{
	for(int i = 0; i < size; i++)
	{
		cout << a[i] << ' ';
	}
	cout << endl;
}

void Print2(const int* a, int size)
{
	int i;
	int nSum = a[0];
	for(i = 1; i < size; i++)
		nSum += a[i];

	cout << nSum << "：";
	for(i = 0; i < size; i++)
	{
		cout << setprecision(3) << (double)a[i] / (double)nSum << ' ';
	}
	cout << endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
	int song[] = {43,63,43,89,322,2,5,32};
	int size = sizeof(song) / sizeof(int);
	int* vote = new int[size];
	memset(vote, 0, size*sizeof(int));

	int s;
	for(int i = 0; i < 10000; i++)
	{
		s = RandSong2(song, size);
		vote[s]++;
		cout << s;
	}
	cout << "\n\n==============\n\n";
	Print(vote, size);
	Print2(vote, size);
	Print2(song, size);
	return 0;
}

