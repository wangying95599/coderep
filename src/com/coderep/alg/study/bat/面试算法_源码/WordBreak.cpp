// WordBreak.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <set>
#include <string>
#include <vector>
using namespace std;

void AddAnswer(const string& str, const vector<int>& oneBreak, vector<string>& answer)
{
	int s = (int)oneBreak.size();
	int size = (int)str.length();
	answer.push_back(string());
	string& sentence = answer.back();
	sentence.reserve(size+s);	//申请足够的内容长度
	int start = 0, end = 0;
	for(int i = s-2; i >= 0; i--)	//oneBreak[size-1]==0，特殊处理
	{
		end = oneBreak[i];	//别忘了，k=oneBreak[i]的值表示在string[k]的前面添加break
		sentence += str.substr(start, end-start);
		sentence += ' ';
		start = end;
	}
	sentence += str.substr(start, size-start);	//最后一个break
}

//计算str[0...cur-1]的wordbreak有哪些
void FindAnswer(const vector<vector<bool> >& chess, const string& str, int cur,
				vector<int>& oneBreak, vector<string>& answer)
{
	if(cur == 0)	//叶子
	{
		AddAnswer(str, oneBreak, answer);
		return;
	}
	int size = (int)str.length();
	for(int i = 0; i < cur-1; i++)
	{
		if(chess[cur][i])	//str[i...cur]在词典中
		{
			oneBreak.push_back(i);
			FindAnswer(chess, str, i, oneBreak, answer);
			oneBreak.pop_back();
		}
	}
}

void WordBreak(const set<string>& dict, const string& str, vector<string>& answer)
{
	int size = (int)str.length();
	//chess[i][j]：str[0...i-1]中，是否可以在第j号元素的前面加break
	vector<vector<bool> > chess(size+1, vector<bool>(size));
	vector<bool> f(size+1);	//f[i]：str[0...i-1]是否在词典中

	int i,j;
	f[0] = true;	//空串在词典中
	for(i = 1; i <= size; i++)	//str[0...i-1]：长度为i
	{
		for(j = i-1; j >= 0; j--)
		{
			if(f[j] && (dict.find(str.substr(j, i-j)) != dict.end()))	//str[j...i-1]
			{
				f[i] = true;
				chess[i][j] = true;
			}
		}
	}
	vector<int> oneBreak;	//一种可行的划分
	FindAnswer(chess, str, size, oneBreak, answer);	//计算str[0...size-1]的wordbreak有哪些
}

void Print(const vector<string>& answer)
{
	vector<string>::const_iterator itEnd = answer.end();
	for(vector<string>::const_iterator it = answer.begin();
		it != itEnd; it++)
		cout << *it << endl;
	cout << endl;
}

bool WordBreak1(const set<string>& dict, const string& str)
{
	int size = (int)str.length();
	vector<bool> f(size+1);	//f[i]：str[0...i-1]是否在词典中

	f[0] = true;
	int i,j;
	for(i = 1; i <= size; i++)	//str[0...i-1]：长度为i
	{
		for(j = i-1; j >= 0; j--)
		{
			if(f[j] && (dict.find(str.substr(j, i-j)) != dict.end()))	//str[j...i-1]
			{
				f[i] = true;
				break;
			}
		}
	}
	return f[size];
}

bool WordBreak2(const set<string>& dict, const string& str)
{
	int size = (int)str.length();
	if(size == 0)
		return true;

	for(int i = size-1; i >= 0; i--)
	{
		if(WordBreak2(dict, str.substr(0,i))
		&&(dict.find(str.substr(i, size-i)) != dict.end()))
			return true;
	}
	return false;
}

int WordBreak3(const set<string>& dict, const string& str, vector<int>& f)
{
	int size = (int)str.length();
	for(int i = size-1; i >= 0; i--)
	{
		if(f[i] == 0)
			f[i] = WordBreak3(dict, str.substr(0,i), f);

		if((f[i] == 1) && (dict.find(str.substr(i, size-i)) != dict.end()))
			return 1;
	}
	return -1;
}
/*
int _tmain(int argc, _TCHAR* argv[])
{
	set<string> dict;
	dict.insert("cat");
	dict.insert("cats");
	dict.insert("and");
	dict.insert("sand");
	dict.insert("dog");
	dict.insert("dog");
	string str = "catsandsdog";
	int size = (int)str.length();
	vector<int> f(size+1);	//f[i]：str[0...i-1]是否在词典中
	memset(&f.front() + 1, 0, sizeof(int)*size);
	f[0] = 1;
	if(WordBreak3(dict, str, f) == 1)
		cout << "Break is TRUE\n";
	else
		cout << "Break is FALSE\n";
	return 0;
}*/

int _tmain(int argc, _TCHAR* argv[])
{
	set<string> dict;
	dict.insert("下雨天");
	dict.insert("留客");
	dict.insert("留客天");
	dict.insert("天留");
	dict.insert("留我不");
	dict.insert("我不留");
	dict.insert("留");
	dict.insert("dog");
	string str = "下雨天留客天留我不不留";
	//vector<string> answer;
	//WordBreak(dict, str, answer);
	//Print(answer);

	int size = (int)str.length();
	vector<int> f(size+1);	//f[i]：str[0...i-1]是否在词典中
	memset(&f.front() + 1, 0, sizeof(int)*size);
	f[0] = 1;
	cout << f[size] << endl;
	cout << WordBreak3(dict, str, f) << endl;
	cout << WordBreak2(dict, str) << endl;
	return 0;
}