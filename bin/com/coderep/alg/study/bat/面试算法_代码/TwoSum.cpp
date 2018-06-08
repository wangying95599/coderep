// TwoSum.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <algorithm>
#include <fstream>
#include <vector>
using namespace std;

int TwoSum(int sum, const int* a, int size)
{
	int low = 0;
	int high = size-1;
	int s;
	int times = 0;
	while(low < high)
	{
		s = a[low] + a[high];
		if(s == sum)
		{
			times++;
			//cout << a[low] << " + " << a[high] << '\n';
			low++;
			high--;
		}
		else if(s > sum)
			high--;
		else// if(s < sum)
			low++;
	}
	return times;
}

int Find(const int* a, int size, int x)
{
	int low = 0;
	int high = size-1;
	int mid;
	while(low <= high)
	{
		mid = (low + high) / 2;
		if(a[mid] == x)
			return mid;
		if(a[mid] > x)
			high = mid - 1;
		else
			low = mid + 1;
	}
	return low;
}

int _tmain(int argc, _TCHAR* argv[])
{
	ifstream iFile;
	iFile.open("D:\\Prime.txt");	//读入素数
	vector<int> a;
	int i;
	while(iFile >> i)
		a.push_back(i);

	int* p = &a.front();	//100万以内所有的素数
	int size = (int)a.size();	//100万素数的个数
	int j;
	int m = 0;	//素和阶数
	int f = 0;	//哪个整数得到最大的素和阶数
	for(i = 0; i < 1000000; i++)
	{
		j = Find(p, size, i);	//返回p[0,size-1]大于i的最小值索引
		j = TwoSum(i, p, j);	//p[x]+p[y]==i，返回几种拆分方法
		if(m < j)
		{
			m = j;
			f = i;
		}
	}
	cout << f << ":\t" << m << endl;
	return 0;
}