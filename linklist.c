#include <stdio.h>
#include "linklist.h"
#include <stdlib.h>
#include <string.h>

struct llink{
	int id;
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

/*void deletas(llink** l){
		llink* current = *l;
		llink* next;
		while(current != NULL){
			next = current -> next;
			free(current -> author);
			free(current);
			current->next = NULL;
			current = next;
		}
		*l = NULL;
	}*/


LLINK encontra(int ids, LLINK l,int* i){
	LLINK t = l;
	LLINK c = l;
	t = t -> next;
	while(t!=NULL){
		if(t->id == ids) return c;
		c = t;
		t = t->next;
	}
    (*i)=1;
	return c;
}

LLINK cria(int ids, char* string){
	LLINK l = malloc(sizeof(struct llink));
	l -> id = ids;
	l -> author = (char*)malloc(sizeof(char)*strlen(string)+1);
	if(string != NULL) strcpy(l->author, string);
	l -> times = 1;
	l -> next = NULL;
	return l;
}

int encontraPrimeiro(int ids,LLINK l){
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


LLINK insertUno(LLINK l, int ids,char* string){
    if(l->id==-1){
        l->id =ids;
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
    int i = 0;
	test = encontra(ids,l,&i);
	if(test!=NULL&&i==0){
		test->next->times += 1;
		l = ordenador(aux,test);
		return l;
	}
	else{
		LLINK nodo = cria(ids,string);
		test -> next = nodo;
		return l;
	}
}



void printas(LLINK l){
		while(l!=NULL){
    printf("id: %d ",l->id);
    printf("nome: %s ", l->author);
    printf("times: %d\n",l->times);
    l=l->next;}
}
/*
llink* fazcenas(llink* l, char* string){
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
	llink* l = NULL;
    l = primeiro(l);
    printf("dacrkhg %d\n",l->id);
	char* s = "string";
	l = fazcenas(l,s);
	l = insertUno(l,6,s);
	l = insertUno(l,12,s);
	l = insertUno(l,6,s);
	
	//printf("%d\n",l->id);
	if( l == NULL)
		printf("MAIN NULL\n");
	printas(l);
	return 1;
}*/
