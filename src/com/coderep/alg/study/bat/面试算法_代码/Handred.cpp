// Handred.cpp : 定义控制台应用程序的入口点。
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

//考察第cur个空位，当前表达式的值是n，最后一个数是last，操作符放置于op
bool Calc(const int* a, int size, int cur, int n, int last,
	vector<pair<int, char> >& op,int sum, int& count)
{
	if(cur == size-1)	//递归结束
	{
		last = 10 * last + a[size-1];
		if((LastOperator(op, cur-1) ? (n+last) : (n-last)) == sum)	//找到解
		{
			count++;
			Print(count, a, op, size);
			return true;
		}
		return false;
	}
	last = 10*last+a[cur];
	Calc(a, size, cur+1, n, last, op, sum, count);	//<空>
	bool bAdd = LastOperator(op, cur-1);
	op.push_back(make_pair(cur, '+'));		//'+'
	Calc(a, size, cur+1, bAdd ? n+last : n-last, 0, op, sum, count);
	op.back().second = '-';					//'-'
	Calc(a, size, cur+1, bAdd ? n+last : n-last, 0, op, sum, count);
	op.pop_back();							//回溯
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

