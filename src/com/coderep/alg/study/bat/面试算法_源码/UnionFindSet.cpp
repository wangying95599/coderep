// UnionFindSet.cpp : �������̨Ӧ�ó������ڵ㡣
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
	while(root != m_pParent[root])	//��δ�����ڵ�
	{
		root = m_pParent[root];
	}

	int t = i;
	int p;
	while(t != root)
	{
		p = m_pParent[t];	//t2��ԭ���ڵ�
		m_pParent[t] = root;	//t2�ĸ��ڵ�ֱ�Ӹ�ֵ����t
		t = p;	//����ԭ���ĸ��ڵ�������ϲ���
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
	const int N = 10;	//��������
	CUnionFindSet ufs(N);
	ufs.Union(2,6);	//���ݱ߳�ʼ�����鼯
	ufs.Union(5,6);
	ufs.Union(1,8);
	ufs.Union(2,9);
	ufs.Union(5,3);
	ufs.Union(4,8);
	ufs.Union(4,0);

	int* component = new int[N];
	memset(component, 0, N*sizeof(int));
	int i;
	for(i = 0; i < N; i++)	//����ÿ������ġ��׸���
		component[ufs.Find(i)]++;

	int nComponent = 0;	//ͳ�ơ��׸�������Ŀ
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

