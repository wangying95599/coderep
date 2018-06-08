
#include <stdio.h>

void compute_sum(int i,int &sum){
	if (i > 3){
		return;
	}
	sum += i;
	compute_sum(i + 1, sum);
}

int main(){
	int sum = 0;
	compute_sum(1, sum);
	printf("sum = %d\n", sum);
	return 0;
}

