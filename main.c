#include <stdio.h>
#include "rtos.h"
#include <unistd.h>

int tick_count = 0;
void task1() {
    static int counter = 0;
    printf("Task 1 running %d\n", counter++);
}

void task2() {
    static int counter = 0;
    printf("Task 2 running %d\n", counter++);
}

void task3() {
    static int counter = 0;
    printf("Task 3 running %d\n", counter++);
}

void task4() {
    static int counter = 0;
    printf("Task 4 running %d\n", counter++);
}

void task5() {
    static int counter = 0;
    printf("Task 5 running %d\n", counter++);
}

int main() {
    create_task(task1, 5, 2);
    create_task(task2, 4, 2);
    create_task(task3, 3, 3);
    create_task(task4, 2, 4);
    create_task(task5, 1, 5);

    
    while(1) {
        printf("\nTick: %d\n", tick_count);
        scheduler();       
        tick_count++;
        usleep(500000); 
    }
    return 0;
}