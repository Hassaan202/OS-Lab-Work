#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>


void* printMessage(void* message){
    char* mess=(char*) message;
    printf("%s\n", mess);
    //terminates the thread with paramter being the return status
    pthread_exit(0);
}


int main(){
    pthread_t tid1, tid2;
    int iret1, iret2;
    pthread_attr_t attr1, attr2;
    char mess1[]="This is first thread.";
    char mess2[]="This is second thread.";
    //initialize threads with deafults attribs(stack, scheduling etc.)
    pthread_attr_init(&attr1);
    pthread_attr_init(&attr2);
    //create the threads (can pass NULL as attribute to set the default attributes)
    //can also typecast ecplicitly parameters to void* but automatically done also
    pthread_create(&tid1, &attr1, printMessage, mess1);
    pthread_create(&tid2, &attr2, printMessage, (void*)mess2);
    //parent thread waits for the child thread to terminate to continue execution
    //as this is synchronous threading so parent and child don't execute concurrently
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    //will print 0 value for both threads indicating success
    printf("Thread 1: %d\n", iret1);
    printf("Thread 2: %d\n", iret2);

    return 0;
}