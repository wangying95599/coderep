// BinaryTree.cpp : �������̨Ӧ�ó������ڵ㡣
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

typedef void (*VISIT)(int value);

class CBinaryTree
{
private:
	STreeNode* m_pRoot;

private:
	void Destroy(STreeNode* pRoot);
	bool _Insert(STreeNode*& pRoot, int value);				//�ݹ�
	bool _Insert2(int value);								//�ǵݹ�
	void _PreOrder(STreeNode* pRoot, VISIT Visit) const;	//�ݹ�
	void _PreOrder2(VISIT Visit) const;						//�ǵݹ�
	void _InOrder(STreeNode* pRoot, VISIT Visit) const;		//�ݹ�
	void _InOrder2(VISIT Visit) const;						//�ǵݹ�
	void _InOrder3(VISIT Visit) const;						//�ǵݹ�
	void _PostOrder(STreeNode* pRoot, VISIT Visit) const;	//�ݹ�
	void _PostOrder2(VISIT Visit) const;					//�ǵݹ�
	void DeleteChildless(STreeNode* pParent, STreeNode* pNode);	//pNode����
	void DeleteSingleSon(STreeNode* pParent, STreeNode* pNode); //pNode��pParentΨһ�ӽ��
public:
	CBinaryTree();
	~CBinaryTree();
	bool Insert(int value);
	bool Delete(int value);
	STreeNode* Find(int value) const;
	void PreOrder(VISIT Visit) const;
	void InOrder(VISIT Visit) const;
	void PostOrder(VISIT Visit) const;
	const STreeNode* LCA(const STreeNode* p1, const STreeNode* p2) const;
	int LCA2(const STreeNode* u, const STreeNode* v);
};

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
	//return _Insert(m_pRoot, value);
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
		else	//�ҵ���ɾ��ֵ
		{
			break;
		}
	}
	if(!pNode)	//û���ҵ�
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
		STreeNode* pCur = pNode;	//�ݴ��ɾ���ڵ�
		pParent = pNode;
		pNode = pNode->pLeft;
		while(pNode->pRight)
		{
			pParent = pNode;
			pNode = pNode->pRight;
		}
		pCur->value = pNode->value;	//ɾ������
		if(!pNode->pLeft)	//����Ҳ��
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
	//_InOrder2(Visit);
	//_InOrder3(Visit);
}

void CBinaryTree::_InOrder(STreeNode* pRoot, VISIT Visit) const
{
	if(pRoot)
	{
		_InOrder(pRoot->pLeft, Visit);
		Visit(pRoot->value);
		_InOrder(pRoot->pRight, Visit);
	}
}

void CBinaryTree::_InOrder2(VISIT Visit) const
{
	stack<STreeNode*> s;
	STreeNode* pCur = m_pRoot;
	while(pCur || !s.empty())
	{
		while(pCur)	//��������
		{
			s.push(pCur);
			pCur = pCur->pLeft;
		}
		if(!s.empty())
		{
			pCur = s.top();	//��������Ϊ�յĽ��
			s.pop();
			Visit(pCur->value);
			pCur = pCur->pRight;	//ת���Һ���
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
		if(times == 0)	//��һ��ѹջ
		{
			if(pCur->pRight)
				s.push(make_pair(pCur->pRight, 0));
			s.push(make_pair(pCur, 1));	//�ڶ���ѹջ
			if(pCur->pLeft)
				s.push(make_pair(pCur->pLeft, 0));
		}
		else
		{
			Visit(pCur->value);
		}
	}
}

void CBinaryTree::PreOrder(VISIT Visit) const
{
	//_PreOrder(m_pRoot, Visit);
	_PreOrder2(Visit);
}

void CBinaryTree::_PreOrder(STreeNode* pRoot, VISIT Visit) const
{
	if(pRoot)
	{
		Visit(pRoot->value);
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
		Visit(pCur->value);
		if(pCur->pRight)
			s.push(pCur->pRight);
		if(pCur->pLeft)
			s.push(pCur->pLeft);
	}
}

void CBinaryTree::PostOrder(VISIT Visit) const
{
	_PostOrder(m_pRoot, Visit);
	//_PostOrder2(Visit);
}

void CBinaryTree::_PostOrder(STreeNode* pRoot, VISIT Visit) const
{
	if(pRoot)
	{
		_PostOrder(pRoot->pLeft, Visit);
		_PostOrder(pRoot->pRight, Visit);
		Visit(pRoot->value);
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
		if(times == 0)	//��һ��ѹջ
		{
			s.push(make_pair(pCur, 1));	//�ڶ���ѹջ
			if(pCur->pRight)
				s.push(make_pair(pCur->pRight, 0));
			if(pCur->pLeft)
				s.push(make_pair(pCur->pLeft, 0));
		}
		else
		{
			Visit(pCur->value);
		}
	}
}

const STreeNode* CBinaryTree::LCA(const STreeNode* p1, const STreeNode* p2) const
{
	int left,right;
	if(p1->value < p2->value)
	{
		left = p1->value;
		right = p2->value;
	}
	else
	{
		left = p2->value;
		right = p1->value;
	}


	STreeNode* pLCA = m_pRoot;
	while(true)
	{
		if(pLCA->value > right)
		{
			pLCA = pLCA->pLeft;
		}
		else if(pLCA->value < left)
		{
			pLCA = pLCA->pRight;
		}
		else
		{
			return pLCA;
		}
	}
	return pLCA;
}


int CBinaryTree::LCA2(const STreeNode* u, const STreeNode* v)
{
	const STreeNode* t = m_pRoot;
    int left = u->value;
    int right = v->value;    
    const STreeNode* parent = NULL;    

    //����������ڣ������������ҽ�㣬���ԣ�����  
    if (left > right) {    
        int temp = left;    
        left = right;    
        right = temp;    
    }    

    while (true)
	{    
        //���tС��u��v����t���������в���  
        if (t->value < left) {    
            parent = t;    
            t = t->pRight;    

        //���t����u��v����t���������в���  
        } else if (t->value > right) {    
            parent = t;    
            t = t->pLeft;    
        } else if (t->value == left || t->value == right) {    
            return parent->value;    
        } else {    
            return t->value;    
        }    
    }
	return 0;
}  

void PrintValue(int value)
{
	cout << value << '\t';
}

void Print(const int* pData, int size)
{
	for(int i = 0; i < size; i++)
		cout << pData[i] << '\t';
	cout << endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
/*	const int N = 20;
	int data[N];
	int i;
	for(i = 0; i < N; i++)
		data[i] = rand() % 100;
	Print(data, N);

	CBinaryTree tree;
	for(i = 0; i < N; i++)
		tree.Insert(data[i]);

	tree.InOrder(PrintValue);
	cout << endl;*/

	CBinaryTree tree;
	tree.Insert(10);
	tree.Insert(5);
	tree.Insert(1);
	tree.Insert(7);
	const STreeNode* p = tree.LCA(tree.Find(10), tree.Find(5));
	cout << p->value << endl;

	int value = tree.LCA2(tree.Find(10), tree.Find(5));
	return 0;
}
