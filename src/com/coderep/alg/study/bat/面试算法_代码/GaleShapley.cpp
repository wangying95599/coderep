// GaleShapley.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 4;
void GaleShapley(const int (&man)[N][N], const int (&woman)[N][N], int (&match)[N])
{
	int wm[N][N];		//wm[i][j]��Ů��i���к�j������
	int choose[N];		//choose[i]��Ů��i��ǰ��������
	int manIndex[N];	//manIndex[i]���к�i�����ٸ�Ů���ܾ���
	int i,j;
	int w,m;
	for(i = 0; i < N; i++)
	{
		match[i] = -1;		//�����к�����ʼ��Ϊ���
		choose[i] = -1;		//����Ů������ʼ��Ϊ���
		manIndex[i] = 0;	//Ϊ0������ζ�Ŵ���ϲ����Ů����ʼѡ
		for(j = 0; j < N; j++)
			wm[i][woman[i][j]] = j;	//���к�woman[i][j]�������ǵ�jλ
	}

	bool bSingle = false;	//�Ƿ������к�������Ů��
	while(!bSingle)			//ÿ���к���ǰ��ѡŮ��
	{
		bSingle = true;		//��δ���ֵ����к�
		for(i = 0; i < N; i++)	//ÿ���к�iѡ����δ���ܾ�����ϲ����Ů��
		{
			if(match[i] != -1)	//�к�i�Ѿ���Ů��
				continue;
			bSingle = false;
			j = manIndex[i]++;
			w = man[i][j];		//�к�i��jϲ����Ů��w
			m = choose[w];		//Ů��w��ǰ������m
			if((m == -1) || (wm[w][i] < wm[w][m]))	//Ů��w��ϲ���к�i
			{
				match[i] = w;
				choose[w] = i;
				if(m != -1)
					match[m] = -1;	//Ů��w����ǰ����m
			}
		}
	}
}
void GaleShapley2(const int (&man)[N][N], const int (&woman)[N][N], int (&match)[N])
{
	int girl[N][N];		//girl[i][j]��Ů��i���к�j������
	int boy[N][N];		//boy[i][j]���к�i��Ů��j������
	int choose[N];		//choose[i]��Ů��i��ǰ��������
	int manIndex[N];	//manIndex[i]���к�i�����ٸ�Ů���ܾ���
	int womanIndex[N];	//manIndex[i]���к�i�����ٸ�Ů���ܾ���
	bool manPersuit[N];	//manIndex[i]���к�i��Ů���Ƿ����Լ�ѡ��
	bool womanPersuit[N];	//womanPersuit[i]��Ů��i���к��Ƿ����Լ�ѡ��
	int i,j;
	int w,m;
	for(i = 0; i < N; i++)
	{
		match[i] = -1;		//�����к�����ʼ��Ϊ���
		choose[i] = -1;		//����Ů������ʼ��Ϊ���
		manIndex[i] = 0;	//Ϊ0������ζ�Ŵ���ϲ����Ů����ʼѡ
		womanIndex[i] = 0;	//Ϊ0������ζ�Ŵ���ϲ�����к���ʼѡ
		manPersuit[i] = false;
		womanPersuit[i] = false;
		for(j = 0; j < N; j++)
		{
			girl[i][woman[i][j]] = j;	//���к�woman[i][j]�������ǵ�jλ
			boy[i][man[i][j]] = j;		//��Ů��man[i][j]�������ǵ�jλ
		}
	}

	bool bSingle = false;	//�Ƿ������к�������Ů��
	while(!bSingle)			//ÿ���к���ǰ��ѡŮ��
	{
		for(i = 0; i < N; i++)	//ÿ���к�iѡ����δ���ܾ�����ϲ����Ů��
		{
			if((match[i] != -1) && manPersuit[i])	//�к�i�Ѿ����Լ�׷����Ů��
				continue;
			j = manIndex[i]++;
			j %= N;
			w = man[i][j];		//�к�i��jϲ����Ů��w
			m = choose[w];		//Ů��w��ǰ������m
			if((m == -1) || (girl[w][i] < girl[w][m]))	//Ů��w��ϲ���к�i
			{
				if(match[i] != -1)
				{
					choose[match[i]] = -1;	//Ů��match[i]ʧ��
					womanPersuit[match[i]] = false;
				}
				if(m != -1)
				{
					match[m] = -1;		//�к�mʧ��
					manPersuit[m] = false;
				}
				match[i] = w;
				choose[w] = i;
				manPersuit[i] = true;	//�к�i׷����Ů��
			}
		}

		for(j = 0; j < N; j++)	//ÿ��Ů��jѡ����δ���ܾ�����ϲ�����к�
		{
			if((choose[j] != -1) && womanPersuit[j])	//Ů��j�Ѿ������Լ�ѡ�������
				continue;
			i = womanIndex[j]++;
			i %= N;
			m = woman[j][i];	//Ů��j��iϲ�����к�m
			w = match[m];		//�к�m��ǰ��Ů��w
			if((w == -1) || (boy[m][j] < boy[m][w]))	//�к�m��ϲ��Ů��j
			{
				if(choose[j] != -1)
				{
					match[choose[j]] = -1;	//�к�choose[j]ʧ��
					manPersuit[choose[j]] = false;
				}
				if(w != -1)
				{
					choose[w] = -1;	//Ů��wʧ��
					womanPersuit[w] = false;
				}
				choose[j] = m;
				match[m] = j;
				womanPersuit[j] = true;	//Ů��jѡ���к�
			}
		}

		bSingle = true;
		for(i = 0; i < N; i++)
		{
			if(match[i] == -1)
			{
				bSingle = false;
				break;
			}
		}
	}
}

bool PersuitPhoenix(int (&man)[N][N], int (&woman)[N][N], int (&match)[N], int (&choose)[N], int type)
{
	int wm[N][N];	//wm[i][j]��Ů��i���к�j������
	int i,j;
	for(i = 0; i < N; i++)
	{
		for(j = 0; j < N; j++)
		{
			wm[i][woman[i][j]] = j;	//���к�woman[i][j]�������ǵ�jλ
		}
	}

	bool bMatch = true;
	int w;
	for(i = 0; i < N; i++)
	{
		for(j = 0; j < N; j++)	//�����к�i������ȴӸߵ��ͱ���
		{
			w = man[i][j];	//���������Ů��match[i]���к�i��ϲ��Ů��w
			if(w == match[i])	//�����Լ�Ů�ѣ�������
				break;
			if(wm[w][choose[w]] > wm[w][i])	//Ů��wҲ��ϲ���к�i
			{
				bMatch = false;
				if(type == 1)
					cout << "�к�" << i << " - Ů��" << w << " ˽��\n";	//�к�i��Ů��w�ض�˽��
				else
					cout << "Ů��" << i << " - �к�" << w << " ˽��\n";	//�к�i��Ů��w�ض�˽��
				break;
			}
		}
	}
	return bMatch;
}

bool Validate(int (&man)[N][N], int (&woman)[N][N], int (&match)[N])
{
	int choose[N];	//choose[j]��Ů��j������
	int i;
	for(i = 0; i < N; i++)
		choose[i] = -1;
	for(i = 0; i < N; i++)
	{
		if(match[i] == -1)
		{
			cout << "�к�" << i << "���" << endl;
			return false;
		}
		if(choose[match[i]] != -1)
		{
			cout << "Ů��" << match[i] << "���к�" << choose[match[i]] << "���к�" << i << endl;
			return false;
		}
		choose[match[i]] = i;	//�к�iѡ����Ů��match[i]
	}

	bool b = PersuitPhoenix(man, woman, match, choose, 1);	//����ˣ����ÿ���к��Ƿ��и����ʵ�Ů��
	if(b)
		return PersuitPhoenix(woman, man, choose, match, 2);	//������ã����Ů�����ȶ���
	return false;
}

void Print(int* a, int size)
{
	for(int i = 0; i < size; i++)
		cout << a[i] << "  ";
	cout << "\n";
}

void Print2(int (&m)[N][N])
{
	for(int i = 0; i < N; i++)
	{
		cout << i << "��";
		Print(m[i], N);
	}
	cout << "==============\n";
}

void Init(int (&man)[N][N], int (&woman)[N][N])
{
	int i;
	int temp[N];
	for(i = 0; i < N; i++)
		temp[i] = i;
	Print(temp, N);

	for(i = 0; i < N; i++)
	{
		random_shuffle(temp, temp+N);
		memcpy(man[i], temp, sizeof(int)*N);

		random_shuffle(temp, temp+N);
		memcpy(woman[i], temp, sizeof(int)*N);
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	int man[N][N] = {
		{2,3,1,0},
		{2,1,3,0},
		{0,2,3,1},
		{1,3,2,0},
	};	//�к�ϲ����Ů���б�
	int woman[N][N] = {
		{0,3,2,1},
		{0,1,2,3},
		{0,2,3,1},
		{1,0,3,2},
	};	//Ů��ϲ�����к��б�
	int match[N];	//�к���Ů��
	GaleShapley(man, woman, match);
	Print(match, N);
	Validate(man, woman, match);
	return 0;
}