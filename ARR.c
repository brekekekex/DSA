#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct ARR{
    int* head;
    int length;
};

void printARR(struct ARR* a){
    printf("@%p\tARR\n", a);
    for(int i = 0; i < a->length; i++){
        printf("%p\t%d\n", (a->head) + (sizeof(int)*i), (a->head)[i]);
    }
    printf("\n");
}

struct ARR* fromArray(int* ar, int l){
    struct ARR* n = malloc(sizeof(struct ARR));
    assert(n != NULL);
    n->head = malloc(sizeof(int)*l);
    assert(n->head != NULL);
    n->length = l;
    for(int i = 0; i < l; i++){
        (n->head)[i] = ar[i];
    }
    return n;
}

void destroy(struct ARR** a){
    free((*a)->head);
    (*a)->length = 0;
    free(*a);
}

void arrFill(int* a, int* b, int bl){
    for(int i = 0; i < bl; i++){
        a[i] = b[i];
    }
}

struct ARR* clone(struct ARR* a){
    struct ARR* n = fromArray(a->head, a->length);
    return n;
}

struct ARR* append(int d, struct ARR* a){
    int* arr = malloc(sizeof(int)*((a->length) + 1));
    assert(arr != NULL);
    arrFill(arr, a->head, a->length);
    free(a->head);
    a->head = arr;
    a->length++;
    (a->head)[(a->length)-1] = d;
    return a;
}

struct ARR* prepend(int d, struct ARR* a){
    int* arr = malloc(sizeof(int)*((a->length) + 1));
    assert(arr != NULL);
    arrFill(arr+1, a->head, a->length);
    free(a->head);
    a->head = arr;
    a->length++;
    (a->head)[0] = d;
    return a;
}

struct ARR* join(struct ARR* a, struct ARR* b){
    int l = (a->length) + (b->length);
    int* arr = malloc(sizeof(int)*l);
    arrFill(arr, a->head, a->length);
    arrFill(arr + (a->length), b->head, b->length);
    free(b->head);
    b->length = 0;
    free(b);
    free(a->head);
    a->head = arr;
    a->length = l;
    return a;
}

int locate(int d, struct ARR* a){
    for(int i = 0; i < a->length; i++){
        if((a->head)[i] == d){
            return i;
        }
    }
    return -1;
}

int contains(int d, struct ARR* a){
    return (locate(d, a) != -1); 
}

struct ARR* selSort(struct ARR* a){
    for(int i = 0; i < (a->length) - 1; i++){
        int cmin = (a->head)[i];
        int cminpos = i;
        for(int j = i + 1; j < a->length; j++){
            if((a->head)[j] < cmin){
                cminpos = j;
            }
        }
        if(i == cminpos){
            continue;
        }
        (a->head)[i] ^= (a->head)[cminpos];
        (a->head)[cminpos] ^= (a->head)[i];
        (a->head)[i] ^= (a->head)[cminpos];
    }
    return a;
}









int main(void){
    int alpha[] = {3, 2};
    struct ARR* a = fromArray(alpha, 2);

    printARR(a);
    a = selSort(a);
    printARR(a);
    
    return 0;

}