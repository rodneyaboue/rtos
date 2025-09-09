#if !defined(RTOS_H)
#define RTOS_H

#include <setjmp.h>
#define STACK_SIZE 1024
#define MAX_TASKS 5


typedef enum { READY, RUNNING, BLOCKED } task_state_t;

typedef struct {
    int id;
    int priority;
    task_state_t state;
    void (*task_func)(void);
    unsigned char stack[STACK_SIZE]; // simulation
} task_t;

extern task_t tasks[MAX_TASKS];
extern jmp_buf context[MAX_TASKS];
extern int current_task;
extern int num_tasks;
int create_task(void (*func)(void), int priority);
void scheduler();
void display_dashboard();

#endif // RTOS_H