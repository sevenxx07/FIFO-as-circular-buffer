#include "stdio.h"
#include "stdlib.h"
#include "string.h"
 
#include "queue.h"
//prvni tail se nastavuje uz na 1 i kdyz je to nula 
 
/* creates a new queue with a given size */
queue_t* create_queue(int capacity){
    //capacity is n + we are returning pointer on struct q
    //need to define every variable of q 
    queue_t *q;
    q = (queue_t*)malloc(sizeof(queue_t)); 
    if (q == NULL){
        exit(100);
    }
    q->capacity = capacity;
    q->counter = 0;
    q->head = 0;
    q->tail = 0;
    q->array = (void**)malloc(capacity*sizeof(void*));
    if (q->array == NULL){
        free(q);
        exit(100);
    }
 
    for (int i = 0; i < capacity; i++){
        q->array[i] = NULL;
    }
 
 
    return q;
}
 
/* deletes the queue and all allocated memory */
void delete_queue(queue_t *queue){
    free(queue->array);
    free(queue);
    queue = NULL; //no one can use this pointer
}
/*
 * inserts a reference to the element into the queue
 * returns: true on success; false otherwise
 */
bool push_to_queue(queue_t *queue, void *data){
    bool ret;
    /*
    printf("push to queue\n");
    printf("counter: %d\n", queue->counter);
    printf("head: %d\n", queue->head);
    printf("tail: %d\n", queue->tail);
    */
    if(queue->counter >= queue->capacity){
        queue->capacity *= 2;
        queue->array = (void**)realloc(queue->array,queue->capacity*(sizeof(void*)));
        //queue->array = array_2;
        for (int i = queue->capacity/2; i < queue->capacity; i++){
            queue->array[i] = NULL;
        }
        if (queue->tail == 0){
            queue->tail = queue->capacity/2;
        }
        if(queue->tail < queue->head){
            int new_index = queue->capacity/2;
            int counter = 0;
            for(int j = 0; j < queue->tail; j++){
                queue->array[new_index] = queue->array[j];
                queue->array[j] = NULL;
                new_index++;
                counter++;
            }
            queue->tail = queue->capacity/2 + counter + 1;
        }
         
    }
 
    ret = true;
    queue->array[queue->tail] = data;
    queue->tail++;
    if (queue->tail > queue->capacity - 1){
        queue->tail = 0;
    }
    queue->counter++;
    return ret;
}
 
/*
 * gets the first element from the queue and removes it from the queue
 * returns: the first element on success; NULL otherwise
 */
void* pop_from_queue(queue_t *queue){
    /*
    printf("pop from queue\n");
    printf("counter: %d\n", queue->counter);
    printf("head: %d\n", queue->head);
    printf("tail: %d\n", queue->tail);
    */
    if(queue->counter == 0){
        return NULL;
    }
 
    void *first_elem = queue->array[queue->head];
    queue->array[queue->head] = NULL;
    queue->head++;   
    if(queue->head > queue->capacity - 1){
        queue->head = 0;
    }
    queue->counter--;
     
     
    if(queue->counter < queue->capacity/2){
        if (queue->head >= queue->capacity/2 && queue->tail < queue->capacity/2){
            int new_index = queue->capacity/2 - (queue->capacity - queue->head ) ;
            //printf("new index: %d\n", new_index);
     
            for(int i = queue->head; i < queue->capacity ; i++){
                //printf("XXX\n");
                queue->array[new_index] = queue->array[i];
                queue->array[i] = NULL;
                new_index++;
            }
            queue->head = queue->capacity/2 - (queue->capacity - queue->head);
        }
        if (queue->head >= queue->capacity/2 && queue->tail > queue->capacity/2){
            int new_index = 0;
 
            for(int i = queue->head; i < queue->tail; i++){
                queue->array[new_index] = queue->array[i];
                queue->array[i] = NULL;
                new_index++;
            }
            queue->head = 0;
            queue->tail = new_index;
        }
        if(queue->tail >= queue->capacity/2){
            int new_index = 0;
            for(int i = queue->capacity/2; i < queue->tail; i++){
                queue->array[new_index] = queue->array[i];
                queue->array[i] = NULL;
                new_index++;
            }
            queue->tail = new_index;
 
        } 
 
        queue->capacity /= 2;
        queue->array = (void**)realloc(queue->array,queue->capacity*(sizeof(void*)));
        if (queue->array == NULL){
            free(queue->array);
            exit(100);
        }
     
         
    }
    return first_elem;
     
}
 
/*
 * gets idx-th element from the queue, i.e., it returns the element that 
 * will be popped after idx calls of the pop_from_queue()
 * returns: the idx-th element on success; NULL otherwise
 */
void* get_from_queue(queue_t *queue, int idx){
    /*
    printf("get from queue\n");
    printf("counter: %d\n", queue->counter);
    printf("head: %d\n", queue->head);
    printf("tail: %d\n", queue->tail);
    */
     
    if(idx < 0 || idx + 1 > queue->counter){
             
        return NULL;
    }else{
        return queue->array[idx + queue->head];
    }
}
 
/* gets number of stored elements */
int get_queue_size(queue_t *queue){
    return queue->counter;
}
