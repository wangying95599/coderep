// YoungTableau.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
using namespace std;

#define INFINITY 100000
class CYoung
{
private:
	int m_row;
	int m_col;
	int **m_pData;
public:
	CYoung(int,int);
	~CYoung();
	bool Insert(int x);
	void PrintArray() const;
};

//���캯����ɳ�Ա������ʼ��
CYoung::CYoung(int row, int col) 
{
	m_row=row;
	m_col=col;
	int **m_pData= new int *[m_row];//��ά�����ǰ��������洢
	for (int i=0;i<m_row;i++)//����ÿһ�������пռ�
		m_pData[i]=new int[m_col];
	for(int i=0;i<m_row;i++)
		for(int j=0;j<m_col;j++)
			m_pData[i][j]=INFINITY;//��ʼ��ʱ������ֵ��ΪINFINITY
}

//�������������ͷ�֮ǰ������ڴ�
CYoung::~CYoung()
{
	for (int i=0;i<m_row;i++)
	{
		delete []m_pData[i];
	}
	delete []m_pData;
}

//��ӡ���Ͼ���
void CYoung::PrintArray() const 
{
	for(int i=0;i<m_row;i++)
	{
		for(int j=0;j<m_col;j++)
			cout<<m_pData[i][j]<<"  ";
		cout<<endl;
	}
	cout<<endl;
}

//���Ͼ���Ĳ��뺯��insert
bool CYoung::Insert(int x)
{
	int row=m_row-1;
	int col=m_col-1;
	if(m_pData[row][col]<INFINITY) //�൱�ھ���������½ǵ�Ԫ�ض���ռ�ݣ����Դ�ʱ���Ͼ��������������ټ�������ֵ
		return false;
	m_pData[row][col]=x;
	int r=row;
	int c=col;//�к��еĳ�ʼ��
	while((row>=0) || (col>=0))
	{
		if((row>=1)  && (m_pData[row-1][col]>m_pData[r][c]))
		{
			r=row-1;
			c=col;
		}
		if((col>=1)  && (m_pData[row][col-1]>m_pData[r][c]))
		{
			r=row;
			c=col-1;
		}
		if((r==row)&&(c==col)) //�ҵ�λ��
			break;
		swap(m_pData[row][col],m_pData[r][c]);
		row=r;
		col=c;
	}
	return true;
}

int _tmain(int argc, _TCHAR* argv[])
{
	CYoung cy(5,4);//����ʵ����Ϊ����cy������5��4�еľ���
	int a[]={50,20,15,3,25,70,40,18,55,10};
	int length=sizeof(a)/sizeof(int);
	for(int i=0;i<length;i++)
	{
		cy.Insert(a[i]);//�������Ԫ�����β��뵽������
		cy.PrintArray();//ÿ�β���Ԫ�غ󶼴�ӡ����Ӧ�����Ͼ���
	}
	return 0;
}

