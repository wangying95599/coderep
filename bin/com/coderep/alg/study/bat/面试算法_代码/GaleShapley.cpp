// GaleShapley.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 4;
void GaleShapley(const int (&man)[N][N], const int (&woman)[N][N], int (&match)[N])
{
	int wm[N][N];		//wm[i][j]：女孩i对男孩j的排名
	int choose[N];		//choose[i]：女孩i当前的男朋友
	int manIndex[N];	//manIndex[i]：男孩i被多少个女孩拒绝过
	int i,j;
	int w,m;
	for(i = 0; i < N; i++)
	{
		match[i] = -1;		//所有男孩都初始化为光棍
		choose[i] = -1;		//所有女孩都初始化为光棍
		manIndex[i] = 0;	//为0，则意味着从最喜欢的女孩开始选
		for(j = 0; j < N; j++)
			wm[i][woman[i][j]] = j;	//对男孩woman[i][j]的排名是第j位
	}

	bool bSingle = false;	//是否所有男孩都有了女友
	while(!bSingle)			//每个男孩当前轮选女友
	{
		bSingle = true;		//尚未发现单身男孩
		for(i = 0; i < N; i++)	//每个男孩i选择尚未被拒绝的最喜欢的女孩
		{
			if(match[i] != -1)	//男孩i已经有女友
				continue;
			bSingle = false;
			j = manIndex[i]++;
			w = man[i][j];		//男孩i第j喜欢的女孩w
			m = choose[w];		//女孩w当前的男友m
			if((m == -1) || (wm[w][i] < wm[w][m]))	//女孩w更喜欢男孩i
			{
				match[i] = w;
				choose[w] = i;
				if(m != -1)
					match[m] = -1;	//女孩w抛弃前男友m
			}
		}
	}
}
void GaleShapley2(const int (&man)[N][N], const int (&woman)[N][N], int (&match)[N])
{
	int girl[N][N];		//girl[i][j]：女孩i对男孩j的排名
	int boy[N][N];		//boy[i][j]：男孩i对女孩j的排名
	int choose[N];		//choose[i]：女孩i当前的男朋友
	int manIndex[N];	//manIndex[i]：男孩i被多少个女孩拒绝过
	int womanIndex[N];	//manIndex[i]：男孩i被多少个女孩拒绝过
	bool manPersuit[N];	//manIndex[i]：男孩i的女孩是否是自己选的
	bool womanPersuit[N];	//womanPersuit[i]：女孩i的男孩是否是自己选的
	int i,j;
	int w,m;
	for(i = 0; i < N; i++)
	{
		match[i] = -1;		//所有男孩都初始化为光棍
		choose[i] = -1;		//所有女孩都初始化为光棍
		manIndex[i] = 0;	//为0，则意味着从最喜欢的女孩开始选
		womanIndex[i] = 0;	//为0，则意味着从最喜欢的男孩开始选
		manPersuit[i] = false;
		womanPersuit[i] = false;
		for(j = 0; j < N; j++)
		{
			girl[i][woman[i][j]] = j;	//对男孩woman[i][j]的排名是第j位
			boy[i][man[i][j]] = j;		//对女孩man[i][j]的排名是第j位
		}
	}

	bool bSingle = false;	//是否所有男孩都有了女友
	while(!bSingle)			//每个男孩当前轮选女友
	{
		for(i = 0; i < N; i++)	//每个男孩i选择尚未被拒绝的最喜欢的女孩
		{
			if((match[i] != -1) && manPersuit[i])	//男孩i已经有自己追到的女友
				continue;
			j = manIndex[i]++;
			j %= N;
			w = man[i][j];		//男孩i第j喜欢的女孩w
			m = choose[w];		//女孩w当前的男友m
			if((m == -1) || (girl[w][i] < girl[w][m]))	//女孩w更喜欢男孩i
			{
				if(match[i] != -1)
				{
					choose[match[i]] = -1;	//女孩match[i]失恋
					womanPersuit[match[i]] = false;
				}
				if(m != -1)
				{
					match[m] = -1;		//男孩m失恋
					manPersuit[m] = false;
				}
				match[i] = w;
				choose[w] = i;
				manPersuit[i] = true;	//男孩i追到了女孩
			}
		}

		for(j = 0; j < N; j++)	//每个女孩j选择尚未被拒绝的最喜欢的男孩
		{
			if((choose[j] != -1) && womanPersuit[j])	//女孩j已经有了自己选择的男友
				continue;
			i = womanIndex[j]++;
			i %= N;
			m = woman[j][i];	//女孩j第i喜欢的男孩m
			w = match[m];		//男孩m当前的女友w
			if((w == -1) || (boy[m][j] < boy[m][w]))	//男孩m更喜欢女孩j
			{
				if(choose[j] != -1)
				{
					match[choose[j]] = -1;	//男孩choose[j]失恋
					manPersuit[choose[j]] = false;
				}
				if(w != -1)
				{
					choose[w] = -1;	//女孩w失恋
					womanPersuit[w] = false;
				}
				choose[j] = m;
				match[m] = j;
				womanPersuit[j] = true;	//女孩j选到男孩
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
	int wm[N][N];	//wm[i][j]：女孩i对男孩j的排名
	int i,j;
	for(i = 0; i < N; i++)
	{
		for(j = 0; j < N; j++)
		{
			wm[i][woman[i][j]] = j;	//对男孩woman[i][j]的排名是第j位
		}
	}

	bool bMatch = true;
	int w;
	for(i = 0; i < N; i++)
	{
		for(j = 0; j < N; j++)	//按照男孩i的钟情度从高到低遍历
		{
			w = man[i][j];	//相对于现任女友match[i]，男孩i更喜欢女孩w
			if(w == match[i])	//遇到自己女友，快闪！
				break;
			if(wm[w][choose[w]] > wm[w][i])	//女孩w也更喜欢男孩i
			{
				bMatch = false;
				if(type == 1)
					cout << "男孩" << i << " - 女孩" << w << " 私奔\n";	//男孩i和女孩w必定私奔
				else
					cout << "女孩" << i << " - 男孩" << w << " 私奔\n";	//男孩i和女孩w必定私奔
				break;
			}
		}
	}
	return bMatch;
}

bool Validate(int (&man)[N][N], int (&woman)[N][N], int (&match)[N])
{
	int choose[N];	//choose[j]：女孩j的男友
	int i;
	for(i = 0; i < N; i++)
		choose[i] = -1;
	for(i = 0; i < N; i++)
	{
		if(match[i] == -1)
		{
			cout << "男孩" << i << "光棍" << endl;
			return false;
		}
		if(choose[match[i]] != -1)
		{
			cout << "女孩" << match[i] << "：男孩" << choose[match[i]] << "和男孩" << i << endl;
			return false;
		}
		choose[match[i]] = i;	//男孩i选择了女孩match[i]
	}

	bool b = PersuitPhoenix(man, woman, match, choose, 1);	//凤求凰：检查每个男孩是否有更合适的女友
	if(b)
		return PersuitPhoenix(woman, man, choose, match, 2);	//反向调用：检查女孩的稳定性
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
		cout << i << "：";
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
	};	//男孩喜欢的女孩列表
	int woman[N][N] = {
		{0,3,2,1},
		{0,1,2,3},
		{0,2,3,1},
		{1,0,3,2},
	};	//女孩喜欢的男孩列表
	int match[N];	//男孩的女友
	GaleShapley(man, woman, match);
	Print(match, N);
	Validate(man, woman, match);
	return 0;
}