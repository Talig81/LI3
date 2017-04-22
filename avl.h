#ifndef AVLTREE_H_INCLUDED
#define AVLTREE_H_INCLUDED


typedef struct node* NODE;
typedef struct mini* M;

void dispose(NODE t);
NODE find(long e, NODE t);
NODE insert(long e, NODE t,char* string,char* revisao,int a);
int countNodes(NODE t);
int qtRevisoes(NODE t);
int encontraRev(NODE t,int* n, long* number);
#endif // AVLTREE_H_INCLUDED