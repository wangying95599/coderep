// Sequence.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <utility>
#include <list>
using namespace std;

int MaxSequence(const int* a, int size)
{
	if(size <= 0)
		return 0;
	int m = 1;
	int p = 1;
	for(int i = 1; i < size; i++)
	{
		if(a[i] - a[i-1] == 1)
		{
			p++;
			m = max(m, p);
		}
		else
		{
			p = 1;
		}
	}
	return m;
}

int MaxSequence2(const int* a, int size, int& from, int& to)
{
	if(size <= 0)
		return 0;
	int m = 1;
	int p = 1;
	to = 0;
	for(int i = 1; i < size; i++)
	{
		if(a[i] - a[i-1] == 1)
		{
			p++;
			if(m < p)
			{
				m = p;
				to = i;
			}
		}
		else
		{
			p = 1;
		}
	}
	from = to - m + 1;
	return m;
}

void Print(const char* a, int from, int to)
{
	for(int i = from; i <= to; i++)
		cout << a[i] << '\t';
	cout << '\n';
}

int LongestSubstringK2(const char* str, int size, int k, int& from, int& to)
{
	if(size <= 0)
		return 0;
	map<char, int> wd;
	int left = 0;
	int mx = 0;
	for(int right = 0; right < size; right++)
	{
		wd[str[right]]++;
		while((int)wd.size() > k)
		{
			wd[str[left]]--;
			if(wd[str[left]] == 0)
				wd.erase(str[left]);
			left++;
		}
		if(mx < right-left+1)
		{
			mx = right - left + 1;
			from = left;
			to = right;
		}
	}
	return mx;
}

int LongestSubstringK(const char* str, int size, int k)
{
	if(size <= 0)
		return 0;
	map<char, int> wd;
	int left = 0;
	int mx = 0;
	for(int right = 0; right < size; right++)
	{
		wd[str[right]]++;
		while((int)wd.size() > k)
		{
			wd[str[left]]--;
			if(wd[str[left]] == 0)
				wd.erase(str[left]);
			left++;
		}
		mx = max(right-left+1, mx);
	}
	return mx;
}

class CTrieNode
{
public:
	int nIndex;	//ԭ�ַ������ֵ��е�λ�ã���Ϊ-1����ʾ�ý�㲻����������
	map<char, CTrieNode*> child;
public:
	CTrieNode() : nIndex(-1) {}
};

class CTrieTree
{
private:
	CTrieNode* m_pRoot;				//����
	const vector<string>& m_words;	//�ʵ�
	list<pair<int, int> > m_pair;	//���Ķ�

	void Destroy(CTrieNode* m_pRoot);
	void InsertR(int nIndex);	//��m_words[nIndex]�������Tree
	void CalcPair(int nIndex);	//����m_words[nIndex]�Ƿ���Tree�е��ַ������ɻ��Ĵ�
	void Palindrome(CTrieNode* node, string& str, int nIndex);	//��node��ʼ���ַ����Ƿ��ǻ��Ĵ�
	bool IsPalindrome(const string& str) const;	//�ж�str�Ƿ��ǻ��Ĵ�
public:
	CTrieTree(const vector<string>& words);
	~CTrieTree() { Destroy(m_pRoot); }
	void PalindromePair();
	void PrintPair();
};

CTrieTree::CTrieTree(const vector<string>& words) : m_words(words)
{
	m_pRoot = new CTrieNode();
	for(int i = 0; i < (int)words.size(); i++)
		InsertR(i);
}

void CTrieTree::InsertR(int nIndex)
{
	CTrieNode* node = m_pRoot;
	const string& str = m_words[nIndex];
	for(auto it = str.rbegin(); it != str.rend(); it++)
	{
		if(!node->child[*it])
			node->child[*it] = new CTrieNode();
		node = node->child[*it];
	}
	node->nIndex = nIndex;
}

void CTrieTree::Destroy(CTrieNode* node)
{
	if(node)
	{
		for(auto it = node->child.begin(); it != node->child.end(); it++)
			Destroy(it->second);
		delete node;
	}
}

bool CTrieTree::IsPalindrome(const string& str) const
{
	int right = str.size()-1;
	int left = 0;
	while(left < right)
	{
		if(str[left] != str[right])
			return false;
		left++;
		right--;
	}
	return true;
}

void CTrieTree::Palindrome(CTrieNode* node, string& str, int nIndex)
{
	if(!node)
		return;
	if((node->nIndex != -1) && (node->nIndex != nIndex))	//node�ǵ����ҷǵ�ǰ��
	{
		if(IsPalindrome(str))
			m_pair.push_back(make_pair(nIndex, node->nIndex));
	}
	for(auto c = node->child.begin(); c != node->child.end(); c++)
	{
		str.push_back(c->first);
		Palindrome(c->second, str, nIndex);
		str.pop_back();
	}
}

void CTrieTree::CalcPair(int nIndex)
{
	CTrieNode* node = m_pRoot;
	const string& str = m_words[nIndex];
	for(auto p = str.begin(); p != str.end(); p++)
	{
		if(!node)
			return;
		if((node->nIndex != -1) && IsPalindrome(string(p, str.end())))
			m_pair.push_back(make_pair(nIndex, node->nIndex));
		node = node->child[*p];
	}
	string s;
	Palindrome(node, s, nIndex);	//��nodeΪ�������еĻ��Ĵ����ǽ�
}

void CTrieTree::PrintPair()
{
	int i,j;
	for(auto p = m_pair.begin(); p != m_pair.end(); p++)
	{
		i = p->first;
		j = p->second;
		cout << '(' << i << ", " << j << ")\t" << m_words[i] << '\t' << m_words[j] << '\n';
	}
}

void CTrieTree::PalindromePair()
{
	for(int i = 0; i < (int)m_words.size(); i++)
		CalcPair(i);
}

int _tmain(int argc, _TCHAR* argv[])
{
	vector<string> words(6);
	words[0] = "abcd";
	words[1] = "dcba";
	words[2] = "lls";
	words[3] = "s";
	words[4] = "sssll";
	words[5] = "sss";
	CTrieTree t(words);
	t.PalindromePair();
	t.PrintPair();
	return 0;
}

