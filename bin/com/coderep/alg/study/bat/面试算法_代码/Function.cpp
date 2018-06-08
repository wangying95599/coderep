// Function.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <math.h>
#include <fstream>
#include <iomanip>
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	double x,y;
	ofstream oFile;
	oFile.open("D:\\123.txt");
	oFile << setprecision(10);
	for(x = 0.52366782; x < 0.52366783; x += 0.0000000001)
	{
		y = 0.563+0.28*log10(sqrt(x)) - x;
		oFile << x << '\t' << y << '\n';
	}
	oFile.close();

	return 0;
}

