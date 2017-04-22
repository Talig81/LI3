#ifndef AVLTREE_H_INCLUDED
#define AVLTREE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
  long data;
  char *content;
  struct node *left;
  struct node *right;
  int height;
  struct mini *mini;
  int qtRevs;
} node;

typedef struct mini{
    int data;
    int height;
    char* timestamp;
    struct mini *left;
    struct mini *right;
}mini;


void dispose(node *t);
node *find(long e, node *t);
node* insert(long e, node* t,char* string,char* revisao,int a);
int countNodes(node* t);
int get(node *n);
int qtRevisoes(node* t);
int contaTudo(node* t);
int encontraRev(node* t,int* n, long* number);
#endif // AVLTREE_H_INCLUDED