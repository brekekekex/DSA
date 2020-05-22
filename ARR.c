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

struct ARR* insertSort(struct ARR* a){
    for(int i = 1; i < a->length; i++){                               
        int current = (a->head)[i];
        int j = i - 1;
        if((a->head)[j] <= (a->head)[i]){
    next:   continue;
        }
        for(; (a->head)[j] > current; j--){
            (a->head)[j+1] = (a->head)[j];
            if(j == 0){
                (a->head)[j] = current;
                goto next;
            }
        }
        (a->head)[j+1] = current;        
    }
    return a;
}

int getMax(struct ARR* a){
    int cMax = (a->head)[0];
    for(int i = 1; i < a->length; i++){
        if((a->head)[i] > cMax){
            cMax = (a->head)[i];
        }
    }
    return cMax;
}

struct ARR* countSort(struct ARR* a){
    int k = getMax(a);
    int* daa = malloc(sizeof(int)*(k+1));
    assert(daa != NULL);
    for(int i = 0; i < a->length; i++){
        daa[(a->head)[i]]++;
    }
    int p = 0;
    for(int i = 0; i < k + 1; i++){
        for(; daa[i] != 0; daa[i]--, p++){
            (a->head)[p] = i;
        }
    }
    free(daa);
    return a;
}

struct ARR* reverse(struct ARR* a){
    int i = 0;
    int j = (a->length) - 1;
    for(; i < j; i++, j--){
        (a->head)[i] ^= (a->head)[j];
        (a->head)[j] ^= (a->head)[i];
        (a->head)[i] ^= (a->head)[j];
    }
    return a;
}

int binarySearch(int d, struct ARR* a){
    int l = 0;
    int r = a->length;
    int m = (l+r)>>1;
    for(; l < r; m = (l+r)>>1){
        if((a->head)[m] < d){
            l = m + 1;
        } else{
            r = m;
        }
    }
    return ((a->head)[l] == d) ? l : -1;
}

int main(void){
    int alpha[] = {1, 2, 3, 3};
    struct ARR* a = fromArray(alpha, 3);

    return 0;

}