#ifndef LISTA_LIGADA
#define LISTA_LIGADA

typedef struct llink{
	int id;
	char* author;
	int times;
	struct llink *next;
} llink;


void deletas(llink** l);
void printas(llink* l);
llink* encontra(int ids, llink* l);
llink* ordenador(llink* l,llink* f);
llink* cria(int ids, char* string);
llink* lasti(llink* l);
llink* insertUno(llink* l,int ids, char* string);
int encontraPrimeiro(int ids,llink* l);
void printas(llink* l);
llink* primeiro(llink* l);

#endif 