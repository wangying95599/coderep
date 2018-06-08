// Palindrom.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
using namespace std;

bool IsPalindrome(const char *s, int n)
{
 	if (s == NULL || n < 1)	//�մ���Ϊ�ǻ��Ĵ�
 		return true;

	// ��ʼ��ͷָ���βָ��
 	const char* front = s;
 	const char* back = s+ n - 1;

 	while (front < back)
 	{
 		if (*front != *back)
 		{
 			return false;
 		}
 		++front;
 		--back;
 	}
 	return true;
}

bool IsPalindrome2(const char *s, int n)
{
 	if (s == NULL || n < 1)
 		return true;

	// m��λ���ַ������м�λ��      
 	int m = ((n >> 1) - 1) >= 0 ? (n >> 1) - 1 : 0;
 	const char* first = s + m;
 	const char* second = s + n - 1 - m;

 	while (first >= s)
 	{
 		if (*first!= *second)
 		{
 			return false;
 		}
 		first--;
 		second++;
 	}
 	return true;
}

int _tmain(int argc, _TCHAR* argv[])
{
	char str[] = "aabba";
	bool b = IsPalindrome2(str, sizeof(str)/sizeof(char)-1);
	cout << b;
	return 0;
}

