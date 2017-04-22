#ifndef LISTA_LIGADA
#define LISTA_LIGADA

typedef struct llink* LLINK;

LLINK initLL();
LLINK encontra(int ids, LLINK l,int* i);
LLINK insertUno(LLINK l,int ids, char* string);
void printas(LLINK l);
#endif 