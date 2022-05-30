#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>


#define MAX_LINES 100000
#define MAX_THREADS 10
#define FILENAME "test.txt"

pthread_mutex_t value_mutex = PTHREAD_MUTEX_INITIALIZER;

void* writetofile() {
    int lines;
    FILE *fp;
    clock_t start, end;
	double cpu_time_used;
	
    start = clock();
	lines=0;
    while(lines<MAX_LINES/MAX_THREADS) {
		pthread_mutex_lock(&value_mutex);
		fp=fopen(FILENAME, "a");
        fprintf(fp,"%d\n",lines);
        lines++;
		fclose(fp);
		pthread_mutex_unlock(&value_mutex);
    }
    end = clock();
    cpu_time_used = (double) (end - start) / CLOCKS_PER_SEC;
    printf("%f seconds\n", cpu_time_used);
}


int main() {
    clock_t start, end;
	double cpu_time_used;
	int i;
    pthread_t threads[MAX_THREADS];

    start = clock();
	
    for(i=0;i<MAX_THREADS;i++) {
        pthread_create(&threads[i], NULL, writetofile, NULL);
    }
	
    for(i=0;i<MAX_THREADS;i++){
		pthread_join(threads[i], NULL);
	}

    end = clock();
	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\nTotal time: %lf\n\n", cpu_time_used);
    return 0;
}