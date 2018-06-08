// Parentheses.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stack>
using namespace std;

bool IsLeftParentheses(char c)
{
	return (c == '(') ||
		(c == '[') || (c == '{');
}

bool IsMatch(char left, char c)
{
	if(left == '(')
		return c == ')';
	if(left == '[')
		return c == ']';
	if(left == '{')
		return c == '}';
	return false;
}
bool MatchParentheses(const char* p)
{
	stack<char> s;
	char cur;
	while(*p)
	{
		cur = *p;
		if(IsLeftParentheses(cur))
			s.push(cur);
		else //if(IsRightParentheses(cur))
		{
			if(s.empty() || !IsMatch(s.top(), cur))
				return false;
			s.pop();
		}
		p++;
	}
	return s.empty();
}

int _tmain(int argc, _TCHAR* argv[])
{
	char* p = "(({})[])[()]";
	bool bMatch = MatchParentheses(p);
	if(bMatch)
		cout << p << "括号匹配。\n";
	else
		cout << p << "括号不匹配。\n";
	return 0;
}