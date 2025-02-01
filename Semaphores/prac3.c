#include <stdio.h>
#include <pthread.h>

/*
Bridge Crossing Problem:
Model a scenario where there is a narrow bridge that can only accommodate a limited number of vehicles at a time. Vehicles approach the bridge from both sides and need to cross it. However, only one of vehicles can be on the bridge. Use binary semaphores to control access to the bridge and ensure that vehicles can cross it safely without collisions.
*/


typedef struct {
    int value;
} semaphore;


void semaphore_init(semaphore* sem, int initial_value) {
    sem->value = initial_value;
}


void semaphore_wait(semaphore* sem) {
    
    while (sem->value <= 0);
    sem->value--;
}


void semaphore_signal(semaphore* sem) {
    sem->value++;
}


int main(){


    return 0;
}
