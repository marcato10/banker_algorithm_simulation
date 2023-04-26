#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Array.h"
#include "Queue.h"
#include <unistd.h>
#include <stdbool.h>

int main() {
    const int size = 4;
    srand(time(NULL));
    //Mude para 1 caso queira que os recursos disponíveis são aleatórios
    bool random = 0;

    //Recursos totais do sistema.
    Array total_resources;
    total_resources.size = 0;
    Reserve(&total_resources,size);
    if(random == 0){
        int initial[4] = {8,4,6,7};
        for(int i = 0;i < size;i++){
            total_resources.data[i] = initial[i];
        }
    }
    else{
        for(int i = 0; i < total_resources.size;i++){
            total_resources.data[i] = rand()%10;
        }
    }


    Array avaliable_resources;
    avaliable_resources.size = 0;


    Reserve(&avaliable_resources,size);



    for(int i = 0; i < size;i++){
        avaliable_resources.data[i] = total_resources.data[i];
    }

    printf("\nRecursos totais: ");
    printArray(&total_resources);

    printf("\nRecursos disponíveis: ");
    printArray(&avaliable_resources);

    //Definindo os processos que vão usar recursos
    //Quantidade de processos (com limite até o número 6)

    int number_process = 4;
    int column = size;

    //Cria um array de Processos
    Process* process_request = calloc(number_process, sizeof(Process));
    for(int i = 0; i < number_process;i++){
        process_request[i].PID = i+1;
        process_request[i].process_status = WAITING;
        int *request_line = calloc(column,sizeof(int));

        for(int j = 0;j < column;j++){
            int random_number = rand()%5 + 1;
            request_line[j] = random_number;
        }

        process_request[i].resources_required = request_line;
    }


    //Gera a tabela de requisição

    int row = number_process;
    int **resources_request;
    resources_request = malloc(row * sizeof(int*));

    printf("\nLinhas alocadas\n");

    //Tabela de requisição recebe a quantidade de recursos necessários de cada processo
    for(int i = 0; i < number_process;i++){
        printf("\nPID %d: ",process_request[i].PID);
        resources_request[i] = calloc(column,sizeof(int));

        for(int j = 0; j < column;j++){
            resources_request[i][j] = process_request[i].resources_required[j];
            printf("%d ",resources_request[i][j]);
        }
    }


    //Verifica linha por linha e cria uma fila de execução
    int column_counter = 0;
    Queue running_process;
    running_process.head = NULL;

    int not_possible = 0;
    int finished_process = 0;
    int i = 0;
    while(1){
        if(not_possible >= row || finished_process >= row)
            break;

        if(process_request[i].process_status == FINISHED){
            finished_process++;
            i = (i+1)%row;
            continue;
        }

        column_counter = 0;
        for(int j = 0; j < column;j++){
            //Incrementa até a quantidade de colunas se o valor da requisição for menor que a disponível
            if(resources_request[i][j] <= avaliable_resources.data[j]){
                ++column_counter;
            }
        }
        //Se todos os itens forem menor, executa o processo.
        if(column_counter >= column){
            queue(&running_process,&process_request[i]);
            running_process.size = running_process.size+1;
            process_request[i].process_status = EXECUTING;
            printf("\nProcesso PID: %d adicionado na fila",process_request[i].PID);
            not_possible = 0;
            process_request[i].process_status = FINISHED;
        }
        else{
            not_possible++;
        }
        i = (i+1)%row;
    }

    //Executa a fila gerada
    queueExecute(&running_process,avaliable_resources.data,column);

    //Desaloca memória (evita memory leak)


    for(int i = 0; i < row;i++){
        free(resources_request[i]);
    }

    free(resources_request);
    for(int i = 0; i < row;i++){
        free(process_request[i].resources_required);
    }

    free(process_request);
    Destroy(&total_resources);
    Destroy(&avaliable_resources);
    return 0;
}