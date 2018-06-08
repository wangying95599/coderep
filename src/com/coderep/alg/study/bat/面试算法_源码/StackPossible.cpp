// StackPossible.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stack>
using namespace std;

bool IsPossible(const char* strIn, const char* strOut)
{
	stack<char> s;
	while(*strOut)
	{
		if(!s.empty() && (s.top() == *strOut))
		{
			s.pop();
			strOut++;
		}
		else
		{
			if(*strIn == 0)
				return false;
			s.push(*strIn);
			strIn++;
		}
	}
	return true;
}
int _tmain(int argc, _TCHAR* argv[])
{
	char* strIn = "ABCDEFG";
	char* strOut = "BAEDFGC";
	bool b = IsPossible(strIn, strOut);
	cout << b <<endl;
	return 0;
}