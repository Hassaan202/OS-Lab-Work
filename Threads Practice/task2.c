#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>


void* printData(void* arr){
    int* a=(int*)arr;
    for (int i=0;i<5;i++){
        printf("%d ", a[i]);
    }
    printf("\n");
    pthread_exit(0);
}

int main(){
    int arr[20]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
    int data1[5], data2[5], data3[5], data4[5];
    for (int i=0;i<5;i++){
        data1[i]=arr[i];
        data2[i]=arr[i+5];
        data3[i]=arr[i+10];
        data4[i]=arr[i+15];
    }
    pthread_t t1,t2,t3,t4;
    int iret1, iret2, iret3, iret4;
    iret1=pthread_create(&t1, NULL, printData, (void*)data1);
    iret2=pthread_create(&t2, NULL, printData, (void*)data2);
    iret3=pthread_create(&t3, NULL, printData, (void*)data3);
    iret4=pthread_create(&t4, NULL, printData, (void*)data4);
    
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    pthread_join(t4, NULL);

    printf("Thread 1: %d\n", iret1);
    printf("Thread 2: %d\n", iret2);
    printf("Thread 3: %d\n", iret3);
    printf("Thread 4: %d\n", iret4);

    return 0;
}