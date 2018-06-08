// Segment.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <math.h>
#include <list>
#include <algorithm>
#include <time.h>
using namespace std;

typedef struct tagSSegment
{
	int id;
	bool start;
	int value;

	static bool Compare(const tagSSegment& s1, const tagSSegment& s2)
	{
		return s1.value < s2.value;
	}

}SSegment;

int MaxRepeatPart(const int* start, const int* end, int N)
{
	SSegment* seg = new SSegment[2*N];
	int size = 0;
	int i;
	for(i = 0; i < N; i++)
	{
		seg[size].id = i;
		seg[size].start = true;
		seg[size].value = start[i];
		size++;

		seg[size].id = i;
		seg[size].start = false;
		seg[size].value = end[i];
		size++;
	}

	sort(seg, seg+size, SSegment::Compare);
	list<int> q;	//缓冲区
	int f;
	int cur = 0;
	for(i = 0; i < size; i++)
	{
		if(seg[i].start)
			q.push_back(seg[i].id);
		else
		{
			if(q.empty())
				continue;
			f = q.front();
			if(f == seg[i].id)	//发现了队首线段的终点，出队
			{
				q.pop_front();	//出队
				if(!q.empty())
					cur = max(cur, seg[i].value-start[q.front()]);
			}
			else
			{
				q.erase(find(q.begin(), q.end(), seg[i].id));	//出"队"
				cur = max(cur, seg[i].value-start[seg[i].id]);
			}
		}
	}

	delete[] seg;
	return cur;
}
int _tmain(int argc, _TCHAR* argv[])
{
	const int N = 5;
	int start[N], end[N];
	//for(int k = 0; k < 10; k++)
	{
		//srand((int)time(NULL));
		for(int i = 0; i < N; i++)
		{
			start[i] = rand() % 1000;
			end[i] = rand() % 1000;
			if(start[i] > end[i])
				swap(start[i], end[i]);
			cout << start[i] << '-' << end[i];
			cout << endl;
		}

		cout << MaxRepeatPart(start, end, N) << endl;
	}
	return 0;
}

