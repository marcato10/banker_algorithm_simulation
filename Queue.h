#include <unistd.h>
#include "Process.h"

typedef struct Node{
    Process process;
    struct Node* next;
}Node;

typedef struct Queue{
    int size;
    Node* head;
}Queue;

void queue(Queue* queue,Process* process){
    Node* new_node = (Node*) malloc(sizeof(Node));
    new_node->process = *process;
    new_node->next = NULL;

    if(queue->head == NULL){
        queue->head = new_node;
        queue->size = queue->size++;
        return;
    }

    Node* iterator = queue->head;
    while(iterator->next != NULL){
        iterator = iterator->next;
    }
    iterator->next = new_node;
    queue->size = queue->size++;
}

void pop(Queue* queue){
    if(queue->head == 0){
        printf("\nQueue is empty");
        return;
    }
    if(queue->head->next == NULL){
        queue->head = NULL;
        queue->size = queue->size-1;
        return;
    }
    Node* aux = queue->head;
    queue->head = queue->head->next;

    queue->size = queue->size-1;
}
void printResource(int*array,int size){
    printf("\n");
    for(int i = 0; i < size;i++){
        printf("%d ",array[i]);
    }
}

void queueExecute(Queue *queue,int* avaliable_resource,int column){
    printf("\nPID da ordem de execução: \n");

    while(queue->head != NULL){
        for(int i = 0; i < column;i++){

            queue->head->process.process_status = EXECUTING;

            //Faz os recursos
            avaliable_resource[i] = avaliable_resource[i] - queue->head->process.resources_required[i];
            queue->head->process.process_status = FINISHED;
            avaliable_resource[i] = avaliable_resource[i] + queue->head->process.resources_required[i];

        }
        printf("(%d) ",queue->head->process.PID);
        pop(queue);
    }
    printf("\nTodas as tarefas foram finalizadas");

}


