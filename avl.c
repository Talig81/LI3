#include "avl.h"

node* find(long e, node* t )
{
    if( t == NULL )
        return NULL;
    if( e < t->data )
        return find( e, t->left );
    else if( e > t->data )
        return find( e, t->right );
    else
        return t;
}

void disposeMini(mini* m){
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

void dispose(node* t){
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

int qtRevisoes(node* t){
    int c = 0;
    if(t==NULL){
        return 0;
    }
        c = t->qtRevs;    
        c += qtRevisoes(t->left);
        c += qtRevisoes(t->right);
        return c;
}

int contaMini(mini* m){
    int c = 0;
    if(m==NULL)return 0;
    c += contaMini(m->left);
    c += contaMini(m->right); 
    return c;
}

int contaTudo(node* t){
    int c = 1;
    if(t==NULL)return 0;
    c += contaTudo(t->left);
    c += contaTudo(t->right);
    c += contaMini(t->mini);
    return c;
}

char* encontraRev(mini* m,int n){
    if(m==NULL)
        return NULL;
    if(n < m->data)
        return encontraRev(m->left,n);
    if(n > m -> data)
        return encontraRev(m->right,n);
    else
        return m -> timestamp;
}


static long max(long l, long r)
{
    return l > r ? l: r;
}

static int height(node* n)
{
    if( n == NULL )
        return -1;
    else
        return n->height;
}


static int heightMini(mini* m){
    if(m==NULL) return -1;
    else return m -> height;
}

static mini* miniSingleLeft(mini* m){
    mini* m1 = NULL;
    m1 = m -> left;
    m -> left = m1 -> right;
    m1 -> right = m;
    m->height = max(heightMini(m->left),heightMini(m->right))+1;
    m1 -> height = max(heightMini(m1->left),m->height)+1;
    return m1;
}
    
static node* single_rotate_with_left( node* k2 )
{
    node* k1 = NULL;

    k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;

    k2->height = max( height( k2->left ), height( k2->right ) ) + 1;
    k1->height = max( height( k1->left ), k2->height ) + 1;
    return k1;
}

static mini* miniSingleRight(mini* m1){
    mini* m = NULL;
    m = m1 -> right;
    m1 -> right = m ->left;
    m -> left = m1;
    m1->height = max(heightMini(m1->left),heightMini(m1->right))+1;
    m -> height = max(heightMini(m->left),m1->height)+1;
    return m;
}

static node* single_rotate_with_right( node* k1 )
{
    node* k2;

    k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;

    k1->height = max( height( k1->left ), height( k1->right ) ) + 1;
    k2->height = max( height( k2->right ), k1->height ) + 1;

    return k2;
}

static mini* doubleMiniLeft(mini* m3){
    m3 -> left = miniSingleRight(m3->left);
    return miniSingleLeft(m3);
}
static node* double_rotate_with_left( node* k3 )
{
    /* Rotate between k1 and k2 */
    k3->left = single_rotate_with_right( k3->left );

    /* Rotate between K3 and k2 */
    return single_rotate_with_left( k3 );
}

static mini* doubleMiniRight(mini* m){
    m -> right = miniSingleLeft(m);
    return miniSingleRight(m);
}

static node* double_rotate_with_right( node* k1 )
{

    k1->right = single_rotate_with_left( k1->right );
    return single_rotate_with_right( k1 );
}

mini* insertMini(int e, mini* m,char* times,node* t){
    if(m==NULL){
        m = (mini*)malloc(sizeof(mini));
        m -> timestamp = (char*)malloc(sizeof(char)*strlen(times)+1);
        m -> data = e;
        m -> height = 0;
        strcpy(m -> timestamp,times);
        m -> left = m -> right = NULL;
        t -> qtRevs += 1;
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
node* insert(long e, node * t,char* string,char* revisao,int a)
{
    if( t == NULL )
    {
        t = (node*)malloc(sizeof(node));
        if( t == NULL )
        {
            fprintf (stderr, "Out of memory!!! (insert)\n");
            exit(1);
        }
        else
        {   
            mini* f = NULL;
            t->data = e;
            t->height = 0;
            t->content = (char*)malloc(sizeof(char)*strlen(string)+1);
            strcpy( t->content, string );
            t->left = t->right = NULL;
            t->qtRevs = 0;
            t -> mini = insertMini(a,f,revisao,t);           
        }
    }
    else if( e < t->data )
    {
        t->left = insert( e, t->left,string,revisao,a );
        if( height( t->left ) - height( t->right ) == 2 )
            if( e < t->left->data )
                t = single_rotate_with_left( t );
            else
                t = double_rotate_with_left( t );
    }
    else if( e > t->data )
    {
        t->right = insert( e, t->right, string,revisao,a ) ;
        if( height( t->right ) - height( t->left ) == 2 )
            if( e > t->right->data )
                t = single_rotate_with_right( t );
            else
                t = double_rotate_with_right( t );
    }
    if(t -> data == e){
        t -> mini = insertMini(a,t->mini,revisao,t);
        }
    t->height = max( height( t->left ), height( t->right ) ) + 1;
    return t;
}


int countNodes(node* t){
    int c = 1;
    if(t==NULL)
        return 0;
    else{
        c += countNodes(t->left);
        c += countNodes(t->right);
        return c;
    }
}

int get(node* n)
{
    return n->data;
}


