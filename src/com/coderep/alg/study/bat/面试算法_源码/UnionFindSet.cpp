// UnionFindSet.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
using namespace std;

class CUnionFindSet
{
private:
	int m_nN;
	int* m_pParent;
public:
	CUnionFindSet(int n);
	~CUnionFindSet();
	void Union(int i, int j);
	int Find(int i);
	void Print() const;
};

CUnionFindSet::CUnionFindSet(int n)
{
	m_nN = n;
	m_pParent = new int[m_nN];
	for(int i = 0; i < m_nN; i++)
		m_pParent[i] = i;
}

CUnionFindSet::~CUnionFindSet()
{
	if(m_pParent != NULL)
	{
		delete[] m_pParent;
		m_pParent = NULL;
	}
}

int CUnionFindSet::Find(int i)
{
	if((i < 0) || (i >= m_nN))
		return -1;

	int root = i;
	while(root != m_pParent[root])	//尚未到根节点
	{
		root = m_pParent[root];
	}

	int t = i;
	int p;
	while(t != root)
	{
		p = m_pParent[t];	//t2的原父节点
		m_pParent[t] = root;	//t2的父节点直接赋值给根t
		t = p;	//沿着原来的父节点继续向上查找
	}

	return root;
}

void CUnionFindSet::Union(int i, int j)
{
	if((i < 0) || (i >= m_nN) || (j < 0) || (j >= m_nN))
		return;

	int ri = Find(i);
	int rj = Find(j);
	if(ri != rj)
		m_pParent[ri] = rj;
}

void CUnionFindSet::Print() const
{
	for(int i = 0; i < m_nN; i++)
		cout << m_pParent[i] << '\t';
	cout << endl;
}

int CalcCompoment()
{
	const int N = 10;	//岛屿数量
	CUnionFindSet ufs(N);
	ufs.Union(2,6);	//根据边初始化并查集
	ufs.Union(5,6);
	ufs.Union(1,8);
	ufs.Union(2,9);
	ufs.Union(5,3);
	ufs.Union(4,8);
	ufs.Union(4,0);

	int* component = new int[N];
	memset(component, 0, N*sizeof(int));
	int i;
	for(i = 0; i < N; i++)	//计算每个岛屿的“首府”
		component[ufs.Find(i)]++;

	int nComponent = 0;	//统计“首府”的数目
	for(i = 0; i < N; i++)
	{
		if(component[i] != 0)
			nComponent++;
	}
	delete[] component;
	return nComponent;
}
int _tmain(int argc, _TCHAR* argv[])
{
	cout << CalcCompoment();
	return 0;
}

