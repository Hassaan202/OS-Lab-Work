#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>

struct sumStore{
    int arg1, arg2, sum;
};

void* modifySum(void* param){
    struct sumStore* a1=(struct sumStore*)param;
    printf("%d\n", a1->arg1);
    printf("%d\n", a1->arg2);
    a1->sum=a1->arg1+a1->arg2;
    pthread_exit(0);
}

int main(){
    struct sumStore var1={3,4,0};
    pthread_t tid;
    int iret=pthread_create(&tid, NULL, modifySum, (void*)&var1);
    pthread_join(tid, NULL);
    //the paramter is passed by reference i.e. pointer to original data so it gets modified in the parent too
    printf("Sum is %d\n", var1.sum);

    return 0;
}