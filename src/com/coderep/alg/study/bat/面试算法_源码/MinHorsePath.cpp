// MinHorsePath.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <vector>
using namespace std;

class CMinHorsePath
{
private:
	int m_nRow;
	int m_nCol;
	int m_iStartRow;
	int m_iStartCol;
	int m_iEndRow;
	int m_iEndCol;

public:
	CMinHorsePath(int row, int col, int sRow, int sCol, int eRow, int eCol)
	{
		m_nRow = row;
		m_nCol = col;
		m_iStartRow = sRow;
		m_iStartCol = sCol;
		m_iEndRow = eRow;
		m_iEndCol = eCol;
	}

	void MinPath()
	{
		vector<vector<int> > chess(m_nRow, vector<int>(m_nCol));
		chess[m_iStartRow][m_iStartCol] = 1;
		Jump(m_iStartRow, m_iStartCol);
	}

private:
	void Jump(int i, int j, int step)
	{
		int iHorse[] = {};
	}
};

int _tmain(int argc, _TCHAR* argv[])
{
	CMinHorsePath mhp(9,8,0,0,4,6);
	mhp.MinPath();
	return 0;
}

