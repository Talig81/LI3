#include <stdio.h>
#include "linklist.h"
#include <stdlib.h>
#include <string.h>

struct llink{
	long id;
	char* author;
	int times;
	struct llink *next;
};

LLINK initLL(){
	LLINK l = malloc(sizeof(struct llink));
    l -> id = -1;
    l -> author = (char*)malloc(sizeof(char*)*52);
    l -> times = 0;
    return l;
}



LLINK lasti(LLINK l){
	while(l->next != NULL) l = l -> next;
	return l;
}
void deletas(LLINK* l){
		LLINK current = *l;
		LLINK next;
		while(current != NULL){
			next = current -> next;
			free(current -> author);
			free(current);
			current->next = NULL;
			current = next;
		}
		*l = NULL;
	}

LLINK encontra(long ids, LLINK l){
	LLINK t = l;
	LLINK c = l;
	t = t -> next;
	while(t!=NULL){
		if(t->id == ids) return c;
		c = t;
		t = t->next;
	}
	return NULL;
}

char* findContr(long in,LLINK l){
	while(l != NULL){
		if(l->id == in) return l->author;
		l = l->next;
	}
	return NULL;
}

long* giveFirst(LLINK l){
	long* abc = malloc(sizeof(long)*30);
	if( l!=NULL ){
		for(int i = 0; i<10;i++){
			abc[i] = l -> id;
			l = l->next;
		}
	}
	return abc;
}

LLINK cria(long ids, char* string){
	LLINK l = malloc(sizeof(struct llink));
	l -> id = ids;
	if(string != NULL){
         l -> author = (char*)malloc(sizeof(char)*strlen(string)+1);
         strcpy(l->author, string);
    }
    else l -> author = NULL;
	l -> times = 1;
	l -> next = NULL;
	return l;
}

int encontraPrimeiro(long ids,LLINK l){
	if(ids == l->id) return 1;
	else return 0;
}

LLINK ordenador(LLINK l,LLINK f){
		LLINK c = f -> next;
		LLINK aux = l;
		if(c -> times > f -> times){
			f -> next = c -> next;
			c -> next = NULL;
			if(aux -> times <= c -> times){
				c -> next =aux;
				l = c;
				return l;
			}
			else{
				while(aux -> next-> times > c -> times){
					aux = aux -> next;
					}
				c -> next = aux -> next;
				aux -> next = c;
				}
			}
			return l;
		}


LLINK insertUno(LLINK l, long ids,char* string){
	if(string == NULL) string = " ";
    if(l->id==-1){
        l->id =ids;
        if(string != NULL)
             strcpy(l->author,string);
        l->times=1;
        return l;
    }
	if(l==NULL){
		l = cria(ids,string);
		return l;
	}			
	LLINK test;
	LLINK aux = l;
	if(encontraPrimeiro(ids,l)==1){
		l -> times += 1;
		return l;
	}
	test = encontra(ids,l);
	if(test!=NULL){
		test->next->times += 1;
		l = ordenador(aux,test);
		return l;
	}
	else{
		aux = lasti(aux);
		LLINK nodo = cria(ids,string);
		aux -> next = nodo;
		return l;
	}
}

void printas(LLINK f){
		LLINK l = f;
		int cx = 10;
		while(l!=NULL&& cx!= 0){
    printf("id: %ld ",l->id);
    printf("nome: %s ", l->author);
    printf("times: %d\n",l->times);
    l=l->next;
    cx--;
	}
}
/*
LLINK fazcenas(LLINK l, char* string){
	int n = 6;
	while(n < 12){
		l = insertUno(l,n,string);
		n++;
	}
	while(n>6){
		l = insertUno(l,n,string);
		n--;
	}
	l=insertUno(l,n,string);
	l = insertUno(l,n,string);
	if( l == NULL)
		printf("fazcenasLOL\n");

	return l;
}

int main(int argc,char** argv){
	LLINK l = initLL();
    printf("dacrkhg %ld\n",l->id);
	char* s = "string";
	l = fazcenas(l,s);
	l = insertUno(l,6,s);
	l = insertUno(l,12,s);
	l = insertUno(l,6,s);
    l = insertUno(l,6,s);
	l = insertUno(l,6,NULL);
    l = insertUno(l,81,NULL);
    l = insertUno(l,81,NULL);
    l = insertUno(l,81,NULL);
	//printf("%d\n",l->id);
	deletas(&l);
	if( l == NULL)
		printf("MAIN NULL\n");
	printas(l);
	return 1;
}*/


