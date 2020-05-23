#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct QUENODE{
    int datum;
    int before;
};

struct QUE{
    struct QUENODE* rear;
    struct QUENODE* front;
};

struct QUENODE* newNode(int d){
    struct QUENODE* q = malloc(sizeof(struct QUENODE));
    assert(q != NULL);
    q->datum = d;
    return q;
}

void delNode(struct QUENODE** q){
    free(*q);
    (*q) = NULL;
}

struct QUE* newQueue(void){
    struct QUE* q = malloc(sizeof(struct QUE));
    assert(q != NULL);
    q->rear = NULL;
    q->front = NULL;
    return q;
}

void enqueue(int d, struct QUE* q){

}

int dequeue(struct QUE* q){
    
}

