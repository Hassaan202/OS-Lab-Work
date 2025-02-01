#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>


void* sumAndStore(void* arr){
    int* a=(int*)arr;
    int n=a[0];
    int sum=0;
    for (int i=1;i<=n;i++){
        sum+=a[i];
    }
    a[n+1]=sum;
    pthread_exit(0);
}


int main(){
    int n;
    printf("Enter the size of the array: ");
    scanf("%d", &n);
    int* arr=(int*)calloc(n+2,sizeof(int));
    //0 index will store num of elements, last index will store the return value i.e sum, middle are elems
    arr[0]=n;
    for (int i=1;i<=n;i++){
        printf("%d: ", i-1);
        scanf("%d", &arr[i]);
    }
    pthread_t tid;
    pthread_create(&tid, NULL, sumAndStore, (void*)arr);
    pthread_join(tid, NULL);
    printf("The sum is %d.\n", arr[n+1]);

    return 0;
}