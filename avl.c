#include "avl.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAXLNE 20;
#define NUMBS 19000;

struct node {
  long data;
  char *content;
  struct node *left;
  struct node *right;
  int height;
  struct mini *mini;
  int qtRevs;
  long maxBytes;
  long nW;
};

struct mini{
    long data;
    int height;
    char* timestamp;
    struct mini *left;
    struct mini *right;
};

NODE leftie(NODE t){
    t = t->left;
    return t;
}

bool startsWith(const char *pre, const char *str)
{
    size_t lenpre = strlen(pre),
           lenstr = strlen(str);
    return lenstr < lenpre ? false : strncmp(pre, str, lenpre) == 0;
}

int preFixes(NODE t,char** arr, int i,char* string){
    if(t == NULL)
        return i;
    if(startsWith(string,t->content)){
        arr[i] = strdup(t->content);
        arr[i+1]=malloc(sizeof(char)*30);
        i++;
    }
    if(t->left != NULL)
        i = preFixes(t->left, arr, i,string);
    if(t->right != NULL)
        i = preFixes(t->right, arr, i,string);
    return i;
}

long bitie(NODE t){
    return t->maxBytes;
}

long wordie(NODE t){
    return t-> nW;
}

NODE rightie(NODE t){
    t = t->right;
    return t;
}

NODE find(long e, NODE t ){
    if( t == NULL )
        return NULL;
    if( e < t->data )
        return find( e, t->left );
    else if( e > t->data )
        return find( e, t->right );
    else
        return t;
}

M encontraContrs(M m, long* n){
    if(m==NULL) return NULL;
    if(*n > m->data) return encontraContrs(m->right,n);
    else if(*n < m->data) return encontraContrs(m->left,n);
    else return m;
}

M getMini(NODE t){
    if(t==NULL) return NULL;
    return t->mini;
}

int encontraContribuidores(M m, long n){
    if(m==NULL) return 0;
    if(n > m->data) return encontraContribuidores(m->right,n);
    else if(n < m->data) return encontraContribuidores(m->left,n);
    else return 1;
}

char* encontraTitulo(NODE t, long n, long m){
    NODE f = find(n,t);
    if(f == NULL) return NULL;
    M mini = encontraContrs(f -> mini, &m);
    if(mini == NULL) return NULL;
    return mini->timestamp;
}

char* encontraTimestamp(NODE t, long n){
    NODE f = find(n,t);
    if ( f == NULL) return NULL;
    return f -> content;
}

void disposeMini(M m){
    if(m==NULL) return;
    if(m!=NULL){
        disposeMini(m->left);
        disposeMini(m->right);
        free(m->timestamp);
        free(m);
    }
    m = NULL;
    return;
}

int encontraRev(NODE t,int* n,long number){
    if(t==NULL) return 0;
    NODE f = t;
    NODE c = t;
    f = find(*n,c);
    if(f == NULL) return 0;
    M mini = encontraContrs(getMini(f),&number);
    if(mini == NULL) return 0;
    return 1;
}

void dispose(NODE t){
    if(t==NULL) return;
    if(t!=NULL){
        dispose(t->left);
        dispose(t->right);
        disposeMini(t->mini);
        t->mini=NULL;
        free(t->content);
        free(t);
    }
    t = NULL;
    return;
}

int qtRevisoes(NODE t){
    int c = 0;
    if(t==NULL){
        return 0;
    }
        c = t->qtRevs;    
        c += qtRevisoes(t->left);
        c += qtRevisoes(t->right);
        return c;
}

static long max(long l, long r)
{
    return l > r ? l: r;
}

static int height(NODE n)
{
    if( n == NULL )
        return -1;
    else
        return n->height;
}


static int heightMini(M m){
    if(m==NULL) return -1;
    else return m -> height;
}

static M miniSingleLeft(M m){
    M m1 = NULL;
    m1 = m -> left;
    m -> left = m1 -> right;
    m1 -> right = m;
    m->height = max(heightMini(m->left),heightMini(m->right))+1;
    m1 -> height = max(heightMini(m1->left),m->height)+1;
    return m1;
}
    
 NODE single_rotate_with_left( NODE k2 )
{
    NODE k1 = NULL;

    k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;

    k2->height = max( height( k2->left ), height( k2->right ) ) + 1;
    k1->height = max( height( k1->left ), k2->height ) + 1;
    return k1;
}

static M miniSingleRight(M m1){
    M m = NULL;
    m = m1 -> right;
    m1 -> right = m ->left;
    m -> left = m1;
    m1->height = max(heightMini(m1->left),heightMini(m1->right))+1;
    m -> height = max(heightMini(m->left),m1->height)+1;
    return m;
}

static NODE single_rotate_with_right( NODE k1 )
{
    NODE k2;

    k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;

    k1->height = max( height( k1->left ), height( k1->right ) ) + 1;
    k2->height = max( height( k2->right ), k1->height ) + 1;

    return k2;
}

static M doubleMiniLeft(M m3){
    m3 -> left = miniSingleRight(m3->left);
    return miniSingleLeft(m3);
}
static NODE double_rotate_with_left( NODE k3 )
{
    /* Rotate between k1 and k2 */
    k3->left = single_rotate_with_right( k3->left );

    /* Rotate between K3 and k2 */
    return single_rotate_with_left( k3 );
}

static M doubleMiniRight(M m){
    m -> right = miniSingleLeft(m);
    return miniSingleRight(m);
}

static NODE double_rotate_with_right( NODE k1 )
{

    k1->right = single_rotate_with_left( k1->right );
    return single_rotate_with_right( k1 );
}
M initMini(int e,char* times, NODE t){
    M m = malloc(sizeof(struct mini));
        m -> timestamp = (char*)malloc(sizeof(char)*strlen(times)+1);
        m -> data = e;
        m -> height = 0;
        strcpy(m -> timestamp,times);
        m -> left = m -> right = NULL;
        t -> qtRevs += 1;
        return m;
}

M insertMini(int e, M m,char* times,NODE t){
    if(m==NULL){
        m = initMini(e,times,t);
    }
    else if( e < m->data )
    {
        m->left = insertMini( e, m->left,times,t);
        if( heightMini(m->left) - heightMini(m->right)==2)
            if( e < m->left->data )
                m = miniSingleLeft(m);
            else
                m = doubleMiniLeft(m);
    }
    else if( e > m->data )
    {
        m->right = insertMini( e, m->right, times,t) ;
        if( heightMini(m->right) - heightMini(m->left)==2)
            if( e > m->right->data )
                m = miniSingleRight(m);
            else
                m = doubleMiniRight(m);
    }
    m->height = max( heightMini(m->left), heightMini(m->right))+1;
    return m;
}
NODE insert(long e, NODE t,char* string,char* revisao,int a,long* bytess,long* nWord)
{
    if( t == NULL )
    {
        t = malloc(sizeof(struct node));
        if( t == NULL )
        {
            fprintf (stderr, "Out of memory!!! (insert)\n");
            exit(1);
        }
        else
        {   
            M f = NULL;
            t->data = e;
            t->height = 0;
            t->content = (char*)malloc(sizeof(char)*strlen(string)+1);
            if(string == NULL) t->content = NULL;
            strcpy( t->content, string );
            t->left = t->right = NULL;
            t->qtRevs = 0;
            t->maxBytes = (*bytess);
            t->nW = 0;
            t -> mini = insertMini(a,f,revisao,t);           
        }
    }
    else if( e < t->data )
    {
        t->left = insert( e, t->left,string,revisao,a,bytess,nWord);
        if( height( t->left ) - height( t->right ) == 2 )
            if( e < t->left->data )
                t = single_rotate_with_left( t );
            else
                t = double_rotate_with_left( t );
    }
    else if( e > t->data )
    {
        t->right = insert( e, t->right, string,revisao,a,bytess,nWord ) ;
        if( height( t->right ) - height( t->left ) == 2 )
            if( e > t->right->data )
                t = single_rotate_with_right( t );
            else
                t = double_rotate_with_right( t );
    }
    if(t -> data == e){
        t -> mini = insertMini(a,t->mini,revisao,t);
        if(*bytess>t->maxBytes) t -> maxBytes =*bytess;
        if(*nWord > t->nW) t -> nW = *nWord;
        }
    t->height = max( height( t->left ), height( t->right ) ) + 1;
    return t;
}


int countNodes(NODE t){
    int c = 1;
    if(t==NULL)
        return 0;
    else{
        c += countNodes(t->left);
        c += countNodes(t->right);
        return c;
    }
}

long get(NODE n)
{
    return n->data;
}


/*
int main(){
    NODE t = NULL;
    long a = 10;
    long b = 40;
    int fd = 40;
    char** arr = malloc(sizeof(char)*19000);
    t = insert (10,t,"titulo","2424-2424-242",40,&a,&b);
    t = insert (12,t,"tr","42342",41,&a,&b);
    t = insert (13,t,"titular","234",44,&a,&b);
    NODE f = find(12,t);
    if(f->mini==NULL) printf("foi aqui\n");
    printf("aa%ld\n",f->data);
    printf("%ld\n",t->mini->data);
    printf("%ld\n",t->data);
    printf("PFF %d\n",encontraRev(t,&fd,10));
    int i = encontraContribuidores(t->mini,41);
    char* string = "t";
    printf("fds%d\n",i);
    int cd = 0;
    printf("%d\n",preFixes(t,arr,cd,string));
    printf("%s %s %s\n",arr[0],arr[1],arr[2]);
    printf("%s %s %s\n",arr[0],arr[1],arr[2]);
    return 1;
}*/