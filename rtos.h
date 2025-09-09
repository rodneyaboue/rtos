#ifndef RTOS_H
#define RTOS_H

#define MAX_TASKS 100

typedef enum { READY, RUNNING, FINISHED } task_state_t;

typedef struct {
    int id;
    int duree;          // Durée totale (Burst Time)
    int reste;          // Temps restant pour exécution
    int priorite;       // Priorité (plus petit = plus prioritaire)
    int tempsAttente;   // Temps d'attente
    int tempsRetour;    // Temps de retour
    task_state_t state; // État
} task_t;

extern task_t tasks[MAX_TASKS];
extern int num_tasks;

void schedulerFCFS();
void schedulerSJF();
void schedulerPriority();
void schedulerRR(int quantum);
void schedulerSJFPreemptif();
void schedulerPriorityPreemptif();
void displayDashboard();

#endif // RTOS_H