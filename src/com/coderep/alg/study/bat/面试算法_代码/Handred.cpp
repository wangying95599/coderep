// Handred.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <memory>
#include <vector>
#include <iostream>
using namespace std;

void Print(int index, const int* a, const vector<pair<int, char> >& op, int size)
{
	cout << index << ":\t";
	vector<pair<int, char> >::const_iterator o = op.begin();
	for(int i = 0; i < size; i++)
	{
		cout << a[i];
		if(i == size-1)
			break;
		if((o != op.end()) && (o->first == i))
		{
			cout << " " << o->second  << " ";
			o++;
		}
	}
	cout << '\n';
}

bool LastOperator(vector<pair<int, char> >& op, int size)
{
	if(op.empty())
		return true;
	return op.back().second == '+';
}

//�����cur����λ����ǰ���ʽ��ֵ��n�����һ������last��������������op
bool Calc(const int* a, int size, int cur, int n, int last,
	vector<pair<int, char> >& op,int sum, int& count)
{
	if(cur == size-1)	//�ݹ����
	{
		last = 10 * last + a[size-1];
		if((LastOperator(op, cur-1) ? (n+last) : (n-last)) == sum)	//�ҵ���
		{
			count++;
			Print(count, a, op, size);
			return true;
		}
		return false;
	}
	last = 10*last+a[cur];
	Calc(a, size, cur+1, n, last, op, sum, count);	//<��>
	bool bAdd = LastOperator(op, cur-1);
	op.push_back(make_pair(cur, '+'));		//'+'
	Calc(a, size, cur+1, bAdd ? n+last : n-last, 0, op, sum, count);
	op.back().second = '-';					//'-'
	Calc(a, size, cur+1, bAdd ? n+last : n-last, 0, op, sum, count);
	op.pop_back();							//����
	return count != 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	int a[] = {1,2,3,4,5,6,7,8,9};
	int size = sizeof(a)/sizeof(int);
	vector<pair<int, char> > op;
	int count = 0;
	Calc(a, size, 0, 0, 0, op, 100, count);
	return 0;
}

