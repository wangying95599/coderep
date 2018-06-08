// WordLadder2.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <set>
#include <string>
#include <queue>
#include <iostream>
using namespace std;

//搜索cur的孩子结点，存入children中
void Extend(const string& cur, vector<string>& children, const set<string>& dict,
			const string& end, set<string>& visit)
{
	string child = cur;
	children.clear();
	int i;
	char c,t;
	for(i = 0; i < (int)cur.size(); i++)
	{
		t = child[i];
		for(c = 'a'; c != 'z'; c++)
		{
			if(c == t)
				continue;
			child[i] = c;
			if(((child == end) || (dict.find(child) != dict.end()))
				&& (visit.find(child) == visit.end()))
			{
				children.push_back(child);
				visit.insert(child);
			}
		}
		child[i] = t;
	}
}

int CalcLadderLength(const string& start, const string& end, const set<string>& dict)
{
	queue<string> q;
	q.push(start);
	vector<string> children;	//从当前结点可扩展得到的新结点集合
	set<string> visit;
	int step = 0;
	string cur;
	int curNumber = 1;		//当前层剩余节点数目
	int nextNumber = 0;		//下一层孩子结点数目
	while(!q.empty())
	{
		cur = q.front();	//从cur开始扩展
		q.pop();
		curNumber--;
		Extend(cur, children, dict, end, visit);
		nextNumber += (int)children.size();
		if(curNumber == 0)	//当前层遍历完，则遍历下一层，所以step加1
		{
			step++;
			curNumber = nextNumber;
			nextNumber = 0;
		}
		for(vector<string>::const_iterator it = children.begin(); it != children.end(); it++)
		{
			if(*it == end)
				return step;
			q.push(*it);
		}
	}
	return 0;
}
int _tmain(int argc, _TCHAR* argv[])
{
	set<string> dict;
	dict.insert("hot");
	dict.insert("dot");
	dict.insert("dog");
	dict.insert("lot");
	dict.insert("log");
	string start = "hit";
	string end = "cog";
	cout << CalcLadderLength(start, end, dict);
	return 0;
}