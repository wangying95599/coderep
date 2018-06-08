// MaxSub.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
using namespace std;

int maxSubArray(int A[], int n)
{
    int maxSum = A[0];  //ȫ����������������
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

            currSum = 0; //����Ҫ�ǵ����㣬����Ļ�sum���մ�ŵ�������������ĺ͡�
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

