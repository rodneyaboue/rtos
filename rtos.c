#include "rtos.h"
#include <stdio.h>

#include <signal.h>
#include <sys/time.h>

jmp_buf context[MAX_TASKS];   
task_t tasks[MAX_TASKS];      
int current_task = 0;         
int num_tasks = 0;            
int create_task(void (*func)(void), int priority) {
    if(num_tasks >= MAX_TASKS) 
    {
        return 1;
    };
    tasks[num_tasks].id = num_tasks;
    tasks[num_tasks].priority = priority;
    tasks[num_tasks].state = READY;
    tasks[num_tasks].task_func = func;
    num_tasks++;
    return 0;
}

void scheduler() {
    for(int i=0; i<num_tasks; i++) {
        if(tasks[i].state == READY) {
            tasks[i].state = RUNNING; 
            display_dashboard();
            tasks[i].task_func();
            tasks[i].state = READY;
        }
    }
}


void display_dashboard() {
    printf("\n--- RTOS Dashboard ---\n");
    for(int i=0; i<num_tasks; i++) {
        char *state_str;
        switch(tasks[i].state) {
            case READY: state_str = "READY"; break;
            case RUNNING: state_str = "RUNNING"; break;
            case BLOCKED: state_str = "BLOCKED"; break;
        }
        printf("Task %d | Priority: %d | State: %s\n",
                tasks[i].id,
                tasks[i].priority,
                state_str);
    }
    printf("---------------------\n");
}