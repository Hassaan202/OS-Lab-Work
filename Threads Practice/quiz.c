#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>
#include <sys/types.h>

int sum=5;

void* addSum(void* arg){
    (sum)+=5;
    pthread_exit(0);
}


void* mulSum(void* arg){
    (sum)*=5;
    pthread_exit(0);
}

int main(){
    int pid=fork();
    //as fork creates two different processes with different memory area therefore
    //both get seperate copies of gloabl variable sum. On the other hand, the global variables
    //in different threadfs are shared
    if (pid==0){
        pthread_t tid, tid1;
        pthread_create(&tid, NULL, addSum, NULL);
        pthread_create(&tid1, NULL, addSum, NULL);
        pthread_join(tid, NULL);
        pthread_join(tid1, NULL);
        sleep(1);
        printf("Sum in child is %d.\n", sum); //10
        exit(0);
    }
    else{
        pthread_t tid;
        pthread_create(&tid, NULL, mulSum, NULL);
        pthread_join(tid, NULL);
        printf("Sum in parent is %d.\n", sum); //25
        wait(NULL);
    }
    return 0;
}