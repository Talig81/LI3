#ifndef AVLTREE_H_INCLUDED
#define AVLTREE_H_INCLUDED

typedef struct node {
  int data;
  char *content;
  struct node *left;
  struct node *right;
  int height;
} node;

void dispose(node *t);
node *find(int e, node *t);
node *find_min(node *t);
node *find_max(node *t);
node *insert(int e, node* t,int * conta,char* string );
node *delete (int data, node *t);
void display_avl(node *t);
int get(node *n);
#endif // AVLTREE_H_INCLUDED
