// YoungTableau.cpp : 定义控制台应用程序的入口点。
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

//构造函数完成成员变量初始化
CYoung::CYoung(int row, int col) 
{
	m_row=row;
	m_col=col;
	int **m_pData= new int *[m_row];//二维数组是按照行来存储
	for (int i=0;i<m_row;i++)//对于每一行申请列空间
		m_pData[i]=new int[m_col];
	for(int i=0;i<m_row;i++)
		for(int j=0;j<m_col;j++)
			m_pData[i][j]=INFINITY;//初始化时，所有值赋为INFINITY
}

//析构函数用于释放之前申请的内存
CYoung::~CYoung()
{
	for (int i=0;i<m_row;i++)
	{
		delete []m_pData[i];
	}
	delete []m_pData;
}

//打印杨氏矩阵
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

//杨氏矩阵的插入函数insert
bool CYoung::Insert(int x)
{
	int row=m_row-1;
	int col=m_col-1;
	if(m_pData[row][col]<INFINITY) //相当于矩阵的最右下角的元素都被占据，所以此时杨氏矩阵已满，不能再继续插入值
		return false;
	m_pData[row][col]=x;
	int r=row;
	int c=col;//行和列的初始化
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
		if((r==row)&&(c==col)) //找到位置
			break;
		swap(m_pData[row][col],m_pData[r][c]);
		row=r;
		col=c;
	}
	return true;
}

int _tmain(int argc, _TCHAR* argv[])
{
	CYoung cy(5,4);//将类实例化为对象cy，构造5行4列的矩阵
	int a[]={50,20,15,3,25,70,40,18,55,10};
	int length=sizeof(a)/sizeof(int);
	for(int i=0;i<length;i++)
	{
		cy.Insert(a[i]);//将数组的元素依次插入到矩阵中
		cy.PrintArray();//每次插入元素后都打印出相应的杨氏矩阵
	}
	return 0;
}

