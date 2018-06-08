// LongestParenthese.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <stack>
#include <vector>
using namespace std;

int GetLongestParenthese(const char* p)
{
	int size = (int)strlen(p);
	stack<int> s;
	int answer = 0;	//最终解
	int start = -1;	//左括号的前一个位置
	for(int i = 0; i < size; i++)
	{
		if(p[i] == '(')
		{
			s.push(i);
		}
		else	//p[i] == ')'
		{
			if(s.empty())
				start = i;
			else
			{
				s.pop();
				if(s.empty())
					answer = max(answer, i-start);
				else
					answer = max(answer, i-s.top());
			}
		}
	}
	return answer;
}

void Print(int i, int deep, int start, int answer)
{
	cout << i << '\t';
	cout << deep << '\t';
	cout << start << '\t';
	cout << answer << '\n';
}

int GetLongestParenthese2(const char* p)
{
	int size = (int)strlen(p);
	int answer = 0;	//最终解
	int deep = 0;	//遇到了多少左括号
	int start = -1;	//最深的(deep==0时)左括号的位置
					//其实，为了方便计算长度，该变量是最深左括号的前一个位置
	int i;
	for(i = 0; i < size; i++)
	{
		if(p[i] == '(')
		{
			deep++;
		}
		else	//p[i] == ')'
		{
			deep--;
			if(deep == 0)
			{
				answer = max(answer, i - start);
			}
			else if(deep < 0)	//说明右括号数目大于左括号，初始化为for循环前
			{
				deep = 0;
				start = i;
			}
		}
	}

	deep = 0;		//遇到了多少右括号
	start = size;	//最深的(deep==0时)右括号的位置
					//其实，为了方便计算长度，该变量是最深右括号的后一个位置
	for(i = size-1; i >= 0; i--)
	{
		if(p[i] == ')')
		{
			deep++;
		}
		else	//p[i] == '('
		{
			deep--;
			if(deep == 0)
			{
				answer = max(answer, start - i);
			}
			else if(deep < 0)	//说明右括号数目大于左括号，初始化为for循环前
			{
				deep = 0;
				start = i;
			}
		}
	}

	return answer;
}

int LargestRectangleArea(vector<int>& height)
{
	height.push_back(0);	//确保原数组height的最后一位能够得到计算

	stack<int> s;
	int answer = 0;
	int temp;	//临时变量
	for (int i = 0; i < (int)height.size(); )
	{
		if (s.empty() || height[i] > height[s.top()])
		{
			s.push(i);
			i++;
		}
		else
		{
			temp = s.top();
			s.pop();
			answer = max(answer,height[temp]*(s.empty() ? i : i-s.top()-1));
		}
	}
	return answer;
}

int TrappingRainWater(int A[], int n)
{
	int secHight = 0;	//当前找到的第二大的数
	int left = 0;
	int right = n-1;
	int trap = 0;	//依次遍历每个方柱能装水的容量
	while (left < right)
	{
		if (A[left] < A[right])
		{
			secHight = max(A[left], secHight);
			trap += (secHight-A[left]);
			left++;
		}
		else
		{
			secHight = max(A[right], secHight);
			trap += (secHight-A[right]);
			right--;
		}
	}
	return trap;
}

int _tmain(int argc, _TCHAR* argv[])
{
	//char p[] = "(((()()))";
	char p[] = "()(()))";
	int a = GetLongestParenthese(p);
	cout << a << endl;

	//int a[] = {0,1,0,2,1,0,1,3,2,1,2,1};
	//cout << TrappingRainWater(a, sizeof(a)/sizeof(int)) << endl;
	/*vector<int> height;
	height.push_back(2);
	height.push_back(7);
	height.push_back(5);
	height.push_back(6);
	height.push_back(4);
	cout << LargestRectangleArea(height) << endl;*/
	return 0;
}

