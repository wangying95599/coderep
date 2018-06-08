// NormalX.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <math.h>
#include <fstream>
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	double X1 = 2;
	double X2 = 2;
	double z;
	ofstream oFile;
	oFile.open("D:\\123.pt");
	for(double x1 = -X1; x1 <= X1; x1 += 0.01)
	{
		for(double x2 = -X2; x2 <= X2; x2 += 0.01)
		{
			z = fabs(x1*x1) + fabs(x2*x2);
			if(z > 2)
				continue;
			oFile << x1 << '\t' << x2 << '\t' << z << '\n';
		}
	}
	oFile.close();
	return 0;
}

