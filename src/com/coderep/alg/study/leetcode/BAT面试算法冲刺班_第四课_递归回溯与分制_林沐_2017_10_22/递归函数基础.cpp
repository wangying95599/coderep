
#include <stdio.h>
void compute_sum_3(int i, int &sum){
	sum += i;
}
void compute_sum_2(int i, int &sum){
	sum += i;
	compute_sum_3(i + 1, sum);
}
void compute_sum_1(int i, int &sum){
	sum += i;
	compute_sum_2(i + 1, sum);
}
int main(){
	int sum = 0;
	compute_sum_1(1, sum);
	printf("sum = %d\n", sum);
	return 0;
}

