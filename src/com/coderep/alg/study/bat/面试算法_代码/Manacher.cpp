// Manacher.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include <algorithm>
#include <list>
#include <vector>
#include <hash_map>
using namespace std;

void Print(const char* str)
{
	cout << '$';
	while(*str)
	{
		cout << "  #  " << *str;
		str++;
	}
	cout << " #\n";
}

void Print(const int* a, int N)
{
	for(int i = 0; i < N; i++)
	{
		cout << a[i] << "  ";
	}
	cout << '\n';
}

void Print(const list<int>& L)
{
	for(auto p = L.begin(); p != L.end(); p++)
		cout << *p << '\t';
	cout << '\n';
}

void Manacher2(const char* str, int& from, int& to)
{
	int size = strlen(str);
	int N = 2*size+1;
	int* p = new int[N];
	int mx = 1;
	int id = 0;
	p[0] = 1;
	int center = 0;	//最长回文子串的中心
	int ml = 1;		//最长回文子串的长度
	for(int i = 1; i < N; i++)
	{
		if(i < mx)
			p[i] = min(p[2*id-i], mx-i);
		else
			p[i] = 1;
		while((i != p[i]) && (((i+p[i]) % 2 == 1)
			|| (str[(i+p[i])/2-1] == str[(i-p[i])/2-1])))
			p[i]++;
		if(mx < i + p[i])
		{
			mx = i + p[i];
			id = i;
		}
		if(ml < p[i])
		{
			ml = p[i];
			center = i;
		}
	}
	from = (center - ml) / 2;
	to = from + ml - 2;
	delete[] p;
}

void Manacher(const char* str)
{
	int size = strlen(str);
	int N = 2*size+1;
	int* p = new int[N];
	int mx = 1;
	int id = 0;
	p[0] = 1;
	for(int i = 1; i < N; i++)
	{
		if(i < mx)
			p[i] = min(p[2*id-i], mx-i);
		else
			p[i] = 1;
		while((i != p[i]) && (((i+p[i]) % 2 == 1)
			|| (str[(i+p[i])/2-1] == str[(i-p[i])/2-1])))
			p[i]++;
		if(mx < i + p[i])
		{
			mx = i + p[i];
			id = i;
		}
	}
	Print(str);
	Print(p, N);
	delete[] p;
}

int Rand(int m)
{
	return rand() * m / RAND_MAX;
}

void TwoDiff2(int* a, int N, int diff)
{
	sort(a, a+N);
	Print(a, N);
	int* p = new int[N];
	int i,j;
	for(i = 0; i < N; i++)
	{
		p[i] = a[i] + diff;
	}
	i = j = 0;
	while((i <= N-1) && (j <= N-1))
	{
		if(a[i] < p[j])
			i++;
		else if(a[i] > p[j])
			j++;
		else	//if(a[i] == p[j])
		{
			cout << p[j] - diff << '\t' << a[i] << '\n';
			i++;
			j++;
		}
	}
	delete[] p;
}

void TwoDiff(int* a, int N, int diff)
{
	int i,j;
	i = j = 0;
	while((i <= N-1) && (j <= N-1))
	{
		if(a[i] < a[j]+diff)
			i++;
		else if(a[i] > a[j]+diff)
			j++;
		else	//if(a[i] == a[j]+diff)
		{
			cout << a[j] << ',' << a[i] << '\n';
			i++;
			j++;
		}
	}
}


void TwoSum(int* a, int N, int sum)
{
	int i = 0;
	int j = N-1;
	while(i < j)
	{
		if(a[i] + a[j] < sum)
			i++;
		else if(a[i] + a[j] > sum)
			j--;
		else	//if(a[i] + a[j] == sum)
		{
			cout << a[i] << ',' << a[j] << '\n';
			i++;
			j--;
		}
	}
}

void Manacher(const char* str, list<int>& prefix, list<int>& suffix)
{
	int size = strlen(str);
	int N = 2*size+1;
	int* p = new int[N];
	p[0] = 1;
	int mx = 1;
	int id = 0;
	int i;
	for(i = 1; i < N; i++)
	{
		if(i < mx)
			p[i] = min(p[2*id-i], mx-i);
		else
			p[i] = 1;
		while((i != p[i]) && (((i+p[i]) % 2 == 1)
			|| (str[(i+p[i])/2-1] == str[(i-p[i])/2-1])))
			p[i]++;
		if(mx < i + p[i])
		{
			mx = i + p[i];
			id = i;
		}
	}
	for(i = 2; i < N; i++)
	{
		if(p[i] == i)
			prefix.push_back(i-1);
		if(i+p[i] == N+1)
			suffix.push_back(p[i]-1);
	}
	delete[] p;
}

void PrintPair(list<pair<int, int> >& L, const vector<string>& words)
{
	int i,j;
	for(auto p = L.begin(); p != L.end(); p++)
	{
		i = p->first;
		j = p->second;
		cout << '(' << i << ", " << j << ")\t" << words[i] << '\t' << words[j] << '\n';
	}
}

void PalindromePair(const vector<string>& words, list<pair<int, int> >& result)
{
	hash_map<string, int> dict;
	int size = (int)words.size();
	int i,s;
	for(i = 0; i < size; i++)
		dict[words[i]] = i;
	list<int> prefix, suffix;
	string word, str;
	for(i = 0; i < size; i++)
	{
		prefix.clear();
		suffix.clear();
		word = words[i].c_str();
		s = (int)words[i].size();
		Manacher(word.c_str(), prefix, suffix);	//计算word的前缀/后缀的回文串
		for(auto p = prefix.begin(); p != prefix.end(); p++)	//前缀串
		{
			str = words[i].substr(*p, s - *p);
			reverse(str.begin(), str.end());
			if(dict.find(str) != dict.end())
			{
				result.push_back(make_pair(dict[str], i));
			}
		}
		for(auto p = suffix.begin(); p != suffix.end(); p++)	//后缀串
		{
			str = words[i].substr(0, s-*p);
			reverse(str.begin(), str.end());
			if(dict.find(str) != dict.end())
			{
				result.push_back(make_pair(i, dict[str]));
			}
		}
		reverse(word.begin(), word.end());	//全串
		if(dict.find(word) != dict.end())
		{
			if(dict[word] != i)
				result.push_back(make_pair(i, dict[word]));
		}
	}
}

void Print(const char* str, int from, int to)
{
	for(int i = from; i <= to; i++)
	{
		cout << str[i];
	}
	cout << '\n';
}

int _tmain(int argc, _TCHAR* argv[])
{
	//vector<string> words(6);
	//words[0] = "abcd";
	//words[1] = "dcba";
	//words[2] = "lls";
	//words[3] = "s";
	//words[4] = "sssll";
	//words[5] = "sss";
	//list<pair<int, int> > result;
	//PalindromePair(words, result);
	//PrintPair(result, words);

	//char* str = "abaacbcbabcbcabcbabcb";
	char* str = "aaba";
	int from, to;
	Manacher(str);
	//Print(str, from, to);


	//int a[] = {0, 3, 7, 9, 11, 14, 16, 17};
	//sort(a, a+N);	若给定数组未排序，则先排序
	//TwoSum(a, sizeof(a)/sizeof(int), 20);
	return 0;
}

