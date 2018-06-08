// Sudoku.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <vector>
using namespace std;

class CSudoku
{
private:
	int m_chess[9][9];
	int m_result[9][9];
	bool m_bSolve;
	int m_nCount;

public:
	CSudoku(int chess[9][9])
	{
		memcpy(m_chess, chess, sizeof(m_chess));
		m_bSolve = false;
		m_nCount = 0;
	}

	bool IsValid(int i, int j)
	{
		int t = m_chess[i][j];
		int k;
		for(k = 0; k < 9; k++)
		{
			if((j != k) && (t == m_chess[i][k]))	//列
				return false;
			if((i != k) && (t == m_chess[k][j]))	//行
				return false;
		}
		int iGrid = (i / 3) * 3;
		int jGrid = (j / 3) * 3;
		int k1,k2;
		for(k1 = iGrid; k1 < iGrid+3; k1++)
		{
			for(k2 = jGrid; k2 < jGrid+3; k2++)
			{
				if((k2 == j) && (k1 == i))
					continue;
				if(t == m_chess[k1][k2])
					return false;
			}
		}
		return true;
	}

	bool Sudoku()
	{
		int i,j, k;
		for(i = 0; i < 9; i++)
		{
			for(j = 0; j < 9; j++)
			{
				if(m_chess[i][j] == 0)
				{
					for(k = 1; k < 10; k++)
					{
						m_chess[i][j] = k;
						if(IsValid(i, j) && Sudoku())
						{
							if(!m_bSolve)
								memcpy(m_result, m_chess, sizeof(m_chess));
							m_bSolve = true;
							m_nCount++;
							//return true;
						}
						m_chess[i][j] = 0;
					}
					return false;
				}
			}
		}
		return true;	//说明所有位置都有值了
	}

	void Print(bool bChess)
	{
		int i,j;
		for(i = 0; i < 9; i++)
		{
			for(j = 0; j < 9; j++)
			{
				if(bChess)
					cout << m_chess[i][j] << "  ";
				else
					cout << m_result[i][j] << "  ";
			}
			cout << "\n";
		}
		cout << "\n\n";
	}

	int GetCount() const
	{
		return m_nCount;
	}
};


int _tmain(int argc, _TCHAR* argv[])
{
	int chess[9][9] = {
		{0, 4, 2, 0, 6, 3, 0, 0, 9},
		{6, 0, 0, 0, 1, 0, 0, 0, 5},
		{3, 0, 0, 0, 2, 0, 4, 8, 0},
		{1, 0, 0, 5, 0, 2, 6, 0, 8},
		{4, 0, 0, 0, 0, 7, 0, 0, 1},
		{9, 0, 5, 6, 0, 0, 0, 0, 7},
		{0, 3, 6, 0, 5, 0, 0, 0, 2},
		{2, 0, 0, 0, 7, 0, 0, 0, 4},
		{7, 0, 0, 2, 9, 0, 8, 5, 0},
	};
	//memset(chess, 0, sizeof(int)*81);
	CSudoku sudoku(chess);
	sudoku.Print(true);
	sudoku.Sudoku();
	sudoku.Print(false);
	cout << sudoku.GetCount() << endl;
	return 0;
}
