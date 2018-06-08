// Palindrom.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
using namespace std;

bool IsPalindrome(const char *s, int n)
{
 	if (s == NULL || n < 1)	//空串认为是回文串
 		return true;

	// 初始化头指针和尾指针
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

	// m定位到字符串的中间位置      
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

