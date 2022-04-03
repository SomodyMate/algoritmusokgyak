#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <omp.h>

void elso(){
    double my_array[7];
    srand(0);
    for (int i = 0; i < 7; i++) {
    my_array[i] = rand();
    }
    double sum1 = 1;
    for (int i = 0; i < 7; i++)
    {
        sum1 *= my_array[i];
        //printf("%lf\n", my_array[i]);
    }
    printf("Szorzat: %lf\n", sum1);
    sum1=1;
    #pragma omp parallel for
    for(int i = 0; i < 7; ++i)
    {
        sum1 *= my_array[i];
    }

    printf("Szorzat: %lf\n", sum1);
    #pragma omp parallel for private(my_array) reduction(*:sum1)
    for (int i = 0; i < 7; i++)
    {    
        sum1 *= my_array[i];
    }
    printf("Szorzat: %lf\n", sum1);
}

int main()
{
    int n_threads;
    n_threads = omp_get_num_threads();
    printf("%d szal van.\n", n_threads);
    elso();
    
    return 0;
}