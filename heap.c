#include <stdio.h>
#include <stdlib.h>
#include "heap.h"
#include "avl.h"
 
struct node_t {
    long priority;
    long data;
};
 
struct heap_t{
   struct node_t *nodes;
    int len;
    int size;
};
 

HEAP initHeap(){
    HEAP hea = malloc(sizeof(struct heap_t));
    push(hea,1,1);
    return hea;
}

HEAP constroi(HEAP h,NODE t){
    if(t==NULL) return h;
    h = constroi(h,leftie(t));
    h = constroi(h,rightie(t));
    push(h,bitie(t),get(t));
    return h;
}

HEAP constroiWord(HEAP h,NODE t){
    if(t==NULL) return h;
    h = constroiWord(h,leftie(t));
    h = constroiWord(h,rightie(t));
    push(h,wordie(t),get(t));
    return h;
}
/*
void eraseHeap(HEAP* h){
    for(int i = 0;i<(*h)->size-1;i++){
        free((*h)->nodes);
    }
    free(h);
    return;
}*/

long* printasHEAP(HEAP h,int n,long* aux){
    for(int i = 0; i < n;i++){
        aux[i] = h->nodes[i].data;
    }
    return aux;
}

void push (HEAP h, long priority, long data) {
    if (h->len + 1 >= h->size) {
        h->size = h->size ? h->size * 2 : 4;
        h->nodes = realloc(h->nodes, h->size * sizeof (struct node_t));
    }
    int i = h->len + 1;
    int j = i / 2;

    while (i > 1 && h->nodes[j].priority < priority) {
        
        h->nodes[i] = h->nodes[j];
        i = j;
        j = j / 2;
    }
    
    h->nodes[i].priority = priority;
    h->nodes[i].data = data;
    h->len++;
}
 
long pop (HEAP h) {
    int i, j, k;
    if (!h->len) {
        return 0;
    }
    long prioriti = h->nodes[1].priority;
    printf("%ld",prioriti);
    long data = h->nodes[1].data;
    h->nodes[1] = h->nodes[h->len];
    h->len--;
    i = 1;
    while (1) {
        k = i;
        j = 2 * i;
        if (j <= h->len && h->nodes[j].priority > h->nodes[k].priority) {
            k = j;
        }
        if (j + 1 <= h->len && h->nodes[j + 1].priority > h->nodes[k].priority) {
            k = j + 1;
        }
        if (k == i) {
            break;
        }
        h->nodes[i] = h->nodes[k];
        i = k;
    }
    h->nodes[i] = h->nodes[h->len + 1];
    return data;
}
/*
int main () {
    HEAP h = initHeap();
    push(h, 3, 42);
    push(h, 4, 12);
    push(h, 5, 65);
    push(h, 1, 81);
    push(h, 2, 4);
    int i =0;
    if(h==NULL) printf("bem");
    return i;
}*/