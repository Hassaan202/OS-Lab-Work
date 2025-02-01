#include <stdio.h>
#include <pthread.h>

typedef struct {
    int count;
    int value;
} semaphore;

void semaphore_init(semaphore* sem, int initial_value) {
    sem->value = initial_value;
    sem->count = 5;
}

void semaphore_wait(semaphore* sem) {
    
    while (sem->value <= 0);
    sem->value--;
}

void semaphore_signal(semaphore* sem) {
    sem->value++;
}

void* thread_function(void* arg) {
    semaphore* sem = (semaphore*)arg;

    printf("Child Thread waiting for semaphore\n");
    semaphore_wait(sem);

    printf("Child Thread acquired the semaphore\n");
    
    // critical section 
    
    sem->count --;

    printf("Child Thread releasing the semaphore\n");
    semaphore_signal(sem);

    return NULL;
}

int main() {
    semaphore sem;
    semaphore_init(&sem, 1); // Initialize the semaphore with 1
    
    pthread_t thread;
    pthread_create(&thread, NULL, thread_function, (void*)&sem);


    printf("Main thread waiting for semaphore\n");
    semaphore_wait(&sem);

    printf("Main thread acquired the semaphore\n");
    
    //critical section
    sem.count ++;

    printf("Main thread releasing the semaphore\n");
    semaphore_signal(&sem);

    pthread_join(thread, NULL);
    
    printf("\nCount = %d", sem.count);
    return 0;
}