// NumberOne.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
using namespace std;

int HammingWeight(unsigned int n)
{
	n = (n & 0x55555555) + ((n & 0xaaaaaaaa)>>1);
	n = (n & 0x33333333) + ((n & 0xcccccccc)>>2);
	n = (n & 0x0f0f0f0f) + ((n & 0xf0f0f0f0)>>4);
	n = (n & 0x00ff00ff) + ((n & 0xff00ff00)>>8);
	n = (n & 0x0000ffff) + ((n & 0xffff0000)>>16);
	return n;
}
int OneNumber(int n)
{ 
	int c = 0;
	while(n != 0)
	{
		c += (n&1);	//奇数则累加1
		n >>= 1;
	}
	return c;
}

int OneNumber2(int n)
{ 
	int c = 0;
	while(n != 0)
	{
		n &= (n-1);	//最低为1的位清0
		c++;
	}
	return c;
}
int _tmain(int argc, _TCHAR* argv[])
{
	for(int i = 0; i < 100; i++)
	{
		cout << i << ":\t" << HammingWeight(i) << endl;
		cout << i << ":\t" << OneNumber(i) << endl;
		cout << i << ":\t" << OneNumber2(i) << endl;
	}
	return 0;
}