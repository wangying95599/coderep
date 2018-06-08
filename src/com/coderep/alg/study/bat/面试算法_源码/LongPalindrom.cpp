// LongPalindrom.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
using namespace std;

int CalcLongPalindrome(const char* str, int size)
{
	int mp = 1;
	int i,j;
	for(i = 0; i < size; i++)
	{
		//����
		j = 1;
		while((i-j >=0) && (i+j < size) && (str[i-j] == str[i+j]))
			j++;
		mp = max(2*j-1,mp);

		//ż��
		j = 0;
		while((i-j >=0) && (i+1+j < size) && str[i-j] == str[i+1+j])
			j++;
		mp = max(2*j,mp);
	}
	return mp;
}

int _tmain(int argc, _TCHAR* argv[])
{
	char* str = "abcdcddcebesebac";
	int s = CalcLongPalindrome(str, (int)strlen(str));
	cout << s << endl;
	return 0;
}