#include <stdio.h>
#include <pthread.h>


/*
Print the sequence:
Three processes are running in parallel sharing variables i and j, both intialized with 1. You have to sychronize them in a way that the output on the console is the fibonacci series. For example 1,1,2,3,5....
Note: use binary semaphore
(Similarly you can print different sequences that are dependent on each other)
*/


//equals i, j
int prev=1, curr=1, count=2;


typedef struct {
    int value;
    int maxRange;
}semaphore;


void semaphore_init(semaphore* sem, int initial_value, int max_val) {
    sem->value = initial_value;
    sem->maxRange=max_val;
}


void semaphore_wait(semaphore* sem) {   
    while (sem->value <= 0);
    sem->value--;
}


void semaphore_signal(semaphore* sem) {
    sem->value++;
}


void* printFibSeries(void* arg){
    semaphore s=*(semaphore*)arg;
    //we go upto maxRange-1 as the other process would be in its waiting state so will not be able to
    //check for the condition of the outer while loop
    while (count<=s.maxRange-1){
        semaphore_wait(&s); //entry
        int tmp=curr+prev;
        prev=curr;
        curr=tmp;
        printf("%d, ", curr);
        count++;
        semaphore_signal(&s); //exit
    }
    pthread_exit(NULL);
}


int main(){
    //number of digits in the series taken as an input
    int n;
    printf("Enter the number of digits to print in the Fibonacci series:\n");
    scanf("%d", &n);
    //create and init a semaphore
    semaphore s;
    semaphore_init(&s, 1, n); //binary semaphore has an initial value of one
    //print the series
    if (n==0){
        printf("No digit.\n");
    }
    else if (n==1){
        printf("1.\n");
    }
    else if (n==2){
        printf("1, 1.\n");
    }
    else{
        printf("1, 1, ");
        pthread_t thread;
        pthread_create(&thread, NULL, printFibSeries, (void*)&s);
        //main
        while (count<=s.maxRange-1){
            semaphore_wait(&s); //entry
            int tmp=curr+prev;
            prev=curr;
            curr=tmp;
            printf("%d, ", curr);
            count++;
            semaphore_signal(&s); //exit
        }
        pthread_join(thread, NULL);
        printf("\n");
    }
    printf("Exit...\n");

    return 0;
}
