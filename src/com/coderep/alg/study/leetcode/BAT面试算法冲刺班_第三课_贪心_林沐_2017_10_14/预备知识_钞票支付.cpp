#include <stdio.h>

int main(){
	const int RMB[] = {200, 100, 20, 10, 5, 1};
	const int NUM = 6;
	int X = 628;
	int count = 0;
	for (int i = 0; i < NUM; i++){
		int use = X / RMB[i];
		count += use;
		X = X - RMB[i] * use;
		printf("��Ҫ���Ϊ%d��%d��, ", RMB[i], use);
		printf("ʣ����Ҫ֧�����%d.\n", X);
	}
	printf("�ܹ���Ҫ%d��\n", count);
	return 0;
}

