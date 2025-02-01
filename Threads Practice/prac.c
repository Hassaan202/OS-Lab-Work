#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>

void* modifyVal(void* a){
    int* val=(int*)a;
    (*val)+=5;
    pthread_exit(0);
}

int main(){
    //testing if local variables gets updated or not
    int var=10;
    printf("Original value: %d\n", var);
    pthread_t tid;
    pthread_create(&tid, NULL, modifyVal, (void*)&var);
    pthread_join(tid, NULL);
    printf("Updated value: %d\n", var);

    return 0;
}