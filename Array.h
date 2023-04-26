#include <time.h>
#include <stdlib.h>
#include <stdio.h>
typedef struct array{
    int size;
    int *data;
}Array;

int Get(Array* arr,int index){
    if(index > arr->size || index < 0){
        printf("Out of range");
        return -1;
    }
    return arr->data[index];
}

//Aloca um array
void Reserve(Array* arr,int size){
    if(arr->size != 0 || size < 0){
        printf("Already reserved or size invalid");
        return;
    }
    arr->size = size;
    arr->data = calloc(size, sizeof(int));
}

void Destroy(Array *arr){
    free(arr->data);
}
void generateRandomNumber(Array* arr){
    srand(time(NULL));
    for(int i = 0; i < arr->size;i++){
        arr->data[i] = rand() % 10;
    }
}
void printArray(Array* arr){
    printf("\n");
    for(int i = 0; i < arr->size;i++){
        printf("%d ",arr->data[i]);
    }
}