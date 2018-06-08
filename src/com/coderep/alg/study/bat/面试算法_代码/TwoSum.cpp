// TwoSum.cpp : �������̨Ӧ�ó������ڵ㡣
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
	iFile.open("D:\\Prime.txt");	//��������
	vector<int> a;
	int i;
	while(iFile >> i)
		a.push_back(i);

	int* p = &a.front();	//100���������е�����
	int size = (int)a.size();	//100�������ĸ���
	int j;
	int m = 0;	//�غͽ���
	int f = 0;	//�ĸ������õ������غͽ���
	for(i = 0; i < 1000000; i++)
	{
		j = Find(p, size, i);	//����p[0,size-1]����i����Сֵ����
		j = TwoSum(i, p, j);	//p[x]+p[y]==i�����ؼ��ֲ�ַ���
		if(m < j)
		{
			m = j;
			f = i;
		}
	}
	cout << f << ":\t" << m << endl;
	return 0;
}