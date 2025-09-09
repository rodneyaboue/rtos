#include <stdio.h>
#include "rtos.h"

int main() {
    printf("Combien de taches voulez-vous simuler (max %d) ? ", MAX_TASKS);
    scanf("%d", &num_tasks);
    if(num_tasks < 1 || num_tasks > MAX_TASKS) return 1;

    for(int i = 0; i < num_tasks; i++) {
        tasks[i].id = i+1;
        printf("Tache %d - duree: ", i+1);
        scanf("%d", &tasks[i].duree);
        printf("Tache %d - priorite: ", i+1);
        scanf("%d", &tasks[i].priorite);
        tasks[i].tempsAttente = 0;
        tasks[i].tempsRetour = 0;
    }

    int choix, quantum;
    printf("Choisissez l'ordonnancement:\n1.FCFS\n2.SJF\n3.Priority\n4.Round Robin\n5.SJF Preemptif\n6.Priority Preemptif\nVotre choix: ");
    scanf("%d", &choix);

    switch(choix) {
        case 1: schedulerFCFS(); break;
        case 2: schedulerSJF(); break;
        case 3: schedulerPriority(); break;
        case 4: 
            printf("Entrez le quantum pour Round Robin: ");
            scanf("%d", &quantum);
            schedulerRR(quantum); 
            break;
        case 5: schedulerSJFPreemptif(); break;
        case 6: schedulerPriorityPreemptif(); break;
        default: return 1;
    }

    displayDashboard();
    return 0;
}
