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
node *insert(int e, node* t,char* string );
node *delete (int data, node *t);
int countNodes(node* t);
node* display_avl(node *t);
int get(node *n);
int counts(node* t);
#endif // AVLTREE_H_INCLUDED
