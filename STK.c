#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct STKNODE{
    int datum;
    struct STKNODE* below;
};

struct STK{
    struct STKNODE* top;
};

void printSTK(struct STK* s){
    struct STKNODE* n = s->top;
    printf("@%p\tSTK\n", s);
    for(; n != NULL; n = n->below){
        printf("@%p\t%d\n", n, n->datum);
    }
    printf("\n");
}

struct STKNODE* newNode(int d){
    struct STKNODE* n = malloc(sizeof(struct STKNODE));
    assert(n != NULL);
    n->datum = d;
    n->below = NULL;
    return n;
}

void delNode(struct STKNODE** n){
    free(*n);
    (*n) = NULL;
}

struct STK* newStack(){
    struct STK* s = malloc(sizeof(struct STK));
    assert(s != NULL);
    s->top = NULL;
    return s;
}

void push(int d, struct STK* s){
    struct STKNODE* n = newNode(d);
    n->below = s->top;
    s->top = n;
}

void pop(struct STK* s){
    assert(s->top != NULL);
    struct STKNODE* tmp = s->top->below;
    delNode(&(s->top));
    s->top = tmp;
}

void delStack(struct STK** s){
    struct STKNODE* tmpa = (*s)->top;
    struct STKNODE* tmpb; 
    for(; tmpa != NULL;){
        tmpb = tmpa->below; 
        delNode(&tmpa);
        tmpa = tmpb;
    }
    free(*s);
    *s = NULL;
}

int main(void){
    struct STK* a = newStack();
    push(1, a);
    push(2, a);
    push(3, a);
    printSTK(a);
}