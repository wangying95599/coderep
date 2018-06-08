// WordBreak.cpp : �������̨Ӧ�ó������ڵ㡣
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
	sentence.reserve(size+s);	//�����㹻�����ݳ���
	int start = 0, end = 0;
	for(int i = s-2; i >= 0; i--)	//oneBreak[size-1]==0�����⴦��
	{
		end = oneBreak[i];	//�����ˣ�k=oneBreak[i]��ֵ��ʾ��string[k]��ǰ�����break
		sentence += str.substr(start, end-start);
		sentence += ' ';
		start = end;
	}
	sentence += str.substr(start, size-start);	//���һ��break
}

//����str[0...cur-1]��wordbreak����Щ
void FindAnswer(const vector<vector<bool> >& chess, const string& str, int cur,
				vector<int>& oneBreak, vector<string>& answer)
{
	if(cur == 0)	//Ҷ��
	{
		AddAnswer(str, oneBreak, answer);
		return;
	}
	int size = (int)str.length();
	for(int i = 0; i < cur-1; i++)
	{
		if(chess[cur][i])	//str[i...cur]�ڴʵ���
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
	//chess[i][j]��str[0...i-1]�У��Ƿ�����ڵ�j��Ԫ�ص�ǰ���break
	vector<vector<bool> > chess(size+1, vector<bool>(size));
	vector<bool> f(size+1);	//f[i]��str[0...i-1]�Ƿ��ڴʵ���

	int i,j;
	f[0] = true;	//�մ��ڴʵ���
	for(i = 1; i <= size; i++)	//str[0...i-1]������Ϊi
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
	vector<int> oneBreak;	//һ�ֿ��еĻ���
	FindAnswer(chess, str, size, oneBreak, answer);	//����str[0...size-1]��wordbreak����Щ
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
	vector<bool> f(size+1);	//f[i]��str[0...i-1]�Ƿ��ڴʵ���

	f[0] = true;
	int i,j;
	for(i = 1; i <= size; i++)	//str[0...i-1]������Ϊi
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
	vector<int> f(size+1);	//f[i]��str[0...i-1]�Ƿ��ڴʵ���
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
	dict.insert("������");
	dict.insert("����");
	dict.insert("������");
	dict.insert("����");
	dict.insert("���Ҳ�");
	dict.insert("�Ҳ���");
	dict.insert("��");
	dict.insert("dog");
	string str = "���������������Ҳ�����";
	//vector<string> answer;
	//WordBreak(dict, str, answer);
	//Print(answer);

	int size = (int)str.length();
	vector<int> f(size+1);	//f[i]��str[0...i-1]�Ƿ��ڴʵ���
	memset(&f.front() + 1, 0, sizeof(int)*size);
	f[0] = 1;
	cout << f[size] << endl;
	cout << WordBreak3(dict, str, f) << endl;
	cout << WordBreak2(dict, str) << endl;
	return 0;
}