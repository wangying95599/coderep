// Entropy.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <math.h>
#include <fstream>
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	float x = 0.001f;
	float y;
	float log2 = log(2.0f);
	ofstream oFile;
	oFile.open(_T("D:\\entropy.txt"));
	while(x < 1)
	{
		y = x * log(x) / log2;
		oFile << x << '\t' << y << '\n';

		x += 0.001f;
	}
	oFile.close();
	return 0;
}

