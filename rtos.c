#include "rtos.h"
#include <stdio.h>

task_t tasks[MAX_TASKS];
int num_tasks = 0;

// Affichage
void displayDashboard() {
    printf("\n--- Dashboard ---\n");
    printf("ID | Duree | Priorite | Attente | Retour\n");
    for(int i = 0; i < num_tasks; i++) {
        printf("%2d | %5d | %8d | %7d | %6d\n",
               tasks[i].id,
               tasks[i].duree,
               tasks[i].priorite,
               tasks[i].tempsAttente,
               tasks[i].tempsRetour);
    }
    printf("-----------------\n");
}

// FCFS simple
void schedulerFCFS() {
    int temps = 0;
    for(int i = 0; i < num_tasks; i++) {
        tasks[i].tempsAttente = temps;
        tasks[i].tempsRetour = temps + tasks[i].duree;
        temps += tasks[i].duree;
        tasks[i].state = FINISHED;
    }
}

// SJF non préemptif
void schedulerSJF() {
    for(int i = 0; i < num_tasks -1; i++) {
        for(int j = 0; j < num_tasks - i -1; j++) {
            if(tasks[j].duree > tasks[j+1].duree) {
                task_t temp = tasks[j];
                tasks[j] = tasks[j+1];
                tasks[j+1] = temp;
            }
        }
    }
    schedulerFCFS();
}

// Priority non préemptif
void schedulerPriority() {
    for(int i = 0; i < num_tasks -1; i++) {
        for(int j = 0; j < num_tasks - i -1; j++) {
            if(tasks[j].priorite > tasks[j+1].priorite) {
                task_t temp = tasks[j];
                tasks[j] = tasks[j+1];
                tasks[j+1] = temp;
            }
        }
    }
    schedulerFCFS();
}

// Round Robin
void schedulerRR(int quantum) {
    for(int i = 0; i < num_tasks; i++) tasks[i].reste = tasks[i].duree;
    int temps = 0, tacheFinie;
    do {
        tacheFinie = 0;
        for(int i = 0; i < num_tasks; i++) {
            if(tasks[i].reste > 0) {
                int exec = (tasks[i].reste > quantum) ? quantum : tasks[i].reste;
                tasks[i].tempsAttente += temps;
                temps += exec;
                tasks[i].reste -= exec;
                if(tasks[i].reste == 0) tasks[i].tempsRetour = temps;
                tacheFinie = 1;
            }
        }
    } while(tacheFinie);
}

// SJF préemptif (Shortest Remaining Time First)
void schedulerSJFPreemptif() {
    for(int i = 0; i < num_tasks; i++) tasks[i].reste = tasks[i].duree;
    int temps = 0, resteTaches = num_tasks;
    while(resteTaches > 0) {
        int idxMin = -1;
        for(int i = 0; i < num_tasks; i++) {
            if(tasks[i].reste > 0 && (idxMin == -1 || tasks[i].reste < tasks[idxMin].reste)) {
                idxMin = i;
            }
        }
        tasks[idxMin].reste--;
        temps++;
        for(int i = 0; i < num_tasks; i++) {
            if(i != idxMin && tasks[i].reste > 0) tasks[i].tempsAttente++;
        }
        if(tasks[idxMin].reste == 0) {
            tasks[idxMin].tempsRetour = temps;
            resteTaches--;
        }
    }
}

// Priority préemptif
void schedulerPriorityPreemptif() {
    for(int i = 0; i < num_tasks; i++) tasks[i].reste = tasks[i].duree;
    int temps = 0, resteTaches = num_tasks;
    while(resteTaches > 0) {
        int idxMin = -1;
        for(int i = 0; i < num_tasks; i++) {
            if(tasks[i].reste > 0 && (idxMin == -1 || tasks[i].priorite < tasks[idxMin].priorite)) {
                idxMin = i;
            }
        }
        tasks[idxMin].reste--;
        temps++;
        for(int i = 0; i < num_tasks; i++) {
            if(i != idxMin && tasks[i].reste > 0) tasks[i].tempsAttente++;
        }
        if(tasks[idxMin].reste == 0) {
            tasks[idxMin].tempsRetour = temps;
            resteTaches--;
        }
    }
}
