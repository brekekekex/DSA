#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct SLLNODE{
    int datum;
    struct SLLNODE* next;
};

void printSLL(struct SLLNODE* s){
    printf("@%p\tSLL\n", s);
    for(; s != NULL; s = s->next){
        printf("@%p\t%d\n", s, s->datum);
    }
    printf("\n");
}

int length(struct SLLNODE* s){
    int i = 0;
    for(; s != NULL; s = s->next, i++);
    return i;
}

int* toArray(struct SLLNODE* s){
    int* a = malloc(sizeof(int) * length(s));
    assert(a != NULL);
    for(int i = 0; s != NULL; s = s->next, i++){
        a[i] = s->datum;
    }
    return a;
}

int compare(struct SLLNODE* a, struct SLLNODE* b){
    for(;a != NULL && b != NULL; a = a->next, b = b->next){
        if(a->datum != b->datum){
            return 0;
        }
    }
    return 1;
}

int locate(int d, struct SLLNODE* s){
    for(int i = 0; s != NULL; s = s->next, i++){
        if(s->datum == d){
            return i;
        }
    }
    return -1;
}

int contains(int d, struct SLLNODE* s){
    for(; s != NULL; s = s->next){
        if(s->datum == d){
            return 1;
        }
    }
    return 0;
}

struct SLLNODE* reverse(struct SLLNODE* s){
    struct SLLNODE* tmpa = NULL;
    struct SLLNODE* tmpb;
    for(; s->next != NULL;){
        tmpb = s->next;
        s->next = tmpa;
        tmpa = s;
        s = tmpb;
    }
    s->next = tmpa;
    return s;
}

struct SLLNODE* newNode(int d){
    struct SLLNODE* n = malloc(sizeof(struct SLLNODE));
    assert(n != NULL);
    n->datum = d;
    return n;
}

struct SLLNODE* getTail(struct SLLNODE* s){
    for(; s->next != NULL; s = s->next);
    return s;
}

struct SLLNODE* getFrom(int j, struct SLLNODE* s){
    for(int i = 0; i < j; i++, s = s->next);
    return s;    
}

int read(int j, struct SLLNODE* s){
    return getFrom(j, s)->datum;
}

struct SLLNODE* set(int j , int d, struct SLLNODE* s){
    getFrom(j, s)->datum = d;
    return s;
}

void destroy(struct SLLNODE** s){
    struct SLLNODE* tmp;
    for(; *s != NULL;){
        tmp = (*s)->next;
        free(*s);
        *s = tmp;
    }
    *s = NULL;
}

struct SLLNODE* prepend(int d, struct SLLNODE* s){
    struct SLLNODE* n = newNode(d);
    n->next = s;
    return n;
}

struct SLLNODE* append(int d, struct SLLNODE* s){
    struct SLLNODE* n = newNode(d);
    getTail(s)->next = n;
    return s;
}

struct SLLNODE* join(struct SLLNODE* a, struct SLLNODE* b){ 
    getTail(a)->next = b;
    return a;
}

struct SLLNODE* split(int j, struct SLLNODE* s){
    struct SLLNODE* tmp = getFrom(j, s);
    getFrom(j-1, s)->next = NULL;
    return tmp;
}

struct SLLNODE* sortedJoin(struct SLLNODE* a, struct SLLNODE* b){
    struct SLLNODE* tmp;
    if(a->datum > b->datum){
        tmp = a;
        a = b;
        b = tmp;
    }
    struct SLLNODE* n = a;
    while(a->next != NULL){
        while(a->datum <= b->datum){
            if(a->next == NULL){
                a->next = b;
                return n;
            }
            tmp = a;
            a = a->next;
        }
        tmp->next = b;
        if(a->datum > b->datum){
            tmp = a;
            a = b;
            b = tmp;
        }   
    }
    a->next = b;
    return n;
}

struct SLLNODE* mergesort(struct SLLNODE* s){
    if(length(s) == 1){
        return s;
    }
    struct SLLNODE* r = mergesort(split((length(s)/2 + (length(s)%2 != 0)), s));
    struct SLLNODE* l = mergesort(s);
    struct SLLNODE* n = sortedJoin(l, r);
    return n;
}

struct SLLNODE* insert(int j, int d, struct SLLNODE* s){
    struct SLLNODE* n = newNode(d);
    return (j == 0) ? prepend(d, s) : join(s, join(n, split(j, s)));
}

struct SLLNODE* delete(int j, struct SLLNODE* s){
    struct SLLNODE* tmp;
    if(j == 0){
        tmp = s->next;
        free(s);
        return tmp;
    }
    tmp = getFrom(j-1, s)->next;
    getFrom(j-1, s)->next = split(j+1, s);
    free(tmp);
    return s;
}

struct SLLNODE* loop(struct SLLNODE* s){
    getTail(s)->next = s;
    return s;
}

struct SLLNODE* unloop(struct SLLNODE* s){
    struct SLLNODE* a = s;
    for(; s->next != a; s = s->next);
    s->next = NULL;
    return a;
}

struct SLLNODE* rotate(int r, struct SLLNODE* s){
    return unloop(join(getFrom(r, s), s));
}

struct SLLNODE* clone(struct SLLNODE* s){
    struct SLLNODE* n = newNode(s->datum);
    s = s->next;
    for(; s != NULL; s = s->next){
        n = prepend(s->datum, n);
    }
    n = reverse(n);
    return n;
}

struct SLLNODE* fromArray(int* a, int len){
    struct SLLNODE* n = newNode(a[0]);
    for(int i = 1; i < len; i++){
        n = prepend(a[i], n);
    }
    return reverse(n);
}

struct SLLNODE* filter(int d, struct SLLNODE* s){
    while(locate(d, s) != -1){
        s = delete(locate(d,s), s);
    }
    return s;
}

struct SLLNODE* unique(struct SLLNODE* s){
    struct SLLNODE* n = s;
    for(int i = 0; s != NULL; s = s->next, i++){
        int f = read(i, n);
        n = join(n, filter(f, split(i+1, n)));
    }
    return n;
}

struct SLLNODE* subtract(struct SLLNODE* a, struct SLLNODE* b){
    for(; b != NULL; b = b->next){
        a = filter(b->datum, a);
    } 
    return unique(a);
}

struct SLLNODE* cup(struct SLLNODE* a, struct SLLNODE* b){
    return unique(join(unique(a), unique(b)));
}

int main(void){
    int arr[] = {4, 2, 4};
    struct SLLNODE* gamma = fromArray(arr, 3);
    
    int brr[] = {4, 2, 3};
    struct SLLNODE* kappa = fromArray(brr, 3);

    printSLL(subtract(kappa, gamma));
    return 0;

}