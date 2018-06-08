// Palindrome.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

void CalcSubstringPalindrome(const char* str, int size, vector<vector<bool> >& p)
{
	int i,j;
	for(i = 0; i < size; i++)
		p[i][i] = true;
	for(i = size-2; i >= 0; i--)
	{
		p[i][i+1] = (str[i] == str[i+1]);
		for(j = i+2; j < size; j++)
		{
			if((str[i] == str[j]) && p[i+1][j-1])
				p[i][j] = true;
		}
	}
}

int MinPalindrome(const char* str)
{
	int size = (int)strlen(str);
	vector<vector<bool> > p(size, vector<bool>(size));
	CalcSubstringPalindrome(str, size, p);

	int i,j;
	int* minPart = new int[size];
	for(i = 0; i < size; i++)
	{
		if(p[0][i])	//本身是回文串，则不需要分割
		{
			minPart[i] = 1;
			continue;
		}
		minPart[i] = i+1;
		for(j = 0; j < i; j++)
		{
			if((p[j+1][i]) && (minPart[i] > minPart[j]+1))
			{
				minPart[i] = minPart[j]+1;
			}
		}
	}
	int mp = minPart[size-1];
	delete[] minPart;
	return mp;
}

int MinPalindrome2(const char* str, int* pre, int size)
{
	vector<vector<bool> > p(size, vector<bool>(size));
	CalcSubstringPalindrome(str, size, p);

	//minPart[i]：str[0...i]最少划分数目
	int* minPart = new int[size];
	int nMin;
	int i,j;
	for(i = 0; i < size; i++)
	{
		if(p[0][i])	//本身是回文串，则不需要分割
		{
			minPart[i] = 1;
			pre[i] = -1;
			continue;
		}
		minPart[i] = i+1;
		nMin = -1;
		for(j = 0; j < i; j++)
		{
			if((p[j+1][i]) && (minPart[i] > minPart[j]+1))
			{
				minPart[i] = minPart[j]+1;
				nMin = j;
			}
		}
		pre[i] = nMin;
	}
	int mp = minPart[size-1];
	delete[] minPart;
	return mp;
}

void FindSolution(const char* str, int size, int nStart, vector<vector<string> >& all, vector<string>& solution, const vector<vector<bool> >& p)
{
	if(nStart >= size)
	{
		all.push_back(solution);
		return;
	}
	for(int i = nStart; i < size; i++)
	{
		if(p[nStart][i])
		{
			solution.push_back(string(str+nStart, str+i+1));
			FindSolution(str, size, i+1, all, solution, p);
			solution.pop_back();
		}
	}
}

void MinPalindrome3(const char* str, vector<vector<string> >& all)
{
	int size = (int)strlen(str);
	vector<vector<bool> > p(size, vector<bool>(size));
	CalcSubstringPalindrome(str, size, p);

	vector<string> solution;	//一个解
	FindSolution(str, size, 0, all, solution, p);
}

void Add(vector<vector<string> >& to, const vector<vector<string> >& from, const string& sub)
{
	if(from.empty())
	{
		to.push_back(vector<string>(1, sub));
		return;
	}
	to.reserve(from.size());
	for(vector<vector<string> >::const_iterator it = from.begin(); it != from.end(); it++)
	{
		to.push_back(vector<string>());
		vector<string>& now = to.back();
		now.reserve(it->size()+1);
		for(vector<string>::const_iterator s = it->begin(); s != it->end(); s++)
			now.push_back(*s);
		now.push_back(sub);
	}
}

void MinPalindrome4(const char* str, vector<vector<string> >& all)
{
	int size = (int)strlen(str);
	vector<vector<bool> > p(size, vector<bool>(size));
	CalcSubstringPalindrome(str, size, p);

	//prefix[i]：长度为i的前缀串的所有划分方案
	vector<vector<string> >* prefix = new vector<vector<string> >[size];
	prefix[0].clear();	//仅为了强调长度为0的串，划分解为空
	int i,j;
	for(i = 1; i <= size; i++)	//考察str[0...i-1]
	{
		for(j = 0; j < i; j++)
		{
			if(p[j][i-1])
			{
				Add((i == size) ? all : prefix[i], prefix[j], string(str+j, str+i));
			}
		}
	}
	delete[] prefix;
}

void Cut(const char* str, const int* pre, int size, vector<string>& result)
{
	int nEnd = size-1;
	int nStart;
	while(pre[nEnd] != -1)
	{
		nStart = pre[nEnd];
		result.push_back(string(str+nStart+1,str+nEnd+1));
		nEnd = nStart;
	}
	result.push_back(string(str,str+nEnd+1));
	reverse(result.begin(), result.end());	//逆序
}

void Print(const vector<string>& result)
{
	for(vector<string>::const_iterator it = result.begin(); it != result.end(); it++)
	{
		cout << (*it).data() << " | ";
	}
	cout << endl;
}

void PrintAll(const vector<vector<string> >& all)
{
	cout << "Count：" << (int)all.size() << endl;
	int i = 0;
	for(vector<vector<string> >::const_iterator it = all.begin(); it != all.end(); it++)
	{
		cout << ++i << "：";
		Print(*it);
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	/*int size = (int)strlen(str);
	int* pre = new int[size];
	cout << MinPalindrome(str) << endl;
	cout << MinPalindrome2(str, pre, size) << endl;
	vector<string> result;
	Cut(str, pre, size, result);
	delete[] pre;
	Print(result);*/

	const char* str = "abacdccdaa";
	vector<vector<string> > all;
	MinPalindrome3(str, all);
	PrintAll(all);
	return 0;
}