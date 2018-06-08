// Parentheses.cpp : �������̨Ӧ�ó������ڵ㡣
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
		cout << p << "����ƥ�䡣\n";
	else
		cout << p << "���Ų�ƥ�䡣\n";
	return 0;
}