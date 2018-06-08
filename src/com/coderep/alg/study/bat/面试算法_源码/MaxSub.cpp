// MaxSub.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
using namespace std;

int maxSubArray(int A[], int n)
{
    int maxSum = A[0];  //全负情况，返回最大负数
    int currSum = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            for (int k = i; k <= j; k++)
            {
                currSum += A[k];
            }
            if (currSum > maxSum)
                maxSum = currSum;

            currSum = 0; //这里要记得清零，否则的话sum最终存放的是所有子数组的和。
        }
    }
    return maxSum;
}

int _tmain(int argc, _TCHAR* argv[])
{
	string str;
	const char* s1 = str.c_str();

	int A[] = {0, 5};
	int i = maxSubArray(A, sizeof(A));
	cout << i << endl;
	return 0;
}

