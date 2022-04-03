#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

void elso(){
    for(int i=0;i<8;i++)
    {
        sleep(1);
        printf("1. szal dolgozik\n");
    }
    return;
}

void masodik(void * arg){
    for(int i =0;i<4;i++)
    {
        sleep(1);
        printf("2. szal dolgozik\n");
    }
    return;
}

void harmadik(void * arg){
    
    sleep(1);
    printf("Uj szal inditva\n");

    return;
}

int main()
{
    pthread_t newthread;
    pthread_create(&newthread, NULL, masodik, NULL);
    elso();

    pthread_join(newthread, NULL);    
    
    pthread_t mythread;

    clock_t start_t, end_t;
    double total_t;
    start_t = clock();
    for (int i = 0; i < 60; i++)
    {        
        pthread_create(&mythread, NULL, harmadik, NULL);
    }   
        
    pthread_join(mythread, NULL);
    end_t = clock(); 
    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    printf("Total time taken by CPU: %f\n", total_t  );
    
    
    return 0;
}