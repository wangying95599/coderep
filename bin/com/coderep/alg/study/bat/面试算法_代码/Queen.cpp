// Queen.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <vector>
using namespace std;

class CQueen
{
private:
	int m_nQueen;
	vector<bool> m_Colomn;	//path�Ѿ�ռ�ݵ���
	vector<bool> m_MainDiagonal;	//path�Ѿ�ռ�ݵ����Խ���
	vector<bool> m_MinorDiagonal;	//path�Ѿ�ռ�ݵĴζԽ���
	vector<vector<int> > m_Answer;	//���ս�

public:
	CQueen(int N) : m_nQueen(N)
	{
		m_Colomn.resize(N, false);
		m_MainDiagonal.resize(2*N-1, false);
		m_MinorDiagonal.resize(2*N-1, false);
	}

	void Queen()
	{
		int* path = new int[m_nQueen];	//һ�����н�
		CalcNQueen(path, 0);
		delete[] path;
	}

private:
	void CalcNQueen(int* path, int row)
	{
		if(row == m_nQueen)
		{
			m_Answer.push_back(vector<int>(path, path+m_nQueen));
			return;
		}
		for(int col = 0; col < m_nQueen; col++)
		{
			if(CanLay(row, col))
			{
				path[row] = col;
				m_Colomn[col] = true;
				m_MinorDiagonal[row+col] = true;
				m_MainDiagonal[m_nQueen-1+row-col] = true;
				CalcNQueen(path, row+1);

				//����
				m_Colomn[col] = false;
				m_MinorDiagonal[row+col] = false;
				m_MainDiagonal[m_nQueen-1+row-col] = false;
			}
		}
	}

	bool CanLay(int row, int col) const
	{
		return !m_Colomn[col] && !m_MinorDiagonal[row+col] && !m_MainDiagonal[m_nQueen-1+row-col];
	}

public:
	void Print() const
	{
		cout << "���н�ĸ�����" << (int)m_Answer.size() << "\n";
		for(vector<vector<int> >::const_iterator it = m_Answer.begin(); it != m_Answer.end(); it++)
		{
			PrintOne(*it);
		}
	}

	void PrintOne(const vector<int>& v) const
	{
		for(vector<int>::const_iterator it = v.begin(); it != v.end(); it++)
			cout << *it << '\t';
		cout << endl;
	}
};

int _tmain(int argc, _TCHAR* argv[])
{
	CQueen queen(8);
	queen.Queen();
	queen.Print();
	return 0;
}