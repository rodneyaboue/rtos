#include <stdio.h>
#include "rtos.h"
#include <unistd.h>

void task1() {
    static int counter = 0;
    printf("Task 1 running %d\n", counter++);
}

void task2() {
    static int counter = 0;
    printf("Task 2 running %d\n", counter++);
}

int main() {
    create_task(task1, 1);
    create_task(task2, 1);

    while(1) {
        scheduler();       
        usleep(500000); 
    }
    return 0;
}