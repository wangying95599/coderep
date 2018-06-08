// ListPatition.cpp : 定义控制台应用程序的入口点。
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
		cout << p->value << " → ";
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
	//两个链表的头指针
	SNode* pLeftHead = new SNode(0);
	SNode* pRightHead = new SNode(0);

	//两个链表的当前最后一个元素
	SNode* left = pLeftHead;
	SNode* right = pRightHead;
	SNode* p = pHead->pNext;
	while(p)	//遍历原链表
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

	//将right链接到left尾部
	left->pNext = pRightHead->pNext;
	right->pNext = NULL;

	//将整理好的链表赋值给当前链表头部
	pHead->pNext = pLeftHead->pNext;

	delete pLeftHead;
	delete pRightHead;
}

SNode* Add(SNode* pHead1, SNode* pHead2)
{
	SNode* pSum = new SNode(0);
	SNode* pTail = pSum;	//新结点插入到pTail的后面
	SNode* p1 = pHead1->pNext;
	SNode* p2 = pHead2->pNext;
	SNode* pCur;
	int carry = 0;	//进位
	int value;
	while(p1 && p2)
	{
		value = p1->value + p2->value + carry;
		carry = value / 10;
		value %= 10;
		pCur = new SNode(value);
		pTail->pNext = pCur;	//新结点链接到pTail的后面
		pTail = pCur;

		p1 = p1->pNext;	//处理下一位
		p2 = p2->pNext;
	}

	//处理较长的链
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

	//处理可能存在的进位
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
		if(bDup)	//此刻的pCur与原数据重复，删之
		{
			pPre->pNext = pNext;
			delete pCur;
		}
		else		//pCur未发现重复，则pPre后移
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