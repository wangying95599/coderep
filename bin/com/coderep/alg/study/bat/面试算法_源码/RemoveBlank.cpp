// Zw13.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
using namespace std;
/*
void SelectNode(const HuffmanNode* pHuffmanTree, int n, int& s1, int &s2)
{
	s1 = -1;	//��Чֵ
	s2 = -1;
	int nMin1 = -1;	//��Чֵ
	int nMin2 = -1;
	for(int i = 0; i < n; i++)
	{
		if((pHuffmanTree[i].nParent == 0) && (pHuffmanTree[i].nWeight > 0))
		{
			if((s1 < 0) || (nMin1 > pHuffmanTree[i].nWeight))
			{
				s2 = s1;
				nMin2 = nMin1;
				s1 = i;
				nMin1 = pHuffmanTree[s1].nWeight;
			}
			else if((s2 < 0) || (nMin2 > pHuffmanTree[i].nWeight))
			{
				s2 = i;
				nMin2 = pHuffmanTree[s2].nWeight;
			}
		}
	}
}*/


void Select(const int* a, int size, int& nMax, int& nSecondMax)
{
	nMax = a[0];
	bool bSecond = false;	//�ڶ������δ����ֵ
	for(int i = 1; i < size; i++)
	{
		if(nMax < a[i])
		{
			nSecondMax = nMax;
			nMax = a[i];
		}
		else if(!bSecond || (nSecondMax < a[i]))
		{
			nSecondMax = a[i];
			bSecond = true;
		}
	}
}

void RemoveBlank(char* pString)
{
	int j = 0;
	for(int i = 0; pString[i] != '\0'; i++)
	{
		if(pString[i] != ' ')
		{
			if(i != j)
			{
				pString[j] = pString[i];
			}
			j++;
		}
	}
	pString[j] = 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	//char str[] = "I have a dream.";
	//RemoveBlank(str);
	//cout << str << endl;
	int nMax, nSecondMax;
	int a[] = {5,5,8,8,10,3,4};
	Select(a, sizeof(a)/sizeof(int), nMax, nSecondMax);
	cout << nMax << endl;
	cout << nSecondMax << endl;
	return 0;
}