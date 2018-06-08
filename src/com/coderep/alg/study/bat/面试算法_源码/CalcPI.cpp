#include <iostream>
#include <math.h>
using namespace std;
#define PI 3.1415926535897932384626433832795

double Rand(double n)
{
	return ((double)rand() * n) / (double)(RAND_MAX);
}

double Boffon(double a, double L)	//横线之间的距离, 针长度
{
	double y;		//到最近的横线的距离 
	double theta;	//针的倾角 
	int c = 0;		//相交次数 
	int n = 1000000;	//实验次数 
	for(int i = 0; i < n; i++)
	{
		y = Rand(a/2);
		theta = Rand(PI);
		if(y < L*sin(theta)/2)	//相交 
			c++;
	}
	return 2 * (double)(n * L) / (double)(c * a);
}

int main(char* args, int s)
{
	double a = 30;
	double L = 10;
	cout << Boffon(a, L);
/*	for(a = L; a < 10*L; a++)
	{
		double p = Boffon(a, L);
		cout << a << ":\t" << p << " \t " << fabs(p - PI) << endl;
	}*/
	return 0;
}