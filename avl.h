#ifndef AVLTREE_H_INCLUDED
#define AVLTREE_H_INCLUDED


typedef struct node* NODE;
typedef struct mini* M;

int preFixes(NODE t,char** argv, int i,char* string);
void dispose(NODE t);
NODE find(long e, NODE t);
NODE insert(long e, NODE t,char* string,char* revisao,int a,long* bytess,long* nWord);
int countNodes(NODE t);
int qtRevisoes(NODE t);
char* encontraTitulo(NODE t, long n, long m);
char* encontraTimestamp(NODE t, long n);
NODE leftie(NODE t);
NODE rightie(NODE t);
long bitie(NODE t);
long wordie(NODE t);
long get(NODE t);
M getMini(NODE t);
int encontraRev(NODE t,int n,long number);
int encontraContribuidores(M m, long n);
#endif // AVLTREE_H_INCLUDED