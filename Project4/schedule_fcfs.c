#include <stdio.h>
#include <stdlib.h>
#include "schedulers.h"
#include "cpu.h"


void add(char *name, int priority, int burst, struct node **head){
    Task *t_new = (Task*)malloc(sizeof(Task*));
    t_new->name = name;
    t_new->priority = priority;
    t_new->burst = burst;
    insert(head, t_new);
}

    
void schedule(struct node **head){

    struct node *current_node, *front_node, *back_node;
    current_node = *head;
    front_node = NULL;

    while(current_node!=NULL && current_node->next!=NULL)
    {
        back_node = current_node->next;
        current_node->next = front_node;       
        front_node = current_node;
        current_node = back_node;     
    }
    if(current_node!=NULL && current_node->next==NULL)
        current_node->next = front_node;
    *head = current_node;

    Task *new_task;
    while(current_node!=NULL)
    {
        new_task = current_node->task;
        run(new_task, new_task->burst);
        current_node = current_node->next;
    }
}
