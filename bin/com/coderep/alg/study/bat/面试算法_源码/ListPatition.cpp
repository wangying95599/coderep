// ListPatition.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <math.h>
#include <iostream>
using namespace std;

typedef struct tagSNode
{
	int value;
	tagSNode* pNext;

	tagSNode(int v) : value(v), pNext(NULL) {}
}SNode;

void Print(const SNode* pHead)
{
	if(!pHead)
		return;

	SNode* p = pHead->pNext;
	while(p)
	{
		cout << p->value << " �� ";
		p = p->pNext;
	}
	cout << endl;
}

void Destroy(SNode* p)
{
	SNode* next;
	while(p)
	{
		next = p->pNext;
		delete p;
		p = next;
	}
}

void Partition(SNode* pHead, int pivotKey)
{
	//���������ͷָ��
	SNode* pLeftHead = new SNode(0);
	SNode* pRightHead = new SNode(0);

	//��������ĵ�ǰ���һ��Ԫ��
	SNode* left = pLeftHead;
	SNode* right = pRightHead;
	SNode* p = pHead->pNext;
	while(p)	//����ԭ����
	{
		if(p->value < pivotKey)
		{
			left->pNext = p;
			left = p;
		}
		else
		{
			right->pNext = p;
			right = p;
		}
		p = p->pNext;
	}

	//��right���ӵ�leftβ��
	left->pNext = pRightHead->pNext;
	right->pNext = NULL;

	//������õ�����ֵ����ǰ����ͷ��
	pHead->pNext = pLeftHead->pNext;

	delete pLeftHead;
	delete pRightHead;
}

SNode* Add(SNode* pHead1, SNode* pHead2)
{
	SNode* pSum = new SNode(0);
	SNode* pTail = pSum;	//�½����뵽pTail�ĺ���
	SNode* p1 = pHead1->pNext;
	SNode* p2 = pHead2->pNext;
	SNode* pCur;
	int carry = 0;	//��λ
	int value;
	while(p1 && p2)
	{
		value = p1->value + p2->value + carry;
		carry = value / 10;
		value %= 10;
		pCur = new SNode(value);
		pTail->pNext = pCur;	//�½�����ӵ�pTail�ĺ���
		pTail = pCur;

		p1 = p1->pNext;	//������һλ
		p2 = p2->pNext;
	}

	//����ϳ�����
	SNode* p = p1 ? p1 : p2;
	while(p)
	{
		value = p->value + carry;
		carry = value / 10;
		value %= 10;
		pCur = new SNode(value);
		pTail->pNext = pCur;
		pTail = pCur;
		p = p->pNext;
	}

	//������ܴ��ڵĽ�λ
	if(carry != 0)
		pTail->pNext = new SNode(carry);
	return pSum;
}

void Reverse(SNode* pHead, int from, int to)
{
	SNode* pCur = pHead->pNext;
	int i;
	for(i = 0; i < from-1; i++)
	{
		pHead = pCur;
		pCur = pCur->pNext;
	}

	SNode* pPre = pCur;
	pCur = pCur->pNext;
	to--;
	SNode* pNext;
	for(;i < to; i++)
	{
		pNext = pCur->pNext;
		pCur->pNext = pHead->pNext;
		pHead->pNext = pCur;
		pPre->pNext = pNext;
		pCur = pNext;
	}
}

void DeleteDuplicateNode(SNode* pHead)
{
	SNode* pPre = pHead->pNext;
	SNode* pCur;
	while(pPre)
	{
		pCur = pPre->pNext;
		if(pCur && (pCur->value == pPre->value))
		{
			pPre->pNext = pCur->pNext;
			delete pCur;
		}
		else
		{
			pPre = pCur;
		}
	}
}

void DeleteDuplicateNode2(SNode* pHead)
{
	SNode* pPre = pHead;
	SNode* pCur = pPre->pNext;
	SNode* pNext;
	while(pCur)
	{
		pNext = pCur->pNext;
		while(pNext && (pCur->value == pNext->value))
		{
			pPre->pNext = pNext;
			delete pCur;
			pCur = pNext;
			pNext = pCur->pNext;
		}
		pPre = pCur;
		pCur = pNext;
	}
}

void DeleteDuplicateNode3(SNode* pHead)
{
	SNode* pPre = pHead;
	SNode* pCur = pPre->pNext;
	SNode* pNext;
	bool bDup;
	while(pCur)
	{
		pNext = pCur->pNext;
		bDup = false;
		while(pNext && (pCur->value == pNext->value))
		{
			pPre->pNext = pNext;
			delete pCur;
			pCur = pNext;
			pNext = pCur->pNext;
			bDup = true;
		}
		if(bDup)	//�˿̵�pCur��ԭ�����ظ���ɾ֮
		{
			pPre->pNext = pNext;
			delete pCur;
		}
		else		//pCurδ�����ظ�����pPre����
		{
			pPre = pCur;
		}
		pCur = pNext;
	}
}
int _tmain(int argc, _TCHAR* argv[])
{
	SNode* pHead = new SNode(0);
	int data[] = {2,3,3,5,7,8,8,8,9,9,10};
	int size = sizeof(data) / sizeof(int);
	for(int i = size-1; i >= 0; i--)
	{
		SNode* p = new SNode(data[i]);
		p->pNext = pHead->pNext;
		pHead->pNext = p;
	}
	Print(pHead);
	DeleteDuplicateNode2(pHead);
	Print(pHead);
	Destroy(pHead);
	return 0;
}