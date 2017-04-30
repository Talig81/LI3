#ifndef LISTA_LIGADA
#define LISTA_LIGADA

typedef struct llink* LLINK;

LLINK initLL();
LLINK encontra(long ids, LLINK l);
LLINK insertUno(LLINK l,long ids, char* string);
void printas(LLINK l);
char* findContr(long in,LLINK l);
long* giveFirst(LLINK l);
void deletas(LLINK* l);
#endif 