// OddEven.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <algorithm>
using namespace std;

void OddEven(int* a, int N)
{
	int i;
	int odd = 0;
	int even = 0;
	for(i = 0; i < N; i++)
	{
		if(a[i] % 2 == 1)
			odd++;
		else
			even++;
	}
	int oddSize = 0;
	int evenSize = 0;
	while(true)
	{
		int oFront = 0;
		int oBack = odd-1;
		int eFront = odd;
		int eBack = N-1;
		while((oFront <= oBack) && (eFront <= eBack))
		{
			while((oFront <= oBack) && (a[oFront] % 2 == 1))
				oFront++;
			if(oFront > oBack)
				break;
			while((eFront <= eBack) && (a[eBack] % 2 == 0))
				eBack--;
			if(eFront > eBack)
				break;

			swap(a[oFront],a[eFront]);
			eFront++;
			oFront++;
			swap(a[eBack],a[oBack]);
			oBack--;
			eBack--;
			oddSize++;
			evenSize++;
		}
	}
}

void reform(int* array, int size)  
{  
    int i = 0, j = size - 1;  
  
    while(i <= j) {  
        while(i <= j) {  
            if(array[i] % 2 == 0)  
                break;  
            else  
                i++;  
        }  
  
        while(i <= j) {  
            if(array[j] % 2 != 0)  
                break;  
            else  
                j--;  
        }  
  
        //如果不在这里进行i++，j--就会出错  
        swap(array[i++], array[j--]);  
    }  
}

void Print(const int* a, int N)
{
	for(int i = 0; i < N; i++)
		cout << a[i] << "  ";
	cout << endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
	const int N = 10;
	int a[N];
	for(int i = 0; i < N; i++)
		a[i] = i+1;
	random_shuffle(a, a+N);
	Print(a, N);
	reform(a, N);
	Print(a, N);
	return 0;
}

