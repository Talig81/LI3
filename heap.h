#ifndef HEAP_H
#define HEAP_H

typedef struct node_t * NODE_T;
typedef struct heap_t * HEAP;
typedef struct node * NODE;

void push (HEAP h, long priority, long data);
long pop (HEAP h);
HEAP initHeap();
HEAP constroi(HEAP h, NODE t);
long* printasHEAP(HEAP h,int n,long* aux);
HEAP constroiWord(HEAP h, NODE t);

#endif
