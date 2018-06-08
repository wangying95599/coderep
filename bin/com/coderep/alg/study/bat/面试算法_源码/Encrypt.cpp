#include "stdafx.h"
#include <iostream>
#include <fstream>
using namespace std;

void Encrypt()
{
	FILE* pFile = fopen("D:\\Algorithm\\MySong.txt", "rb");
	fseek(pFile, 0, SEEK_END);
	int nFileLen = ftell(pFile);
	fseek(pFile, 0, SEEK_SET);
	char* str = new char[nFileLen+1];
	fread(str, nFileLen, 1, pFile);
	fclose(pFile);
	str[nFileLen] = 0;
	char* secret = "JulyEdu";
	int nLen = (int)strlen(secret);
	int j = 0;
	for(int i = 0; i < nFileLen; i++)
	{
		str[i] ^= secret[j];
		j++;
		if(j >= nLen)
			j -= nLen;
	}

	FILE* pFile2 = fopen("D:\\Algorithm\\MySong3.txt", "wb");
	fwrite(str, nFileLen, 1, pFile2);
	fclose(pFile2);

	delete[] str;
}
int _tmain(int argc, _TCHAR* argv[])
{
	Encrypt();
	/*ifstream iFile("D:\\Algorithm\\MySong.txt");
	iFile.seekg(0, ios::end);
	int nFileLen = iFile.tellg();
	iFile.seekg(0, ios::beg);
	char* str = new char[nFileLen+1];
	iFile.read(str, nFileLen);
	iFile.close();
	str[nFileLen] = 0;
	int nCaesar = 3;
	int n = 0;	//记录回车的数目
	for(int i = 0; i < nFileLen; i++)
	{
		if((str[i] >= 'a') && (str[i] <= 'z'))
		{
			str[i] += nCaesar;
			if(str[i] > 'z')
				str[i] -= 26;
		}
		else if((str[i] >= 'A') && (str[i] <= 'Z'))
		{
			str[i] += nCaesar;
			if(str[i] > 'Z')
				str[i] -= 26;
		}
		else if(str[i] == '\n')
		{
			n++;
		}
	}

	ofstream oFile("D:\\Algorithm\\MySong2.txt");
	oFile.write(str, nFileLen - n);
	oFile.close();

	delete[] str;*/
	return 0;
}