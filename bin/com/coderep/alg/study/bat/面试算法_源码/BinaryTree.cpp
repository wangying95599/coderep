// BinaryTree.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <math.h>
#include <iostream>
#include <stack>
using namespace std;

typedef struct tagSTreeNode
{
	int value;
	tagSTreeNode* pLeft;
	tagSTreeNode* pRight;

	tagSTreeNode(int v) : value(v), pLeft(NULL), pRight(NULL) {}
}STreeNode;

typedef void (*VISIT)(STreeNode* pRoot);

class CBinaryTree
{
private:
	STreeNode* m_pRoot;

private:
	void Destroy(STreeNode* pRoot);
	bool _Insert(STreeNode*& pRoot, int value);				
	bool _Insert2(int value);								
	void _PreOrder(STreeNode* pRoot, VISIT Visit) const;	
	void _PreOrder2(VISIT Visit) const;						
	void _InOrder(STreeNode* pRoot, VISIT Visit) const;		
	void _InOrder2(VISIT Visit) const;						
	void _InOrder3(VISIT Visit) const;						
	void _PostOrder(STreeNode* pRoot, VISIT Visit) const;	
	void _PostOrder2(VISIT Visit) const;					
	void DeleteChildless(STreeNode* pParent, STreeNode* pNode);	
	void DeleteSingleSon(STreeNode* pParent, STreeNode* pNode); 
	bool _LargestBST(STreeNode* pRoot, int& nMin, int& nMax, int& count, int& nNumber, STreeNode*& pNode) const;
public:
	CBinaryTree();
	~CBinaryTree();
	bool Insert(int value);
	bool Delete(int value);
	STreeNode* Find(int value) const;
	void PreOrder(VISIT Visit) const;
	void InOrder(VISIT Visit) const;
	void PostOrder(VISIT Visit) const;
	int LargestBST(STreeNode*& pNode) const;	//计算this中包含的最大二叉搜索树
};

int CBinaryTree::LargestBST(STreeNode*& pNode) const
{
	int nMin, nMax, count;
	int nNumber = 0;
	_LargestBST(m_pRoot, nMin, nMax, count, nNumber, pNode);
	return nNumber;
}

bool CBinaryTree::_LargestBST(STreeNode* pRoot, int& nMin, int& nMax,
	int& count, int& nNumber, STreeNode*& pNode) const
{
	count = 0;
	if(!pRoot)
		return true;
	int nMin1 = INT_MAX, nMin2 = INT_MAX;
	int nMax1 = INT_MIN, nMax2 = INT_MIN;
	int c1, c2;
	if(!_LargestBST(pRoot->pLeft, nMin1, nMax1, c1, nNumber, pNode))
		return false;
	if(!_LargestBST(pRoot->pRight, nMin2, nMax2, c2, nNumber, pNode))
		return false;
	if((pRoot->value < nMax1) || (pRoot->value > nMin2))
		return false;
	count = c1 + c2 + 1;
	nMin = min(nMin1, pRoot->value);
	nMax = max(nMax2, pRoot->value);
	if(count > nNumber)
	{
		nNumber = count;
		pNode = pRoot;
	}
	return true;
}

CBinaryTree::CBinaryTree()
{
	m_pRoot = NULL;
}

CBinaryTree::~CBinaryTree()
{
	if(m_pRoot)
	{
		Destroy(m_pRoot);
		m_pRoot = NULL;
	}
}

void CBinaryTree::Destroy(STreeNode* pRoot)
{
	if(pRoot)
	{
		Destroy(pRoot->pLeft);
		Destroy(pRoot->pRight);
		delete pRoot;
	}
}

STreeNode* CBinaryTree::Find(int value) const
{
	if(!m_pRoot)
		return NULL;

	STreeNode* pNode = m_pRoot;
	while(pNode)
	{
		if(value < pNode->value)
			pNode = pNode->pLeft;
		else if(value > pNode->value)
			pNode = pNode->pRight;
		else
			return pNode;
	}
	return NULL;
}

bool CBinaryTree::Insert(int value)
{
	return _Insert2(value);
}

bool CBinaryTree::_Insert(STreeNode*& pRoot, int value)
{
	if(!pRoot)
	{
		pRoot = new STreeNode(value);
		return true;
	}
	if(value < pRoot->value)
		return _Insert(pRoot->pLeft, value);
	if(value > pRoot->value)
		return _Insert(pRoot->pRight, value);
	return false;
}

bool CBinaryTree::_Insert2(int value)
{
	if(!m_pRoot)
	{
		m_pRoot = new STreeNode(value);
		return true;
	}
	STreeNode* pNode = m_pRoot;
	STreeNode* pCur = m_pRoot;
	while(pNode)
	{
		pCur = pNode;
		if(value < pNode->value)
			pNode = pNode->pLeft;
		else if(value > pNode->value)
			pNode = pNode->pRight;
		else
			return false;
	}
	if(value < pCur->value)
		pCur->pLeft = new STreeNode(value);
	else if(value > pCur->value)
		pCur->pRight = new STreeNode(value);
	return true;
}

bool CBinaryTree::Delete(int value)
{
	if(!m_pRoot)
		return false;

	STreeNode* pNode = m_pRoot;
	STreeNode* pParent = NULL;
	while(pNode)
	{
		if(value < pNode->value)
		{
			pParent = pNode;
			pNode = pNode->pLeft;
		}
		else if(value > pNode->value)
		{
			pParent = pNode;
			pNode = pNode->pRight;
		}
		else	
		{
			break;
		}
	}
	if(!pNode)	
		return false;

	if(!pNode->pLeft && !pNode->pRight)
	{
		DeleteChildless(pParent, pNode);
	}
	else if(!pNode->pLeft || !pNode->pRight)
	{
		DeleteSingleSon(pParent, pNode);
	}
	else
	{
		STreeNode* pCur = pNode;	
		pParent = pNode;
		pNode = pNode->pLeft;
		while(pNode->pRight)
		{
			pParent = pNode;
			pNode = pNode->pRight;
		}
		pCur->value = pNode->value;	
		if(!pNode->pLeft)	
			DeleteChildless(pParent, pNode);
		else
			DeleteSingleSon(pParent, pNode);
	}
	return true;
}
void CBinaryTree::DeleteChildless(STreeNode* pParent, STreeNode* pNode)
{
	if(pNode == m_pRoot)
		m_pRoot = NULL;
	else if(pParent->pLeft == pNode)
		pParent->pLeft = NULL;
	else
		pParent->pRight = NULL;
	delete pNode;
}

void CBinaryTree::DeleteSingleSon(STreeNode* pParent, STreeNode* pNode)
{
	STreeNode* pGrandSon = pNode->pLeft ? pNode->pLeft : pNode->pRight;
	if(pNode == m_pRoot)
		m_pRoot = pGrandSon;
	else if(pParent->pLeft == pNode)
		pParent->pLeft = pGrandSon;
	else
		pParent->pRight = pGrandSon;
	delete pNode;
}

void CBinaryTree::InOrder(VISIT Visit) const
{
	_InOrder(m_pRoot, Visit);
	
	
}

void CBinaryTree::_InOrder(STreeNode* pRoot, VISIT Visit) const
{
	if(pRoot)
	{
		_InOrder(pRoot->pLeft, Visit);
		Visit(pRoot);
		_InOrder(pRoot->pRight, Visit);
	}
}

void CBinaryTree::_InOrder2(VISIT Visit) const
{
	stack<STreeNode*> s;
	STreeNode* pCur = m_pRoot;
	while(pCur || !s.empty())
	{
		while(pCur)	
		{
			s.push(pCur);
			pCur = pCur->pLeft;
		}
		if(!s.empty())
		{
			pCur = s.top();	
			s.pop();
			Visit(pCur);
			pCur = pCur->pRight;	
		}
	}
}

void CBinaryTree::_InOrder3(VISIT Visit) const
{
	if(!m_pRoot)
		return;

	stack<pair<STreeNode*, int> > s;
	s.push(make_pair(m_pRoot, 0));
	int times;
	STreeNode* pCur;
	while(!s.empty())
	{
		pCur = s.top().first;
		times = s.top().second;
		s.pop();
		if(times == 0)	
		{
			if(pCur->pRight)
				s.push(make_pair(pCur->pRight, 0));
			s.push(make_pair(pCur, 1));	
			if(pCur->pLeft)
				s.push(make_pair(pCur->pLeft, 0));
		}
		else
		{
			Visit(pCur);
		}
	}
}

void CBinaryTree::PreOrder(VISIT Visit) const
{
	
	_PreOrder2(Visit);
}

void CBinaryTree::_PreOrder(STreeNode* pRoot, VISIT Visit) const
{
	if(pRoot)
	{
		Visit(pRoot);
		_PreOrder(pRoot->pLeft, Visit);
		_PreOrder(pRoot->pRight, Visit);
	}
}

void CBinaryTree::_PreOrder2(VISIT Visit) const
{
	if(!m_pRoot)
		return;

	stack<STreeNode*> s;
	s.push(m_pRoot);
	STreeNode* pCur;
	while(!s.empty())
	{
		pCur = s.top();
		s.pop();
		Visit(pCur);
		if(pCur->pRight)
			s.push(pCur->pRight);
		if(pCur->pLeft)
			s.push(pCur->pLeft);
	}
}

void CBinaryTree::PostOrder(VISIT Visit) const
{
	_PostOrder(m_pRoot, Visit);
	
}

void CBinaryTree::_PostOrder(STreeNode* pRoot, VISIT Visit) const
{
	if(pRoot)
	{
		_PostOrder(pRoot->pLeft, Visit);
		_PostOrder(pRoot->pRight, Visit);
		Visit(pRoot);
	}
}

void CBinaryTree::_PostOrder2(VISIT Visit) const
{
	if(!m_pRoot)
		return;

	stack<pair<STreeNode*, int> > s;
	s.push(make_pair(m_pRoot, 0));
	int times;
	STreeNode* pCur;
	while(!s.empty())
	{
		pCur = s.top().first;
		times = s.top().second;
		s.pop();
		if(times == 0)	
		{
			s.push(make_pair(pCur, 1));	
			if(pCur->pRight)
				s.push(make_pair(pCur->pRight, 0));
			if(pCur->pLeft)
				s.push(make_pair(pCur->pLeft, 0));
		}
		else
		{
			Visit(pCur);
		}
	}
}

void PrintValue(STreeNode* pNode)
{
	cout << pNode->value << '\t';
}

void ChangeValue(STreeNode* pNode)
{
	pNode->value = rand() % 100;
}

void Print(const int* pData, int size)
{
	for(int i = 0; i < size; i++)
		cout << pData[i] << '\t';
	cout << endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
	//构造输入数据
	CBinaryTree tree;
	for(int i = 0; i < 10; i++)
		tree.Insert(rand() % 100);
	tree.InOrder(ChangeValue);

	tree.InOrder(PrintValue);	//中序遍历
	tree.PreOrder(PrintValue);	//前序遍历

	//计算
	STreeNode* pNode;
	int nLargestNumber = tree.LargestBST(pNode);
	cout << pNode->value << '\t' << nLargestNumber << endl;
	return 0;
}

