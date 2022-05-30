#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <omp.h>

#define THREADS 10
#define MAX_PRIME 1000

void is_prime(int n)
{
	int i;
	bool okay;
	
	okay=true;
	
	if (n<=1){
		printf("%d is not a prime\n", n);
		return;
	}
	#pragma omp parallel for
	for (i=2;i<=n-1;i++){
		if(n%i==0){
			okay=false;
		}
	}
	if(okay==false){
		printf("%d is not a prime\n", n);
		return;
	}
	printf("%d is a prime\n", n);
	return;
}

int main(int argc, char *argv[])
{
	clock_t start, end;
	double cpu_time_used;
	int i;
	
	start = clock();
	omp_set_num_threads(THREADS);
	
	#pragma omp parallel for
	for(i=0;i<MAX_PRIME;i++){
		is_prime(i);
	}

	end = clock();
	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

	printf("\n\n\n\n\nNumber of primes: %d\t\t\tTime: %lf\n",MAX_PRIME,cpu_time_used);
	return 0;
}