// LCS.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

void LCS(const char* str1, const char* str2, string& str)
{
	int size1 = (int)strlen(str1);
	int size2 = (int)strlen(str2);
	const char* s1 = str1-1;	//从1开始数，方便后面的代码编写
	const char* s2 = str2-1;
	vector<vector<int> > chess(size1+1, vector<int>(size2+1));
	int i,j;
	for(i = 0; i <= size1; i++)	//第0列
		chess[i][0] = 0;
	for(j = 0; j <= size2; j++)	//第0行
		chess[0][j] = 0;

	for(i = 1; i <= size1; i++)
	{
		for(j = 1; j <= size2; j++)
		{
			if(s1[i] == s2[j])	//i,j相等
				chess[i][j] = chess[i-1][j-1] + 1;
			else
				chess[i][j] = max(chess[i][j-1], chess[i-1][j]);
		}
	}

	i = size1;
	j = size2;
	while((i != 0) && (j != 0))
	{
		if(s1[i] == s2[j])
		{
			str.push_back(s1[i]);
			i--;
			j--;
		}
		else
		{
			if(chess[i][j-1] > chess[i-1][j])
				j--;
			else
				i--;
		}
	}
	reverse(str.begin(), str.end());
}

void FindAnswer(vector<vector<int> >& chess, vector<string>& solution, string& answer, const char* str1, const char* str2, int i, int j)
{
	while((i != 0) && (j != 0))
	{
		if(str1[i] == str2[j])
		{
			answer.push_back(str1[i]);
			i--;
			j--;
		}
		else
		{
			if(chess[i][j-1] == chess[i-1][j])
			{
				int s = (int)answer.size();
				FindAnswer(chess, solution, answer, str1, str2, i-1, j);
				answer.resize(s);

				FindAnswer(chess, solution, answer, str1, str2, i, j-1);
				answer.resize(s);
				break;
			}
			else if(chess[i][j-1] > chess[i-1][j])
			{
				j--;
			}
			else
			{
				i--;
			}
		}
	}

	if((i == 0) || (j == 0))
	{
		solution.push_back(answer);
		reverse(solution.back().begin(), solution.back().end());
		return;
	}
}

void LCS2(const char* str1, const char* str2, vector<string>& solution)
{
	int size1 = (int)strlen(str1);
	int size2 = (int)strlen(str2);
	const char* s1 = str1-1;	//从1开始数，方便后面的代码编写
	const char* s2 = str2-1;
	vector<vector<int> > chess(size1+1, vector<int>(size2+1));
	int i,j;
	for(i = 0; i <= size1; i++)	//第0列
		chess[i][0] = 0;
	for(j = 0; j <= size2; j++)	//第0行
		chess[0][j] = 0;

	for(i = 1; i <= size1; i++)
	{
		for(j = 1; j <= size2; j++)
		{
			if(s1[i] == s2[j])	//i,j相等
				chess[i][j] = chess[i-1][j-1] + 1;
			else
				chess[i][j] = max(chess[i][j-1], chess[i-1][j]);
		}
	}

	string answer;
	FindAnswer(chess, solution, answer, str1-1, str2-1, size1, size2);
}

void Print(const vector<string>& solution)
{
	int i = 1;
	for(vector<string>::const_iterator it = solution.begin(); it != solution.end(); it++)
	{
		cout << i << "："<< it->c_str() << "\n";
		i++;
	}
	cout << "\n\n==================\n";
}

int _tmain(int argc, _TCHAR* argv[])
{
	const char* str1 = "TCGGATCGACTT";//BDCABA
	const char* str2 = "AGCCTACGTA";//ABCBDAB
	vector<string> solution;
	LCS2(str1, str2, solution);
	Print(solution);
	return 0;
}